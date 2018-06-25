package main

import (
	"bufio"
	"bytes"
	"encoding/json"
	"errors"
	"flag"
	"fmt"
	"io"
	"io/ioutil"
	"net/http"
	"os/exec"
	"strconv"
	"strings"
	"time"

	"github.com/golang/glog"
)

const (
	COS_SITE    = "cos-cn-hangzhou.chinac.com"
	CDN_URL     = "test-cdn-url"
	CDN_PCDOWN  = "test-pcdown51cache"
	CDN_PCVIDEO = "test-pcvideo51cache"

	PCDOWN_KEYWORD  = "pcdown51cache"
	PCVIDEO_KEYWORD = "pcvideo51cache"
	INC             = "inc"
)

type FetchBody struct {
	sourceUrl      string
	callbackUrl    string
	callbackParams int
}

var (
	mapping = map[string]string{CDN_PCDOWN: "pcdown51cache.titan.mgtv.com",
		CDN_PCVIDEO: "pcvideo51cache..titan.mgtv.com"}
	fetchBody = FetchBody{callbackUrl: "127.0.0.1:8080"}
)

func replayUrls(r *io.Reader, retries int) (err error) {

	bucketName := ""
	bufReader := bufio.NewReader(r)
	EOF := false

	for {
		if EOF {
			break
		}

		// 读取URL
		var srcurl string
		srcurl, err = bufReader.ReadString('\n')
		if err != nil {
			if err == io.EOF {
				glog.Infof("End to CDN URL file<%s>", srcurl)
				err = nil
				EOF = true
			} else {
				glog.Errorf(err.Error())
				return
			}
		}
		srcurl = strings.Trim(srcurl, "\r\n")

		// 生成发往COS的URL
		var cosurl string
		if bucketName == "" {
			if strings.Contains(srcurl, PCDOWN_KEYWORD) {
				bucketName = CDN_PCDOWN
			} else if strings.Contains(srcurl, PCVIDEO_KEYWORD) {
				bucketName = CDN_PCVIDEO
			} else {
				errmsg := fmt.Sprintf("the CDN URL do not contain <%s> or <%s> keyword", PCDOWN_KEYWORD, PCVIDEO_KEYWORD)
				err = errors.New(errmsg)
				return
			}
		}
		cosurl = strings.Replace(srcurl, mapping[bucketName], bucketName+"."+COS_SITE, 1)

		index := strings.Index(srcurl, mapping[bucketName])
		if index < 0 {
			panic("can not be here")
		}
		index = index + len(mapping[bucketName]) + 1
		objectName := srcurl[index:]

		// 向COS发起POST请求
		fetchBody.callbackParams = fmt.Sprintf("retries=%d", retries)
		fetchBody.sourceUrl = srcurl
		body, err := json.Marshal(fetchBody)
		if err != nil {
			glog.Errorf("json.Marshal failed,err<%s>", err.Error())
			continue
		}

		cosResp, err := http.Post(cosurl, "application/json", bytes.NewReader(body))
		if err != nil {
			glog.Errorf("Failed to Get Response from url<%s>, error<%s>", cosurl, err.Error())
			continue
		} else if cosResp.StatusCode != http.StatusOK {
			glog.Warningf("HEAD URL<%s> failed, StatusCode = %d", cosurl, cosResp.StatusCode)
			continue
		}

		var content bytes.Buffer
		content.WriteString("\n" + cosResp.Status + "\n")
		for key, val := range cosResp.Header {
			content.WriteString(key + ": " + val[0] + "\n")
		}
		glog.Infof("%s", content.String())
	}

	return
}

func portBucket(bucketName string, srcSite string) (err error) {

	glog.Infof("Start to port to bucket<%s>", bucketName)
	date := strings.Split(time.Now().String(), " ")[0]
	count := 1
	for {
		// 从COS读取URL文件，如果读取失败，程序直接返回。
		url := "http://" + CDN_URL + "." + COS_SITE + "/" + bucketName + "-" + INC
		url = url + "-" + date + "-" + strconv.Itoa(count) + ".txt"
		glog.Infof("Begin to get cdn url file<%s>", url)
		count += 1

		var resp *http.Response
		resp, err = http.Get(url)
		if err != nil {
			glog.Errorf("Failed to GET the url file from COS, %s", err.Error())
			return
		}

		if resp.StatusCode == http.StatusNotFound {
			glog.Infof("url file<%s> not found, and that means no more url files", url)
			break
		} else if resp.StatusCode != http.StatusOK {
			errmsg := fmt.Sprintf("Failed to GET the file from COS, Status Code = %d", resp.StatusCode)
			glog.Errorf(errmsg)
			err = errors.New(errmsg)
			return
		}
		replayUrls(resp)

		glog.Infof("End to replay url file<%s>", url)
	}

	glog.Infof("End to port data on bucket<%s>", bucketName)
	return
}

func IncPort() {

	for bucketName, srcSite := range mapping {
		portBucket(bucketName, srcSite)
	}
	glog.Flush()
}

type FetchRespData struct {
	Result     string
	SourceUrl  string
	BucketName string
	ObjectName string
}

func HelloServer(w http.ResponseWriter, req *http.Request) {

	data, err := ioutil.ReadAll(req.Body)
	if err != nil {
		glog.Errorf("Read Body Failed, err<%s>", err.Error())
		return
	}
	glog.Infof("response data, <%s>", data)

	fetchRespData := FetchRespData{}
	if json.Unmarshal(data, &fetchRespData) != nil {
		glog.Errorf("Unmarshal data<%s> Failed, err<%s>", string(data), err.Error())
		return
	}

	if fetchRespData.Result == "Success" {
		return
	}

	resp, err := http.Head(fetchRespData.SourceUrl)
	if err != nil {
		glog.Errorf("Failed to send HEAD request <%s>", fetchRespData.SourceUrl)
		return
	}

	if resp.StatusCode != http.StatusOK {
		glog.Errorf("The URL<%s> dose not exist on source site, status code<%s>", fetchRespData.SourceUrl, resp.StatusCode)
		return
	}

	glog.Infof("Failed to Port URL <%s>, and now start to port it again", fetchRespData.SourceUrl)
	reader := strings.NewReader(fetchRespData.SourceUrl)
	if replayUrls(reader) != nil {
		glog.Errorf("replay URL<%s> failed", FetchRespData.SourceUrl)
	}
}

func HttpServer() {

	http.HandleFunc("/", HelloServer)
	glog.Fatalln(http.ListenAndServe(":8080", nil))
}

func main() {
	flag.Parse()
	//	IncPort()
	HttpServer()
}
