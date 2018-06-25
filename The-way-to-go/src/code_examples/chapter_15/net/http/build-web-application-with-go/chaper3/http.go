net/http/client.go:
// Copyright 2009 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// HTTP client. See RFC 2616.
//
// This is the high-level Client interface.
// The low-level implementation is in transport.go.

package http

// A Client is an HTTP client. Its zero value (DefaultClient) is a
// usable client that uses DefaultTransport.
//
// The Client's Transport typically has internal state (cached TCP
// connections), so Clients should be reused instead of created as
// needed. Clients are safe for concurrent use by multiple goroutines.
//
// A Client is higher-level than a RoundTripper (such as Transport)
// and additionally handles HTTP details such as cookies and
// redirects.
type Client struct {
    // Transport specifies the mechanism by which individual
    // HTTP requests are made.
    // If nil, DefaultTransport is used.
    Transport RoundTripper

    // CheckRedirect specifies the policy for handling redirects.
    // If CheckRedirect is not nil, the client calls it before
    // following an HTTP redirect. The arguments req and via are
    // the upcoming request and the requests made already, oldest
    // first. If CheckRedirect returns an error, the Client's Get
    // method returns both the previous Response and
    // CheckRedirect's error (wrapped in a url.Error) instead of
    // issuing the Request req.
    //
    // If CheckRedirect is nil, the Client uses its default policy,
    // which is to stop after 10 consecutive requests.
    CheckRedirect func(req *Request, via []*Request) error

    // Jar specifies the cookie jar.
    // If Jar is nil, cookies are not sent in requests and ignored
    // in responses.
    Jar CookieJar

    // Timeout specifies a time limit for requests made by this
    // Client. The timeout includes connection time, any
    // redirects, and reading the response body. The timer remains
    // running after Get, Head, Post, or Do return and will
    // interrupt reading of the Response.Body.
    //
    // A Timeout of zero means no timeout.
    //
    // The Client's Transport must support the CancelRequest
    // method or Client will return errors when attempting to make
    // a request with Get, Head, Post, or Do. Client's default
    // Transport (DefaultTransport) supports CancelRequest.
    Timeout time.Duration
}

// DefaultClient is the default Client and is used by Get, Head, and Post.
var DefaultClient = &Client{}

// RoundTripper is an interface representing the ability to execute a
// single HTTP transaction, obtaining the Response for a given Request.
//
// A RoundTripper must be safe for concurrent use by multiple
// goroutines.
type RoundTripper interface {
    // RoundTrip executes a single HTTP transaction, returning
    // the Response for the request req.  RoundTrip should not
    // attempt to interpret the response.  In particular,
    // RoundTrip must return err == nil if it obtained a response,
    // regardless of the response's HTTP status code.  A non-nil
    // err should be reserved for failure to obtain a response.
    // Similarly, RoundTrip should not attempt to handle
    // higher-level protocol details such as redirects,
    // authentication, or cookies.
    //
    // RoundTrip should not modify the request, except for
    // consuming and closing the Body, including on errors. The
    // request's URL and Header fields are guaranteed to be
    // initialized.
    RoundTrip(*Request) (*Response, error)
}

// Do sends an HTTP request and returns an HTTP response, following
// policy (e.g. redirects, cookies, auth) as configured on the client.
//
// An error is returned if caused by client policy (such as
// CheckRedirect), or if there was an HTTP protocol error.
// A non-2xx response doesn't cause an error.
//
// When err is nil, resp always contains a non-nil resp.Body.
//
// Callers should close resp.Body when done reading from it. If
// resp.Body is not closed, the Client's underlying RoundTripper
// (typically Transport) may not be able to re-use a persistent TCP
// connection to the server for a subsequent "keep-alive" request.
//
// The request Body, if non-nil, will be closed by the underlying
// Transport, even on errors.
//
// Generally Get, Post, or PostForm will be used instead of Do.
func (c *Client) Do(req *Request) (resp *Response, err error) {
    if req.Method == "GET" || req.Method == "HEAD" {
        return c.doFollowingRedirects(req, shouldRedirectGet)
    }
    if req.Method == "POST" || req.Method == "PUT" {
        return c.doFollowingRedirects(req, shouldRedirectPost)
    }
    return c.send(req)
}

// Get issues a GET to the specified URL. If the response is one of
// the following redirect codes, Get follows the redirect, up to a
// maximum of 10 redirects:
//
//    301 (Moved Permanently)
//    302 (Found)
//    303 (See Other)
//    307 (Temporary Redirect)
//
// An error is returned if there were too many redirects or if there
// was an HTTP protocol error. A non-2xx response doesn't cause an
// error.
//
// When err is nil, resp always contains a non-nil resp.Body.
// Caller should close resp.Body when done reading from it.
//
// Get is a wrapper around DefaultClient.Get.
//
// To make a request with custom headers, use NewRequest and
// DefaultClient.Do.
func Get(url string) (resp *Response, err error) {
    return DefaultClient.Get(url)
}

// Get issues a GET to the specified URL. If the response is one of the
// following redirect codes, Get follows the redirect after calling the
// Client's CheckRedirect function:
//
//    301 (Moved Permanently)
//    302 (Found)
//    303 (See Other)
//    307 (Temporary Redirect)
//
// An error is returned if the Client's CheckRedirect function fails
// or if there was an HTTP protocol error. A non-2xx response doesn't
// cause an error.
//
// When err is nil, resp always contains a non-nil resp.Body.
// Caller should close resp.Body when done reading from it.
//
// To make a request with custom headers, use NewRequest and Client.Do.
func (c *Client) Get(url string) (resp *Response, err error) {
    req, err := NewRequest("GET", url, nil)
    if err != nil {
        return nil, err
    }
    return c.doFollowingRedirects(req, shouldRedirectGet)
}

// Post issues a POST to the specified URL.
//
// Caller should close resp.Body when done reading from it.
//
// If the provided body is an io.Closer, it is closed after the
// request.
//
// Post is a wrapper around DefaultClient.Post.
//
// To set custom headers, use NewRequest and DefaultClient.Do.
func Post(url string, bodyType string, body io.Reader) (resp *Response, err error) {
    return DefaultClient.Post(url, bodyType, body)
}

// Post issues a POST to the specified URL.
//
// Caller should close resp.Body when done reading from it.
//
// If the provided body is an io.Closer, it is closed after the
// request.
//
// To set custom headers, use NewRequest and Client.Do.
func (c *Client) Post(url string, bodyType string, body io.Reader) (resp *Response, err error) {
    req, err := NewRequest("POST", url, body)
    if err != nil {
        return nil, err
    }
    req.Header.Set("Content-Type", bodyType)
    return c.doFollowingRedirects(req, shouldRedirectPost)
}

// PostForm issues a POST to the specified URL, with data's keys and
// values URL-encoded as the request body.
//
// The Content-Type header is set to application/x-www-form-urlencoded.
// To set other headers, use NewRequest and DefaultClient.Do.
//
// When err is nil, resp always contains a non-nil resp.Body.
// Caller should close resp.Body when done reading from it.
//
// PostForm is a wrapper around DefaultClient.PostForm.
func PostForm(url string, data url.Values) (resp *Response, err error) {
    return DefaultClient.PostForm(url, data)
}

// PostForm issues a POST to the specified URL,
// with data's keys and values URL-encoded as the request body.
//
// The Content-Type header is set to application/x-www-form-urlencoded.
// To set other headers, use NewRequest and DefaultClient.Do.
//
// When err is nil, resp always contains a non-nil resp.Body.
// Caller should close resp.Body when done reading from it.
func (c *Client) PostForm(url string, data url.Values) (resp *Response, err error) {
    return c.Post(url, "application/x-www-form-urlencoded", strings.NewReader(data.Encode()))
}

// Head issues a HEAD to the specified URL.  If the response is one of
// the following redirect codes, Head follows the redirect, up to a
// maximum of 10 redirects:
//
//    301 (Moved Permanently)
//    302 (Found)
//    303 (See Other)
//    307 (Temporary Redirect)
//
// Head is a wrapper around DefaultClient.Head
func Head(url string) (resp *Response, err error) {
    return DefaultClient.Head(url)
}

// Head issues a HEAD to the specified URL.  If the response is one of the
// following redirect codes, Head follows the redirect after calling the
// Client's CheckRedirect function:
//
//    301 (Moved Permanently)
//    302 (Found)
//    303 (See Other)
//    307 (Temporary Redirect)
func (c *Client) Head(url string) (resp *Response, err error) {
    req, err := NewRequest("HEAD", url, nil)
    if err != nil {
        return nil, err
    }
    return c.doFollowingRedirects(req, shouldRedirectGet)
}

func (b *cancelTimerBody) Read(p []byte) (n int, err error) {
    n, err = b.rc.Read(p)
    if err == io.EOF {
        b.t.Stop()
    } else if err != nil && b.reqWasCanceled() {
        return n, &httpError{
            err:     err.Error() + " (Client.Timeout exceeded while reading body)",
            timeout: true,
        }
    }
    return
}

func (b *cancelTimerBody) Close() error {
    err := b.rc.Close()
    b.t.Stop()
    return err
}
net/http/cookie.go:
// Copyright 2009 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package http

// A Cookie represents an HTTP cookie as sent in the Set-Cookie header of an
// HTTP response or the Cookie header of an HTTP request.
//
// See http://tools.ietf.org/html/rfc6265 for details.
type Cookie struct {
    Name  string
    Value string

    Path       string    // optional
    Domain     string    // optional
    Expires    time.Time // optional
    RawExpires string    // for reading cookies only

    // MaxAge=0 means no 'Max-Age' attribute specified.
    // MaxAge<0 means delete cookie now, equivalently 'Max-Age: 0'
    // MaxAge>0 means Max-Age attribute present and given in seconds
    MaxAge   int
    Secure   bool
    HttpOnly bool
    Raw      string
    Unparsed []string // Raw text of unparsed attribute-value pairs
}

// SetCookie adds a Set-Cookie header to the provided ResponseWriter's headers.
// The provided cookie must have a valid Name. Invalid cookies may be
// silently dropped.
func SetCookie(w ResponseWriter, cookie *Cookie) {
    if v := cookie.String(); v != "" {
        w.Header().Add("Set-Cookie", v)
    }
}

// String returns the serialization of the cookie for use in a Cookie
// header (if only Name and Value are set) or a Set-Cookie response
// header (if other fields are set).
// If c is nil or c.Name is invalid, the empty string is returned.
func (c *Cookie) String() string {
    if c == nil || !isCookieNameValid(c.Name) {
        return ""
    }
    var b bytes.Buffer
    fmt.Fprintf(&b, "%s=%s", sanitizeCookieName(c.Name), sanitizeCookieValue(c.Value))
    if len(c.Path) > 0 {
        fmt.Fprintf(&b, "; Path=%s", sanitizeCookiePath(c.Path))
    }
    if len(c.Domain) > 0 {
        if validCookieDomain(c.Domain) {
            // A c.Domain containing illegal characters is not
            // sanitized but simply dropped which turns the cookie
            // into a host-only cookie. A leading dot is okay
            // but won't be sent.
            d := c.Domain
            if d[0] == '.' {
                d = d[1:]
            }
            fmt.Fprintf(&b, "; Domain=%s", d)
        } else {
            log.Printf("net/http: invalid Cookie.Domain %q; dropping domain attribute",
                c.Domain)
        }
    }
    if c.Expires.Unix() > 0 {
        fmt.Fprintf(&b, "; Expires=%s", c.Expires.UTC().Format(TimeFormat))
    }
    if c.MaxAge > 0 {
        fmt.Fprintf(&b, "; Max-Age=%d", c.MaxAge)
    } else if c.MaxAge < 0 {
        fmt.Fprintf(&b, "; Max-Age=0")
    }
    if c.HttpOnly {
        fmt.Fprintf(&b, "; HttpOnly")
    }
    if c.Secure {
        fmt.Fprintf(&b, "; Secure")
    }
    return b.String()
}
net/http/doc.go:
// Copyright 2011 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

/*
Package http provides HTTP client and server implementations.

Get, Head, Post, and PostForm make HTTP (or HTTPS) requests:

    resp, err := http.Get("http://example.com/")
    ...
    resp, err := http.Post("http://example.com/upload", "image/jpeg", &buf)
    ...
    resp, err := http.PostForm("http://example.com/form",
        url.Values{"key": {"Value"}, "id": {"123"}})

The client must close the response body when finished with it:

    resp, err := http.Get("http://example.com/")
    if err != nil {
        // handle error
    }
    defer resp.Body.Close()
    body, err := ioutil.ReadAll(resp.Body)
    // ...

For control over HTTP client headers, redirect policy, and other
settings, create a Client:

    client := &http.Client{
        CheckRedirect: redirectPolicyFunc,
    }

    resp, err := client.Get("http://example.com")
    // ...

    req, err := http.NewRequest("GET", "http://example.com", nil)
    // ...
    req.Header.Add("If-None-Match", `W/"wyzzy"`)
    resp, err := client.Do(req)
    // ...

For control over proxies, TLS configuration, keep-alives,
compression, and other settings, create a Transport:

    tr := &http.Transport{
        TLSClientConfig:    &tls.Config{RootCAs: pool},
        DisableCompression: true,
    }
    client := &http.Client{Transport: tr}
    resp, err := client.Get("https://example.com")

Clients and Transports are safe for concurrent use by multiple
goroutines and for efficiency should only be created once and re-used.

ListenAndServe starts an HTTP server with a given address and handler.
The handler is usually nil, which means to use DefaultServeMux.
Handle and HandleFunc add handlers to DefaultServeMux:

    http.Handle("/foo", fooHandler)

    http.HandleFunc("/bar", func(w http.ResponseWriter, r *http.Request) {
        fmt.Fprintf(w, "Hello, %q", html.EscapeString(r.URL.Path))
    })

    log.Fatal(http.ListenAndServe(":8080", nil))

More control over the server's behavior is available by creating a
custom Server:

    s := &http.Server{
        Addr:           ":8080",
        Handler:        myHandler,
        ReadTimeout:    10 * time.Second,
        WriteTimeout:   10 * time.Second,
        MaxHeaderBytes: 1 << 20,
    }
    log.Fatal(s.ListenAndServe())
*/
package http
net/http/filetransport.go:
// Copyright 2011 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package http

// NewFileTransport returns a new RoundTripper, serving the provided
// FileSystem. The returned RoundTripper ignores the URL host in its
// incoming requests, as well as most other properties of the
// request.
//
// The typical use case for NewFileTransport is to register the "file"
// protocol with a Transport, as in:
//
//   t := &http.Transport{}
//   t.RegisterProtocol("file", http.NewFileTransport(http.Dir("/")))
//   c := &http.Client{Transport: t}
//   res, err := c.Get("file:///etc/passwd")
//   ...
func NewFileTransport(fs FileSystem) RoundTripper {
    return fileTransport{fileHandler{fs}}
}

func (t fileTransport) RoundTrip(req *Request) (resp *Response, err error) {
    // We start ServeHTTP in a goroutine, which may take a long
    // time if the file is large.  The newPopulateResponseWriter
    // call returns a channel which either ServeHTTP or finish()
    // sends our *Response on, once the *Response itself has been
    // populated (even if the body itself is still being
    // written to the res.Body, a pipe)
    rw, resc := newPopulateResponseWriter()
    go func() {
        t.fh.ServeHTTP(rw, req)
        rw.finish()
    }()
    return <-resc, nil
}

func (pr *populateResponse) Header() Header {
    return pr.res.Header
}

func (pr *populateResponse) WriteHeader(code int) {
    if pr.wroteHeader {
        return
    }
    pr.wroteHeader = true

    pr.res.StatusCode = code
    pr.res.Status = fmt.Sprintf("%d %s", code, StatusText(code))
}

func (pr *populateResponse) Write(p []byte) (n int, err error) {
    if !pr.wroteHeader {
        pr.WriteHeader(StatusOK)
    }
    pr.hasContent = true
    if !pr.sentResponse {
        pr.sendResponse()
    }
    return pr.pw.Write(p)
}
net/http/fs.go:
// Copyright 2009 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// HTTP file system request handler

package http

// A Dir implements FileSystem using the native file system restricted to a
// specific directory tree.
//
// While the FileSystem.Open method takes '/'-separated paths, a Dir's string
// value is a filename on the native file system, not a URL, so it is separated
// by filepath.Separator, which isn't necessarily '/'.
//
// An empty Dir is treated as ".".
type Dir string

func (d Dir) Open(name string) (File, error) {
    if filepath.Separator != '/' && strings.IndexRune(name, filepath.Separator) >= 0 ||
        strings.Contains(name, "\x00") {
        return nil, errors.New("http: invalid character in file path")
    }
    dir := string(d)
    if dir == "" {
        dir = "."
    }
    f, err := os.Open(filepath.Join(dir, filepath.FromSlash(path.Clean("/"+name))))
    if err != nil {
        return nil, err
    }
    return f, nil
}

// A FileSystem implements access to a collection of named files.
// The elements in a file path are separated by slash ('/', U+002F)
// characters, regardless of host operating system convention.
type FileSystem interface {
    Open(name string) (File, error)
}

// A File is returned by a FileSystem's Open method and can be
// served by the FileServer implementation.
//
// The methods should behave the same as those on an *os.File.
type File interface {
    io.Closer
    io.Reader
    Readdir(count int) ([]os.FileInfo, error)
    Seek(offset int64, whence int) (int64, error)
    Stat() (os.FileInfo, error)
}

// ServeContent replies to the request using the content in the
// provided ReadSeeker.  The main benefit of ServeContent over io.Copy
// is that it handles Range requests properly, sets the MIME type, and
// handles If-Modified-Since requests.
//
// If the response's Content-Type header is not set, ServeContent
// first tries to deduce the type from name's file extension and,
// if that fails, falls back to reading the first block of the content
// and passing it to DetectContentType.
// The name is otherwise unused; in particular it can be empty and is
// never sent in the response.
//
// If modtime is not the zero time or Unix epoch, ServeContent
// includes it in a Last-Modified header in the response.  If the
// request includes an If-Modified-Since header, ServeContent uses
// modtime to decide whether the content needs to be sent at all.
//
// The content's Seek method must work: ServeContent uses
// a seek to the end of the content to determine its size.
//
// If the caller has set w's ETag header, ServeContent uses it to
// handle requests using If-Range and If-None-Match.
//
// Note that *os.File implements the io.ReadSeeker interface.
func ServeContent(w ResponseWriter, req *Request, name string, modtime time.Time, content io.ReadSeeker) {
    sizeFunc := func() (int64, error) {
        size, err := content.Seek(0, os.SEEK_END)
        if err != nil {
            return 0, errSeeker
        }
        _, err = content.Seek(0, os.SEEK_SET)
        if err != nil {
            return 0, errSeeker
        }
        return size, nil
    }
    serveContent(w, req, name, modtime, sizeFunc, content)
}

// ServeFile replies to the request with the contents of the named
// file or directory.
//
// As a special case, ServeFile redirects any request where r.URL.Path
// ends in "/index.html" to the same path, without the final
// "index.html". To avoid such redirects either modify the path or
// use ServeContent.
func ServeFile(w ResponseWriter, r *Request, name string) {
    dir, file := filepath.Split(name)
    serveFile(w, r, Dir(dir), file, false)
}

// FileServer returns a handler that serves HTTP requests
// with the contents of the file system rooted at root.
//
// To use the operating system's file system implementation,
// use http.Dir:
//
//     http.Handle("/", http.FileServer(http.Dir("/tmp")))
//
// As a special case, the returned file server redirects any request
// ending in "/index.html" to the same path, without the final
// "index.html".
func FileServer(root FileSystem) Handler {
    return &fileHandler{root}
}

func (f *fileHandler) ServeHTTP(w ResponseWriter, r *Request) {
    upath := r.URL.Path
    if !strings.HasPrefix(upath, "/") {
        upath = "/" + upath
        r.URL.Path = upath
    }
    serveFile(w, r, f.root, path.Clean(upath), true)
}

func (w *countingWriter) Write(p []byte) (n int, err error) {
    *w += countingWriter(len(p))
    return len(p), nil
}
net/http/header.go:
// Copyright 2010 The Go Authors.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package http

// A Header represents the key-value pairs in an HTTP header.
type Header map[string][]string

// Add adds the key, value pair to the header.
// It appends to any existing values associated with key.
func (h Header) Add(key, value string) {
    textproto.MIMEHeader(h).Add(key, value)
}

// Set sets the header entries associated with key to
// the single element value.  It replaces any existing
// values associated with key.
func (h Header) Set(key, value string) {
    textproto.MIMEHeader(h).Set(key, value)
}

// Get gets the first value associated with the given key.
// If there are no values associated with the key, Get returns "".
// To access multiple values of a key, access the map directly
// with CanonicalHeaderKey.
func (h Header) Get(key string) string {
    return textproto.MIMEHeader(h).Get(key)
}

// Del deletes the values associated with key.
func (h Header) Del(key string) {
    textproto.MIMEHeader(h).Del(key)
}

// Write writes a header in wire format.
func (h Header) Write(w io.Writer) error {
    return h.WriteSubset(w, nil)
}

// ParseTime parses a time header (such as the Date: header),
// trying each of the three formats allowed by HTTP/1.1:
// TimeFormat, time.RFC850, and time.ANSIC.
func ParseTime(text string) (t time.Time, err error) {
    for _, layout := range timeFormats {
        t, err = time.Parse(layout, text)
        if err == nil {
            return
        }
    }
    return
}

func (w stringWriter) WriteString(s string) (n int, err error) {
    return w.w.Write([]byte(s))
}

func (s *headerSorter) Len() int           { return len(s.kvs) }
func (s *headerSorter) Swap(i, j int)      { s.kvs[i], s.kvs[j] = s.kvs[j], s.kvs[i] }
func (s *headerSorter) Less(i, j int) bool { return s.kvs[i].key < s.kvs[j].key }

// WriteSubset writes a header in wire format.
// If exclude is not nil, keys where exclude[key] == true are not written.
func (h Header) WriteSubset(w io.Writer, exclude map[string]bool) error {
    ws, ok := w.(writeStringer)
    if !ok {
        ws = stringWriter{w}
    }
    kvs, sorter := h.sortedKeyValues(exclude)
    for _, kv := range kvs {
        for _, v := range kv.values {
            v = headerNewlineToSpace.Replace(v)
            v = textproto.TrimString(v)
            for _, s := range []string{kv.key, ": ", v, "\r\n"} {
                if _, err := ws.WriteString(s); err != nil {
                    return err
                }
            }
        }
    }
    headerSorterPool.Put(sorter)
    return nil
}

// CanonicalHeaderKey returns the canonical format of the
// header key s.  The canonicalization converts the first
// letter and any letter following a hyphen to upper case;
// the rest are converted to lowercase.  For example, the
// canonical key for "accept-encoding" is "Accept-Encoding".
// If s contains a space or invalid header field bytes, it is
// returned without modifications.
func CanonicalHeaderKey(s string) string { return textproto.CanonicalMIMEHeaderKey(s) }
net/http/jar.go:
// Copyright 2011 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package http

// A CookieJar manages storage and use of cookies in HTTP requests.
//
// Implementations of CookieJar must be safe for concurrent use by multiple
// goroutines.
//
// The net/http/cookiejar package provides a CookieJar implementation.
type CookieJar interface {
    // SetCookies handles the receipt of the cookies in a reply for the
    // given URL.  It may or may not choose to save the cookies, depending
    // on the jar's policy and implementation.
    SetCookies(u *url.URL, cookies []*Cookie)

    // Cookies returns the cookies to send in a request for the given URL.
    // It is up to the implementation to honor the standard cookie use
    // restrictions such as in RFC 6265.
    Cookies(u *url.URL) []*Cookie
}
net/http/lex.go:
// Copyright 2009 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package http
net/http/request.go:
// Copyright 2009 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// HTTP Request reading and parsing.

package http

// ErrMissingFile is returned by FormFile when the provided file field name
// is either not present in the request or not a file field.
var ErrMissingFile = errors.New("http: no such file")

// HTTP request parsing errors.
type ProtocolError struct {
    ErrorString string
}

func (err *ProtocolError) Error() string { return err.ErrorString }

var (
    ErrHeaderTooLong        = &ProtocolError{"header too long"}
    ErrShortBody            = &ProtocolError{"entity body too short"}
    ErrNotSupported         = &ProtocolError{"feature not supported"}
    ErrUnexpectedTrailer    = &ProtocolError{"trailer header without chunked transfer encoding"}
    ErrMissingContentLength = &ProtocolError{"missing ContentLength in HEAD response"}
    ErrNotMultipart         = &ProtocolError{"request Content-Type isn't multipart/form-data"}
    ErrMissingBoundary      = &ProtocolError{"no multipart boundary param in Content-Type"}
)

func (e *badStringError) Error() string { return fmt.Sprintf("%s %q", e.what, e.str) }

// A Request represents an HTTP request received by a server
// or to be sent by a client.
//
// The field semantics differ slightly between client and server
// usage. In addition to the notes on the fields below, see the
// documentation for Request.Write and RoundTripper.
type Request struct {
    // Method specifies the HTTP method (GET, POST, PUT, etc.).
    // For client requests an empty string means GET.
    Method string

    // URL specifies either the URI being requested (for server
    // requests) or the URL to access (for client requests).
    //
    // For server requests the URL is parsed from the URI
    // supplied on the Request-Line as stored in RequestURI.  For
    // most requests, fields other than Path and RawQuery will be
    // empty. (See RFC 2616, Section 5.1.2)
    //
    // For client requests, the URL's Host specifies the server to
    // connect to, while the Request's Host field optionally
    // specifies the Host header value to send in the HTTP
    // request.
    URL *url.URL

    // The protocol version for incoming requests.
    // Client requests always use HTTP/1.1.
    Proto      string // "HTTP/1.0"
    ProtoMajor int    // 1
    ProtoMinor int    // 0

    // A header maps request lines to their values.
    // If the header says
    //
    //	accept-encoding: gzip, deflate
    //	Accept-Language: en-us
    //	Connection: keep-alive
    //
    // then
    //
    //	Header = map[string][]string{
    //		"Accept-Encoding": {"gzip, deflate"},
    //		"Accept-Language": {"en-us"},
    //		"Connection": {"keep-alive"},
    //	}
    //
    // HTTP defines that header names are case-insensitive.
    // The request parser implements this by canonicalizing the
    // name, making the first character and any characters
    // following a hyphen uppercase and the rest lowercase.
    //
    // For client requests certain headers are automatically
    // added and may override values in Header.
    //
    // See the documentation for the Request.Write method.
    Header Header

    // Body is the request's body.
    //
    // For client requests a nil body means the request has no
    // body, such as a GET request. The HTTP Client's Transport
    // is responsible for calling the Close method.
    //
    // For server requests the Request Body is always non-nil
    // but will return EOF immediately when no body is present.
    // The Server will close the request body. The ServeHTTP
    // Handler does not need to.
    Body io.ReadCloser

    // ContentLength records the length of the associated content.
    // The value -1 indicates that the length is unknown.
    // Values >= 0 indicate that the given number of bytes may
    // be read from Body.
    // For client requests, a value of 0 means unknown if Body is not nil.
    ContentLength int64

    // TransferEncoding lists the transfer encodings from outermost to
    // innermost. An empty list denotes the "identity" encoding.
    // TransferEncoding can usually be ignored; chunked encoding is
    // automatically added and removed as necessary when sending and
    // receiving requests.
    TransferEncoding []string

    // Close indicates whether to close the connection after
    // replying to this request (for servers) or after sending
    // the request (for clients).
    Close bool

    // For server requests Host specifies the host on which the
    // URL is sought. Per RFC 2616, this is either the value of
    // the "Host" header or the host name given in the URL itself.
    // It may be of the form "host:port".
    //
    // For client requests Host optionally overrides the Host
    // header to send. If empty, the Request.Write method uses
    // the value of URL.Host.
    Host string

    // Form contains the parsed form data, including both the URL
    // field's query parameters and the POST or PUT form data.
    // This field is only available after ParseForm is called.
    // The HTTP client ignores Form and uses Body instead.
    Form url.Values

    // PostForm contains the parsed form data from POST, PATCH,
    // or PUT body parameters.
    //
    // This field is only available after ParseForm is called.
    // The HTTP client ignores PostForm and uses Body instead.
    PostForm url.Values

    // MultipartForm is the parsed multipart form, including file uploads.
    // This field is only available after ParseMultipartForm is called.
    // The HTTP client ignores MultipartForm and uses Body instead.
    MultipartForm *multipart.Form

    // Trailer specifies additional headers that are sent after the request
    // body.
    //
    // For server requests the Trailer map initially contains only the
    // trailer keys, with nil values. (The client declares which trailers it
    // will later send.)  While the handler is reading from Body, it must
    // not reference Trailer. After reading from Body returns EOF, Trailer
    // can be read again and will contain non-nil values, if they were sent
    // by the client.
    //
    // For client requests Trailer must be initialized to a map containing
    // the trailer keys to later send. The values may be nil or their final
    // values. The ContentLength must be 0 or -1, to send a chunked request.
    // After the HTTP request is sent the map values can be updated while
    // the request body is read. Once the body returns EOF, the caller must
    // not mutate Trailer.
    //
    // Few HTTP clients, servers, or proxies support HTTP trailers.
    Trailer Header

    // RemoteAddr allows HTTP servers and other software to record
    // the network address that sent the request, usually for
    // logging. This field is not filled in by ReadRequest and
    // has no defined format. The HTTP server in this package
    // sets RemoteAddr to an "IP:port" address before invoking a
    // handler.
    // This field is ignored by the HTTP client.
    RemoteAddr string

    // RequestURI is the unmodified Request-URI of the
    // Request-Line (RFC 2616, Section 5.1) as sent by the client
    // to a server. Usually the URL field should be used instead.
    // It is an error to set this field in an HTTP client request.
    RequestURI string

    // TLS allows HTTP servers and other software to record
    // information about the TLS connection on which the request
    // was received. This field is not filled in by ReadRequest.
    // The HTTP server in this package sets the field for
    // TLS-enabled connections before invoking a handler;
    // otherwise it leaves the field nil.
    // This field is ignored by the HTTP client.
    TLS *tls.ConnectionState

    // Cancel is an optional channel whose closure indicates that the client
    // request should be regarded as canceled. Not all implementations of
    // RoundTripper may support Cancel.
    //
    // For server requests, this field is not applicable.
    Cancel <-chan struct{}
}

// ProtoAtLeast reports whether the HTTP protocol used
// in the request is at least major.minor.
func (r *Request) ProtoAtLeast(major, minor int) bool {
    return r.ProtoMajor > major ||
        r.ProtoMajor == major && r.ProtoMinor >= minor
}

// UserAgent returns the client's User-Agent, if sent in the request.
func (r *Request) UserAgent() string {
    return r.Header.Get("User-Agent")
}

// Cookies parses and returns the HTTP cookies sent with the request.
func (r *Request) Cookies() []*Cookie {
    return readCookies(r.Header, "")
}

// ErrNoCookie is returned by Request's Cookie method when a cookie is not found.
var ErrNoCookie = errors.New("http: named cookie not present")

// Cookie returns the named cookie provided in the request or
// ErrNoCookie if not found.
func (r *Request) Cookie(name string) (*Cookie, error) {
    for _, c := range readCookies(r.Header, name) {
        return c, nil
    }
    return nil, ErrNoCookie
}

// AddCookie adds a cookie to the request.  Per RFC 6265 section 5.4,
// AddCookie does not attach more than one Cookie header field.  That
// means all cookies, if any, are written into the same line,
// separated by semicolon.
func (r *Request) AddCookie(c *Cookie) {
    s := fmt.Sprintf("%s=%s", sanitizeCookieName(c.Name), sanitizeCookieValue(c.Value))
    if c := r.Header.Get("Cookie"); c != "" {
        r.Header.Set("Cookie", c+"; "+s)
    } else {
        r.Header.Set("Cookie", s)
    }
}

// Referer returns the referring URL, if sent in the request.
//
// Referer is misspelled as in the request itself, a mistake from the
// earliest days of HTTP.  This value can also be fetched from the
// Header map as Header["Referer"]; the benefit of making it available
// as a method is that the compiler can diagnose programs that use the
// alternate (correct English) spelling req.Referrer() but cannot
// diagnose programs that use Header["Referrer"].
func (r *Request) Referer() string {
    return r.Header.Get("Referer")
}

// MultipartReader returns a MIME multipart reader if this is a
// multipart/form-data POST request, else returns nil and an error.
// Use this function instead of ParseMultipartForm to
// process the request body as a stream.
func (r *Request) MultipartReader() (*multipart.Reader, error) {
    if r.MultipartForm == multipartByReader {
        return nil, errors.New("http: MultipartReader called twice")
    }
    if r.MultipartForm != nil {
        return nil, errors.New("http: multipart handled by ParseMultipartForm")
    }
    r.MultipartForm = multipartByReader
    return r.multipartReader()
}

// Write writes an HTTP/1.1 request, which is the header and body, in wire format.
// This method consults the following fields of the request:
//	Host
//	URL
//	Method (defaults to "GET")
//	Header
//	ContentLength
//	TransferEncoding
//	Body
//
// If Body is present, Content-Length is <= 0 and TransferEncoding
// hasn't been set to "identity", Write adds "Transfer-Encoding:
// chunked" to the header. Body is closed after it is sent.
func (r *Request) Write(w io.Writer) error {
    return r.write(w, false, nil)
}

// WriteProxy is like Write but writes the request in the form
// expected by an HTTP proxy.  In particular, WriteProxy writes the
// initial Request-URI line of the request with an absolute URI, per
// section 5.1.2 of RFC 2616, including the scheme and host.
// In either case, WriteProxy also writes a Host header, using
// either r.Host or r.URL.Host.
func (r *Request) WriteProxy(w io.Writer) error {
    return r.write(w, true, nil)
}

// ParseHTTPVersion parses a HTTP version string.
// "HTTP/1.0" returns (1, 0, true).
func ParseHTTPVersion(vers string) (major, minor int, ok bool) {
    const Big = 1000000 // arbitrary upper bound
    switch vers {
    case "HTTP/1.1":
        return 1, 1, true
    case "HTTP/1.0":
        return 1, 0, true
    }
    if !strings.HasPrefix(vers, "HTTP/") {
        return 0, 0, false
    }
    dot := strings.Index(vers, ".")
    if dot < 0 {
        return 0, 0, false
    }
    major, err := strconv.Atoi(vers[5:dot])
    if err != nil || major < 0 || major > Big {
        return 0, 0, false
    }
    minor, err = strconv.Atoi(vers[dot+1:])
    if err != nil || minor < 0 || minor > Big {
        return 0, 0, false
    }
    return major, minor, true
}

// NewRequest returns a new Request given a method, URL, and optional body.
//
// If the provided body is also an io.Closer, the returned
// Request.Body is set to body and will be closed by the Client
// methods Do, Post, and PostForm, and Transport.RoundTrip.
//
// NewRequest returns a Request suitable for use with Client.Do or
// Transport.RoundTrip.
// To create a request for use with testing a Server Handler use either
// ReadRequest or manually update the Request fields. See the Request
// type's documentation for the difference between inbound and outbound
// request fields.
func NewRequest(method, urlStr string, body io.Reader) (*Request, error) {
    u, err := url.Parse(urlStr)
    if err != nil {
        return nil, err
    }
    rc, ok := body.(io.ReadCloser)
    if !ok && body != nil {
        rc = ioutil.NopCloser(body)
    }
    req := &Request{
        Method:     method,
        URL:        u,
        Proto:      "HTTP/1.1",
        ProtoMajor: 1,
        ProtoMinor: 1,
        Header:     make(Header),
        Body:       rc,
        Host:       u.Host,
    }
    if body != nil {
        switch v := body.(type) {
        case *bytes.Buffer:
            req.ContentLength = int64(v.Len())
        case *bytes.Reader:
            req.ContentLength = int64(v.Len())
        case *strings.Reader:
            req.ContentLength = int64(v.Len())
        }
    }

    return req, nil
}

// BasicAuth returns the username and password provided in the request's
// Authorization header, if the request uses HTTP Basic Authentication.
// See RFC 2617, Section 2.
func (r *Request) BasicAuth() (username, password string, ok bool) {
    auth := r.Header.Get("Authorization")
    if auth == "" {
        return
    }
    return parseBasicAuth(auth)
}

// SetBasicAuth sets the request's Authorization header to use HTTP
// Basic Authentication with the provided username and password.
//
// With HTTP Basic Authentication the provided username and password
// are not encrypted.
func (r *Request) SetBasicAuth(username, password string) {
    r.Header.Set("Authorization", "Basic "+basicAuth(username, password))
}

// ReadRequest reads and parses an incoming request from b.
func ReadRequest(b *bufio.Reader) (req *Request, err error) {

    tp := newTextprotoReader(b)
    req = new(Request)

    // First line: GET /index.html HTTP/1.0
    var s string
    if s, err = tp.ReadLine(); err != nil {
        return nil, err
    }
    defer func() {
        putTextprotoReader(tp)
        if err == io.EOF {
            err = io.ErrUnexpectedEOF
        }
    }()

    var ok bool
    req.Method, req.RequestURI, req.Proto, ok = parseRequestLine(s)
    if !ok {
        return nil, &badStringError{"malformed HTTP request", s}
    }
    rawurl := req.RequestURI
    if req.ProtoMajor, req.ProtoMinor, ok = ParseHTTPVersion(req.Proto); !ok {
        return nil, &badStringError{"malformed HTTP version", req.Proto}
    }

    // CONNECT requests are used two different ways, and neither uses a full URL:
    // The standard use is to tunnel HTTPS through an HTTP proxy.
    // It looks like "CONNECT www.google.com:443 HTTP/1.1", and the parameter is
    // just the authority section of a URL. This information should go in req.URL.Host.
    //
    // The net/rpc package also uses CONNECT, but there the parameter is a path
    // that starts with a slash. It can be parsed with the regular URL parser,
    // and the path will end up in req.URL.Path, where it needs to be in order for
    // RPC to work.
    justAuthority := req.Method == "CONNECT" && !strings.HasPrefix(rawurl, "/")
    if justAuthority {
        rawurl = "http://" + rawurl
    }

    if req.URL, err = url.ParseRequestURI(rawurl); err != nil {
        return nil, err
    }

    if justAuthority {
        // Strip the bogus "http://" back off.
        req.URL.Scheme = ""
    }

    // Subsequent lines: Key: value.
    mimeHeader, err := tp.ReadMIMEHeader()
    if err != nil {
        return nil, err
    }
    req.Header = Header(mimeHeader)

    // RFC2616: Must treat
    //	GET /index.html HTTP/1.1
    //	Host: www.google.com
    // and
    //	GET http://www.google.com/index.html HTTP/1.1
    //	Host: doesntmatter
    // the same.  In the second case, any Host line is ignored.
    req.Host = req.URL.Host
    if req.Host == "" {
        req.Host = req.Header.get("Host")
    }
    delete(req.Header, "Host")

    fixPragmaCacheControl(req.Header)

    req.Close = shouldClose(req.ProtoMajor, req.ProtoMinor, req.Header, false)

    err = readTransfer(req, b)
    if err != nil {
        return nil, err
    }

    return req, nil
}

// MaxBytesReader is similar to io.LimitReader but is intended for
// limiting the size of incoming request bodies. In contrast to
// io.LimitReader, MaxBytesReader's result is a ReadCloser, returns a
// non-EOF error for a Read beyond the limit, and closes the
// underlying reader when its Close method is called.
//
// MaxBytesReader prevents clients from accidentally or maliciously
// sending a large request and wasting server resources.
func MaxBytesReader(w ResponseWriter, r io.ReadCloser, n int64) io.ReadCloser {
    return &maxBytesReader{w: w, r: r, n: n}
}

func (l *maxBytesReader) Read(p []byte) (n int, err error) {
    toRead := l.n
    if l.n == 0 {
        if l.sawEOF {
            return l.tooLarge()
        }
        // The underlying io.Reader may not return (0, io.EOF)
        // at EOF if the requested size is 0, so read 1 byte
        // instead. The io.Reader docs are a bit ambiguous
        // about the return value of Read when 0 bytes are
        // requested, and {bytes,strings}.Reader gets it wrong
        // too (it returns (0, nil) even at EOF).
        toRead = 1
    }
    if int64(len(p)) > toRead {
        p = p[:toRead]
    }
    n, err = l.r.Read(p)
    if err == io.EOF {
        l.sawEOF = true
    }
    if l.n == 0 {
        // If we had zero bytes to read remaining (but hadn't seen EOF)
        // and we get a byte here, that means we went over our limit.
        if n > 0 {
            return l.tooLarge()
        }
        return 0, err
    }
    l.n -= int64(n)
    if l.n < 0 {
        l.n = 0
    }
    return
}

func (l *maxBytesReader) Close() error {
    return l.r.Close()
}

// ParseForm parses the raw query from the URL and updates r.Form.
//
// For POST or PUT requests, it also parses the request body as a form and
// put the results into both r.PostForm and r.Form.
// POST and PUT body parameters take precedence over URL query string values
// in r.Form.
//
// If the request Body's size has not already been limited by MaxBytesReader,
// the size is capped at 10MB.
//
// ParseMultipartForm calls ParseForm automatically.
// It is idempotent.
func (r *Request) ParseForm() error {
    var err error
    if r.PostForm == nil {
        if r.Method == "POST" || r.Method == "PUT" || r.Method == "PATCH" {
            r.PostForm, err = parsePostForm(r)
        }
        if r.PostForm == nil {
            r.PostForm = make(url.Values)
        }
    }
    if r.Form == nil {
        if len(r.PostForm) > 0 {
            r.Form = make(url.Values)
            copyValues(r.Form, r.PostForm)
        }
        var newValues url.Values
        if r.URL != nil {
            var e error
            newValues, e = url.ParseQuery(r.URL.RawQuery)
            if err == nil {
                err = e
            }
        }
        if newValues == nil {
            newValues = make(url.Values)
        }
        if r.Form == nil {
            r.Form = newValues
        } else {
            copyValues(r.Form, newValues)
        }
    }
    return err
}

// ParseMultipartForm parses a request body as multipart/form-data.
// The whole request body is parsed and up to a total of maxMemory bytes of
// its file parts are stored in memory, with the remainder stored on
// disk in temporary files.
// ParseMultipartForm calls ParseForm if necessary.
// After one call to ParseMultipartForm, subsequent calls have no effect.
func (r *Request) ParseMultipartForm(maxMemory int64) error {
    if r.MultipartForm == multipartByReader {
        return errors.New("http: multipart handled by MultipartReader")
    }
    if r.Form == nil {
        err := r.ParseForm()
        if err != nil {
            return err
        }
    }
    if r.MultipartForm != nil {
        return nil
    }

    mr, err := r.multipartReader()
    if err != nil {
        return err
    }

    f, err := mr.ReadForm(maxMemory)
    if err != nil {
        return err
    }
    for k, v := range f.Value {
        r.Form[k] = append(r.Form[k], v...)
    }
    r.MultipartForm = f

    return nil
}

// FormValue returns the first value for the named component of the query.
// POST and PUT body parameters take precedence over URL query string values.
// FormValue calls ParseMultipartForm and ParseForm if necessary and ignores
// any errors returned by these functions.
// If key is not present, FormValue returns the empty string.
// To access multiple values of the same key, call ParseForm and
// then inspect Request.Form directly.
func (r *Request) FormValue(key string) string {
    if r.Form == nil {
        r.ParseMultipartForm(defaultMaxMemory)
    }
    if vs := r.Form[key]; len(vs) > 0 {
        return vs[0]
    }
    return ""
}

// PostFormValue returns the first value for the named component of the POST
// or PUT request body. URL query parameters are ignored.
// PostFormValue calls ParseMultipartForm and ParseForm if necessary and ignores
// any errors returned by these functions.
// If key is not present, PostFormValue returns the empty string.
func (r *Request) PostFormValue(key string) string {
    if r.PostForm == nil {
        r.ParseMultipartForm(defaultMaxMemory)
    }
    if vs := r.PostForm[key]; len(vs) > 0 {
        return vs[0]
    }
    return ""
}

// FormFile returns the first file for the provided form key.
// FormFile calls ParseMultipartForm and ParseForm if necessary.
func (r *Request) FormFile(key string) (multipart.File, *multipart.FileHeader, error) {
    if r.MultipartForm == multipartByReader {
        return nil, nil, errors.New("http: multipart handled by MultipartReader")
    }
    if r.MultipartForm == nil {
        err := r.ParseMultipartForm(defaultMaxMemory)
        if err != nil {
            return nil, nil, err
        }
    }
    if r.MultipartForm != nil && r.MultipartForm.File != nil {
        if fhs := r.MultipartForm.File[key]; len(fhs) > 0 {
            f, err := fhs[0].Open()
            return f, fhs[0], err
        }
    }
    return nil, nil, ErrMissingFile
}
net/http/response.go:
// Copyright 2009 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// HTTP Response reading and parsing.

package http

// Response represents the response from an HTTP request.
//
type Response struct {
    Status     string // e.g. "200 OK"
    StatusCode int    // e.g. 200
    Proto      string // e.g. "HTTP/1.0"
    ProtoMajor int    // e.g. 1
    ProtoMinor int    // e.g. 0

    // Header maps header keys to values.  If the response had multiple
    // headers with the same key, they may be concatenated, with comma
    // delimiters.  (Section 4.2 of RFC 2616 requires that multiple headers
    // be semantically equivalent to a comma-delimited sequence.) Values
    // duplicated by other fields in this struct (e.g., ContentLength) are
    // omitted from Header.
    //
    // Keys in the map are canonicalized (see CanonicalHeaderKey).
    Header Header

    // Body represents the response body.
    //
    // The http Client and Transport guarantee that Body is always
    // non-nil, even on responses without a body or responses with
    // a zero-length body. It is the caller's responsibility to
    // close Body. The default HTTP client's Transport does not
    // attempt to reuse HTTP/1.0 or HTTP/1.1 TCP connections
    // ("keep-alive") unless the Body is read to completion and is
    // closed.
    //
    // The Body is automatically dechunked if the server replied
    // with a "chunked" Transfer-Encoding.
    Body io.ReadCloser

    // ContentLength records the length of the associated content.  The
    // value -1 indicates that the length is unknown.  Unless Request.Method
    // is "HEAD", values >= 0 indicate that the given number of bytes may
    // be read from Body.
    ContentLength int64

    // Contains transfer encodings from outer-most to inner-most. Value is
    // nil, means that "identity" encoding is used.
    TransferEncoding []string

    // Close records whether the header directed that the connection be
    // closed after reading Body.  The value is advice for clients: neither
    // ReadResponse nor Response.Write ever closes a connection.
    Close bool

    // Trailer maps trailer keys to values, in the same
    // format as the header.
    Trailer Header

    // The Request that was sent to obtain this Response.
    // Request's Body is nil (having already been consumed).
    // This is only populated for Client requests.
    Request *Request

    // TLS contains information about the TLS connection on which the
    // response was received. It is nil for unencrypted responses.
    // The pointer is shared between responses and should not be
    // modified.
    TLS *tls.ConnectionState
}

// Cookies parses and returns the cookies set in the Set-Cookie headers.
func (r *Response) Cookies() []*Cookie {
    return readSetCookies(r.Header)
}

// ErrNoLocation is returned by Response's Location method
// when no Location header is present.
var ErrNoLocation = errors.New("http: no Location header in response")

// Location returns the URL of the response's "Location" header,
// if present.  Relative redirects are resolved relative to
// the Response's Request.  ErrNoLocation is returned if no
// Location header is present.
func (r *Response) Location() (*url.URL, error) {
    lv := r.Header.Get("Location")
    if lv == "" {
        return nil, ErrNoLocation
    }
    if r.Request != nil && r.Request.URL != nil {
        return r.Request.URL.Parse(lv)
    }
    return url.Parse(lv)
}

// ReadResponse reads and returns an HTTP response from r.
// The req parameter optionally specifies the Request that corresponds
// to this Response. If nil, a GET request is assumed.
// Clients must call resp.Body.Close when finished reading resp.Body.
// After that call, clients can inspect resp.Trailer to find key/value
// pairs included in the response trailer.
func ReadResponse(r *bufio.Reader, req *Request) (*Response, error) {
    tp := textproto.NewReader(r)
    resp := &Response{
        Request: req,
    }

    // Parse the first line of the response.
    line, err := tp.ReadLine()
    if err != nil {
        if err == io.EOF {
            err = io.ErrUnexpectedEOF
        }
        return nil, err
    }
    f := strings.SplitN(line, " ", 3)
    if len(f) < 2 {
        return nil, &badStringError{"malformed HTTP response", line}
    }
    reasonPhrase := ""
    if len(f) > 2 {
        reasonPhrase = f[2]
    }
    resp.Status = f[1] + " " + reasonPhrase
    resp.StatusCode, err = strconv.Atoi(f[1])
    if err != nil {
        return nil, &badStringError{"malformed HTTP status code", f[1]}
    }

    resp.Proto = f[0]
    var ok bool
    if resp.ProtoMajor, resp.ProtoMinor, ok = ParseHTTPVersion(resp.Proto); !ok {
        return nil, &badStringError{"malformed HTTP version", resp.Proto}
    }

    // Parse the response headers.
    mimeHeader, err := tp.ReadMIMEHeader()
    if err != nil {
        if err == io.EOF {
            err = io.ErrUnexpectedEOF
        }
        return nil, err
    }
    resp.Header = Header(mimeHeader)

    fixPragmaCacheControl(resp.Header)

    err = readTransfer(resp, r)
    if err != nil {
        return nil, err
    }

    return resp, nil
}

// ProtoAtLeast reports whether the HTTP protocol used
// in the response is at least major.minor.
func (r *Response) ProtoAtLeast(major, minor int) bool {
    return r.ProtoMajor > major ||
        r.ProtoMajor == major && r.ProtoMinor >= minor
}

// Write writes r to w in the HTTP/1.n server response format,
// including the status line, headers, body, and optional trailer.
//
// This method consults the following fields of the response r:
//
//  StatusCode
//  ProtoMajor
//  ProtoMinor
//  Request.Method
//  TransferEncoding
//  Trailer
//  Body
//  ContentLength
//  Header, values for non-canonical keys will have unpredictable behavior
//
// The Response Body is closed after it is sent.
func (r *Response) Write(w io.Writer) error {
    // Status line
    text := r.Status
    if text == "" {
        var ok bool
        text, ok = statusText[r.StatusCode]
        if !ok {
            text = "status code " + strconv.Itoa(r.StatusCode)
        }
    }
    protoMajor, protoMinor := strconv.Itoa(r.ProtoMajor), strconv.Itoa(r.ProtoMinor)
    statusCode := strconv.Itoa(r.StatusCode) + " "
    text = strings.TrimPrefix(text, statusCode)
    if _, err := io.WriteString(w, "HTTP/"+protoMajor+"."+protoMinor+" "+statusCode+text+"\r\n"); err != nil {
        return err
    }

    // Clone it, so we can modify r1 as needed.
    r1 := new(Response)
    *r1 = *r
    if r1.ContentLength == 0 && r1.Body != nil {
        // Is it actually 0 length? Or just unknown?
        var buf [1]byte
        n, err := r1.Body.Read(buf[:])
        if err != nil && err != io.EOF {
            return err
        }
        if n == 0 {
            // Reset it to a known zero reader, in case underlying one
            // is unhappy being read repeatedly.
            r1.Body = eofReader
        } else {
            r1.ContentLength = -1
            r1.Body = struct {
                io.Reader
                io.Closer
            }{
                io.MultiReader(bytes.NewReader(buf[:1]), r.Body),
                r.Body,
            }
        }
    }
    // If we're sending a non-chunked HTTP/1.1 response without a
    // content-length, the only way to do that is the old HTTP/1.0
    // way, by noting the EOF with a connection close, so we need
    // to set Close.
    if r1.ContentLength == -1 && !r1.Close && r1.ProtoAtLeast(1, 1) && !chunked(r1.TransferEncoding) {
        r1.Close = true
    }

    // Process Body,ContentLength,Close,Trailer
    tw, err := newTransferWriter(r1)
    if err != nil {
        return err
    }
    err = tw.WriteHeader(w)
    if err != nil {
        return err
    }

    // Rest of header
    err = r.Header.WriteSubset(w, respExcludeHeader)
    if err != nil {
        return err
    }

    // contentLengthAlreadySent may have been already sent for
    // POST/PUT requests, even if zero length. See Issue 8180.
    contentLengthAlreadySent := tw.shouldSendContentLength()
    if r1.ContentLength == 0 && !chunked(r1.TransferEncoding) && !contentLengthAlreadySent {
        if _, err := io.WriteString(w, "Content-Length: 0\r\n"); err != nil {
            return err
        }
    }

    // End-of-header
    if _, err := io.WriteString(w, "\r\n"); err != nil {
        return err
    }

    // Write body and trailer
    err = tw.WriteBody(w)
    if err != nil {
        return err
    }

    // Success
    return nil
}
net/http/server.go:
// Copyright 2009 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// HTTP server.  See RFC 2616.

package http

// Errors introduced by the HTTP server.
var (
    ErrWriteAfterFlush = errors.New("Conn.Write called after Flush")
    ErrBodyNotAllowed  = errors.New("http: request method or response status code does not allow body")
    ErrHijacked        = errors.New("Conn has been hijacked")
    ErrContentLength   = errors.New("Conn.Write wrote more than the declared Content-Length")
)

// Objects implementing the Handler interface can be
// registered to serve a particular path or subtree
// in the HTTP server.
//
// ServeHTTP should write reply headers and data to the ResponseWriter
// and then return.  Returning signals that the request is finished
// and that the HTTP server can move on to the next request on
// the connection.
//
// If ServeHTTP panics, the server (the caller of ServeHTTP) assumes
// that the effect of the panic was isolated to the active request.
// It recovers the panic, logs a stack trace to the server error log,
// and hangs up the connection.
//
type Handler interface {
    ServeHTTP(ResponseWriter, *Request)
}

// A ResponseWriter interface is used by an HTTP handler to
// construct an HTTP response.
type ResponseWriter interface {
    // Header returns the header map that will be sent by
    // WriteHeader. Changing the header after a call to
    // WriteHeader (or Write) has no effect unless the modified
    // headers were declared as trailers by setting the
    // "Trailer" header before the call to WriteHeader (see example).
    // To suppress implicit response headers, set their value to nil.
    Header() Header

    // Write writes the data to the connection as part of an HTTP reply.
    // If WriteHeader has not yet been called, Write calls WriteHeader(http.StatusOK)
    // before writing the data.  If the Header does not contain a
    // Content-Type line, Write adds a Content-Type set to the result of passing
    // the initial 512 bytes of written data to DetectContentType.
    Write([]byte) (int, error)

    // WriteHeader sends an HTTP response header with status code.
    // If WriteHeader is not called explicitly, the first call to Write
    // will trigger an implicit WriteHeader(http.StatusOK).
    // Thus explicit calls to WriteHeader are mainly used to
    // send error codes.
    WriteHeader(int)
}

// The Flusher interface is implemented by ResponseWriters that allow
// an HTTP handler to flush buffered data to the client.
//
// Note that even for ResponseWriters that support Flush,
// if the client is connected through an HTTP proxy,
// the buffered data may not reach the client until the response
// completes.
type Flusher interface {
    // Flush sends any buffered data to the client.
    Flush()
}

// The Hijacker interface is implemented by ResponseWriters that allow
// an HTTP handler to take over the connection.
type Hijacker interface {
    // Hijack lets the caller take over the connection.
    // After a call to Hijack(), the HTTP server library
    // will not do anything else with the connection.
    //
    // It becomes the caller's responsibility to manage
    // and close the connection.
    //
    // The returned net.Conn may have read or write deadlines
    // already set, depending on the configuration of the
    // Server. It is the caller's responsibility to set
    // or clear those deadlines as needed.
    Hijack() (net.Conn, *bufio.ReadWriter, error)
}

// The CloseNotifier interface is implemented by ResponseWriters which
// allow detecting when the underlying connection has gone away.
//
// This mechanism can be used to cancel long operations on the server
// if the client has disconnected before the response is ready.
type CloseNotifier interface {
    // CloseNotify returns a channel that receives a single value
    // when the client connection has gone away.
    CloseNotify() <-chan bool
}

func (sr *liveSwitchReader) Read(p []byte) (n int, err error) {
    sr.Lock()
    r := sr.r
    sr.Unlock()
    return r.Read(p)
}

func (cw *chunkWriter) Write(p []byte) (n int, err error) {
    if !cw.wroteHeader {
        cw.writeHeader(p)
    }
    if cw.res.req.Method == "HEAD" {
        // Eat writes.
        return len(p), nil
    }
    if cw.chunking {
        _, err = fmt.Fprintf(cw.res.conn.buf, "%x\r\n", len(p))
        if err != nil {
            cw.res.conn.rwc.Close()
            return
        }
    }
    n, err = cw.res.conn.buf.Write(p)
    if cw.chunking && err == nil {
        _, err = cw.res.conn.buf.Write(crlf)
    }
    if err != nil {
        cw.res.conn.rwc.Close()
    }
    return
}

// ReadFrom is here to optimize copying from an *os.File regular file
// to a *net.TCPConn with sendfile.
func (w *response) ReadFrom(src io.Reader) (n int64, err error) {
    // Our underlying w.conn.rwc is usually a *TCPConn (with its
    // own ReadFrom method). If not, or if our src isn't a regular
    // file, just fall back to the normal copy method.
    rf, ok := w.conn.rwc.(io.ReaderFrom)
    regFile, err := srcIsRegularFile(src)
    if err != nil {
        return 0, err
    }
    if !ok || !regFile {
        return io.Copy(writerOnly{w}, src)
    }

    // sendfile path:

    if !w.wroteHeader {
        w.WriteHeader(StatusOK)
    }

    if w.needsSniff() {
        n0, err := io.Copy(writerOnly{w}, io.LimitReader(src, sniffLen))
        n += n0
        if err != nil {
            return n, err
        }
    }

    w.w.Flush()  // get rid of any previous writes
    w.cw.flush() // make sure Header is written; flush data to rwc

    // Now that cw has been flushed, its chunking field is guaranteed initialized.
    if !w.cw.chunking && w.bodyAllowed() {
        n0, err := rf.ReadFrom(src)
        n += n0
        w.written += n0
        return n, err
    }

    n0, err := io.Copy(writerOnly{w}, src)
    n += n0
    return n, err
}

// DefaultMaxHeaderBytes is the maximum permitted size of the headers
// in an HTTP request.
// This can be overridden by setting Server.MaxHeaderBytes.
const DefaultMaxHeaderBytes = 1 << 20 // 1 MB

func (ecr *expectContinueReader) Read(p []byte) (n int, err error) {
    if ecr.closed {
        return 0, ErrBodyReadAfterClose
    }
    if !ecr.resp.wroteContinue && !ecr.resp.conn.hijacked() {
        ecr.resp.wroteContinue = true
        ecr.resp.conn.buf.WriteString("HTTP/1.1 100 Continue\r\n\r\n")
        ecr.resp.conn.buf.Flush()
    }
    n, err = ecr.readCloser.Read(p)
    if err == io.EOF {
        ecr.sawEOF = true
    }
    return
}

func (ecr *expectContinueReader) Close() error {
    ecr.closed = true
    return ecr.readCloser.Close()
}

// TimeFormat is the time format to use with
// time.Parse and time.Time.Format when parsing
// or generating times in HTTP headers.
// It is like time.RFC1123 but hard codes GMT as the time zone.
const TimeFormat = "Mon, 02 Jan 2006 15:04:05 GMT"

func (w *response) Header() Header {
    if w.cw.header == nil && w.wroteHeader && !w.cw.wroteHeader {
        // Accessing the header between logically writing it
        // and physically writing it means we need to allocate
        // a clone to snapshot the logically written state.
        w.cw.header = w.handlerHeader.clone()
    }
    w.calledHeader = true
    return w.handlerHeader
}

func (w *response) WriteHeader(code int) {
    if w.conn.hijacked() {
        w.conn.server.logf("http: response.WriteHeader on hijacked connection")
        return
    }
    if w.wroteHeader {
        w.conn.server.logf("http: multiple response.WriteHeader calls")
        return
    }
    w.wroteHeader = true
    w.status = code

    if w.calledHeader && w.cw.header == nil {
        w.cw.header = w.handlerHeader.clone()
    }

    if cl := w.handlerHeader.get("Content-Length"); cl != "" {
        v, err := strconv.ParseInt(cl, 10, 64)
        if err == nil && v >= 0 {
            w.contentLength = v
        } else {
            w.conn.server.logf("http: invalid Content-Length of %q", cl)
            w.handlerHeader.Del("Content-Length")
        }
    }
}

// Write writes the headers described in h to w.
//
// This method has a value receiver, despite the somewhat large size
// of h, because it prevents an allocation. The escape analysis isn't
// smart enough to realize this function doesn't mutate h.
func (h extraHeader) Write(w *bufio.Writer) {
    if h.date != nil {
        w.Write(headerDate)
        w.Write(h.date)
        w.Write(crlf)
    }
    if h.contentLength != nil {
        w.Write(headerContentLength)
        w.Write(h.contentLength)
        w.Write(crlf)
    }
    for i, v := range []string{h.contentType, h.connection, h.transferEncoding} {
        if v != "" {
            w.Write(extraHeaderKeys[i])
            w.Write(colonSpace)
            w.WriteString(v)
            w.Write(crlf)
        }
    }
}

// The Life Of A Write is like this:
//
// Handler starts. No header has been sent. The handler can either
// write a header, or just start writing.  Writing before sending a header
// sends an implicitly empty 200 OK header.
//
// If the handler didn't declare a Content-Length up front, we either
// go into chunking mode or, if the handler finishes running before
// the chunking buffer size, we compute a Content-Length and send that
// in the header instead.
//
// Likewise, if the handler didn't set a Content-Type, we sniff that
// from the initial chunk of output.
//
// The Writers are wired together like:
//
// 1. *response (the ResponseWriter) ->
// 2. (*response).w, a *bufio.Writer of bufferBeforeChunkingSize bytes
// 3. chunkWriter.Writer (whose writeHeader finalizes Content-Length/Type)
//    and which writes the chunk headers, if needed.
// 4. conn.buf, a bufio.Writer of default (4kB) bytes, writing to ->
// 5. checkConnErrorWriter{c}, which notes any non-nil error on Write
//    and populates c.werr with it if so. but otherwise writes to:
// 6. the rwc, the net.Conn.
//
// TODO(bradfitz): short-circuit some of the buffering when the
// initial header contains both a Content-Type and Content-Length.
// Also short-circuit in (1) when the header's been sent and not in
// chunking mode, writing directly to (4) instead, if (2) has no
// buffered data.  More generally, we could short-circuit from (1) to
// (3) even in chunking mode if the write size from (1) is over some
// threshold and nothing is in (2).  The answer might be mostly making
// bufferBeforeChunkingSize smaller and having bufio's fast-paths deal
// with this instead.
func (w *response) Write(data []byte) (n int, err error) {
    return w.write(len(data), data, "")
}

func (w *response) WriteString(data string) (n int, err error) {
    return w.write(len(data), nil, data)
}

func (w *response) Flush() {
    if !w.wroteHeader {
        w.WriteHeader(StatusOK)
    }
    w.w.Flush()
    w.cw.flush()
}

// Hijack implements the Hijacker.Hijack method. Our response is both a ResponseWriter
// and a Hijacker.
func (w *response) Hijack() (rwc net.Conn, buf *bufio.ReadWriter, err error) {
    if w.wroteHeader {
        w.cw.flush()
    }
    // Release the bufioWriter that writes to the chunk writer, it is not
    // used after a connection has been hijacked.
    rwc, buf, err = w.conn.hijack()
    if err == nil {
        putBufioWriter(w.w)
        w.w = nil
    }
    return rwc, buf, err
}

func (w *response) CloseNotify() <-chan bool {
    return w.conn.closeNotify()
}

// The HandlerFunc type is an adapter to allow the use of
// ordinary functions as HTTP handlers.  If f is a function
// with the appropriate signature, HandlerFunc(f) is a
// Handler object that calls f.
type HandlerFunc func(ResponseWriter, *Request)

// ServeHTTP calls f(w, r).
func (f HandlerFunc) ServeHTTP(w ResponseWriter, r *Request) {
    f(w, r)
}

// Helper handlers

// Error replies to the request with the specified error message and HTTP code.
// The error message should be plain text.
func Error(w ResponseWriter, error string, code int) {
    w.Header().Set("Content-Type", "text/plain; charset=utf-8")
    w.Header().Set("X-Content-Type-Options", "nosniff")
    w.WriteHeader(code)
    fmt.Fprintln(w, error)
}

// NotFound replies to the request with an HTTP 404 not found error.
func NotFound(w ResponseWriter, r *Request) { Error(w, "404 page not found", StatusNotFound) }

// NotFoundHandler returns a simple request handler
// that replies to each request with a ``404 page not found'' reply.
func NotFoundHandler() Handler { return HandlerFunc(NotFound) }

// StripPrefix returns a handler that serves HTTP requests
// by removing the given prefix from the request URL's Path
// and invoking the handler h. StripPrefix handles a
// request for a path that doesn't begin with prefix by
// replying with an HTTP 404 not found error.
func StripPrefix(prefix string, h Handler) Handler {
    if prefix == "" {
        return h
    }
    return HandlerFunc(func(w ResponseWriter, r *Request) {
        if p := strings.TrimPrefix(r.URL.Path, prefix); len(p) < len(r.URL.Path) {
            r.URL.Path = p
            h.ServeHTTP(w, r)
        } else {
            NotFound(w, r)
        }
    })
}

// Redirect replies to the request with a redirect to url,
// which may be a path relative to the request path.
func Redirect(w ResponseWriter, r *Request, urlStr string, code int) {
    if u, err := url.Parse(urlStr); err == nil {
        // If url was relative, make absolute by
        // combining with request path.
        // The browser would probably do this for us,
        // but doing it ourselves is more reliable.

        // NOTE(rsc): RFC 2616 says that the Location
        // line must be an absolute URI, like
        // "http://www.google.com/redirect/",
        // not a path like "/redirect/".
        // Unfortunately, we don't know what to
        // put in the host name section to get the
        // client to connect to us again, so we can't
        // know the right absolute URI to send back.
        // Because of this problem, no one pays attention
        // to the RFC; they all send back just a new path.
        // So do we.
        oldpath := r.URL.Path
        if oldpath == "" { // should not happen, but avoid a crash if it does
            oldpath = "/"
        }
        if u.Scheme == "" {
            // no leading http://server
            if urlStr == "" || urlStr[0] != '/' {
                // make relative path absolute
                olddir, _ := path.Split(oldpath)
                urlStr = olddir + urlStr
            }

            var query string
            if i := strings.Index(urlStr, "?"); i != -1 {
                urlStr, query = urlStr[:i], urlStr[i:]
            }

            // clean up but preserve trailing slash
            trailing := strings.HasSuffix(urlStr, "/")
            urlStr = path.Clean(urlStr)
            if trailing && !strings.HasSuffix(urlStr, "/") {
                urlStr += "/"
            }
            urlStr += query
        }
    }

    w.Header().Set("Location", urlStr)
    w.WriteHeader(code)

    // RFC2616 recommends that a short note "SHOULD" be included in the
    // response because older user agents may not understand 301/307.
    // Shouldn't send the response for POST or HEAD; that leaves GET.
    if r.Method == "GET" {
        note := "<a href=\"" + htmlEscape(urlStr) + "\">" + statusText[code] + "</a>.\n"
        fmt.Fprintln(w, note)
    }
}

func (rh *redirectHandler) ServeHTTP(w ResponseWriter, r *Request) {
    Redirect(w, r, rh.url, rh.code)
}

// RedirectHandler returns a request handler that redirects
// each request it receives to the given url using the given
// status code.
func RedirectHandler(url string, code int) Handler {
    return &redirectHandler{url, code}
}

// ServeMux is an HTTP request multiplexer.
// It matches the URL of each incoming request against a list of registered
// patterns and calls the handler for the pattern that
// most closely matches the URL.
//
// Patterns name fixed, rooted paths, like "/favicon.ico",
// or rooted subtrees, like "/images/" (note the trailing slash).
// Longer patterns take precedence over shorter ones, so that
// if there are handlers registered for both "/images/"
// and "/images/thumbnails/", the latter handler will be
// called for paths beginning "/images/thumbnails/" and the
// former will receive requests for any other paths in the
// "/images/" subtree.
//
// Note that since a pattern ending in a slash names a rooted subtree,
// the pattern "/" matches all paths not matched by other registered
// patterns, not just the URL with Path == "/".
//
// Patterns may optionally begin with a host name, restricting matches to
// URLs on that host only.  Host-specific patterns take precedence over
// general patterns, so that a handler might register for the two patterns
// "/codesearch" and "codesearch.google.com/" without also taking over
// requests for "http://www.google.com/".
//
// ServeMux also takes care of sanitizing the URL request path,
// redirecting any request containing . or .. elements to an
// equivalent .- and ..-free URL.
type ServeMux struct {

}

// NewServeMux allocates and returns a new ServeMux.
func NewServeMux() *ServeMux { return &ServeMux{m: make(map[string]muxEntry)} }

// DefaultServeMux is the default ServeMux used by Serve.
var DefaultServeMux = NewServeMux()

// Handler returns the handler to use for the given request,
// consulting r.Method, r.Host, and r.URL.Path. It always returns
// a non-nil handler. If the path is not in its canonical form, the
// handler will be an internally-generated handler that redirects
// to the canonical path.
//
// Handler also returns the registered pattern that matches the
// request or, in the case of internally-generated redirects,
// the pattern that will match after following the redirect.
//
// If there is no registered handler that applies to the request,
// Handler returns a ``page not found'' handler and an empty pattern.
func (mux *ServeMux) Handler(r *Request) (h Handler, pattern string) {
    if r.Method != "CONNECT" {
        if p := cleanPath(r.URL.Path); p != r.URL.Path {
            _, pattern = mux.handler(r.Host, p)
            url := *r.URL
            url.Path = p
            return RedirectHandler(url.String(), StatusMovedPermanently), pattern
        }
    }

    return mux.handler(r.Host, r.URL.Path)
}

// ServeHTTP dispatches the request to the handler whose
// pattern most closely matches the request URL.
func (mux *ServeMux) ServeHTTP(w ResponseWriter, r *Request) {
    if r.RequestURI == "*" {
        if r.ProtoAtLeast(1, 1) {
            w.Header().Set("Connection", "close")
        }
        w.WriteHeader(StatusBadRequest)
        return
    }
    h, _ := mux.Handler(r)
    h.ServeHTTP(w, r)
}

// Handle registers the handler for the given pattern.
// If a handler already exists for pattern, Handle panics.
func (mux *ServeMux) Handle(pattern string, handler Handler) {
    mux.mu.Lock()
    defer mux.mu.Unlock()

    if pattern == "" {
        panic("http: invalid pattern " + pattern)
    }
    if handler == nil {
        panic("http: nil handler")
    }
    if mux.m[pattern].explicit {
        panic("http: multiple registrations for " + pattern)
    }

    mux.m[pattern] = muxEntry{explicit: true, h: handler, pattern: pattern}

    if pattern[0] != '/' {
        mux.hosts = true
    }

    // Helpful behavior:
    // If pattern is /tree/, insert an implicit permanent redirect for /tree.
    // It can be overridden by an explicit registration.
    n := len(pattern)
    if n > 0 && pattern[n-1] == '/' && !mux.m[pattern[0:n-1]].explicit {
        // If pattern contains a host name, strip it and use remaining
        // path for redirect.
        path := pattern
        if pattern[0] != '/' {
            // In pattern, at least the last character is a '/', so
            // strings.Index can't be -1.
            path = pattern[strings.Index(pattern, "/"):]
        }
        url := &url.URL{Path: path}
        mux.m[pattern[0:n-1]] = muxEntry{h: RedirectHandler(url.String(), StatusMovedPermanently), pattern: pattern}
    }
}

// HandleFunc registers the handler function for the given pattern.
func (mux *ServeMux) HandleFunc(pattern string, handler func(ResponseWriter, *Request)) {
    mux.Handle(pattern, HandlerFunc(handler))
}

// Handle registers the handler for the given pattern
// in the DefaultServeMux.
// The documentation for ServeMux explains how patterns are matched.
func Handle(pattern string, handler Handler) { DefaultServeMux.Handle(pattern, handler) }

// HandleFunc registers the handler function for the given pattern
// in the DefaultServeMux.
// The documentation for ServeMux explains how patterns are matched.
func HandleFunc(pattern string, handler func(ResponseWriter, *Request)) {
    DefaultServeMux.HandleFunc(pattern, handler)
}

// Serve accepts incoming HTTP connections on the listener l,
// creating a new service goroutine for each.  The service goroutines
// read requests and then call handler to reply to them.
// Handler is typically nil, in which case the DefaultServeMux is used.
func Serve(l net.Listener, handler Handler) error {
    srv := &Server{Handler: handler}
    return srv.Serve(l)
}

// A Server defines parameters for running an HTTP server.
// The zero value for Server is a valid configuration.
type Server struct {
    Addr           string        // TCP address to listen on, ":http" if empty
    Handler        Handler       // handler to invoke, http.DefaultServeMux if nil
    ReadTimeout    time.Duration // maximum duration before timing out read of the request
    WriteTimeout   time.Duration // maximum duration before timing out write of the response
    MaxHeaderBytes int           // maximum size of request headers, DefaultMaxHeaderBytes if 0
    TLSConfig      *tls.Config   // optional TLS config, used by ListenAndServeTLS

    // TLSNextProto optionally specifies a function to take over
    // ownership of the provided TLS connection when an NPN
    // protocol upgrade has occurred.  The map key is the protocol
    // name negotiated. The Handler argument should be used to
    // handle HTTP requests and will initialize the Request's TLS
    // and RemoteAddr if not already set.  The connection is
    // automatically closed when the function returns.
    TLSNextProto map[string]func(*Server, *tls.Conn, Handler)

    // ConnState specifies an optional callback function that is
    // called when a client connection changes state. See the
    // ConnState type and associated constants for details.
    ConnState func(net.Conn, ConnState)

    // ErrorLog specifies an optional logger for errors accepting
    // connections and unexpected behavior from handlers.
    // If nil, logging goes to os.Stderr via the log package's
    // standard logger.
    ErrorLog *log.Logger

}

// A ConnState represents the state of a client connection to a server.
// It's used by the optional Server.ConnState hook.
type ConnState int

const (
    // StateNew represents a new connection that is expected to
    // send a request immediately. Connections begin at this
    // state and then transition to either StateActive or
    // StateClosed.
    StateNew ConnState = iota

    // StateActive represents a connection that has read 1 or more
    // bytes of a request. The Server.ConnState hook for
    // StateActive fires before the request has entered a handler
    // and doesn't fire again until the request has been
    // handled. After the request is handled, the state
    // transitions to StateClosed, StateHijacked, or StateIdle.
    StateActive

    // StateIdle represents a connection that has finished
    // handling a request and is in the keep-alive state, waiting
    // for a new request. Connections transition from StateIdle
    // to either StateActive or StateClosed.
    StateIdle

    // StateHijacked represents a hijacked connection.
    // This is a terminal state. It does not transition to StateClosed.
    StateHijacked

    // StateClosed represents a closed connection.
    // This is a terminal state. Hijacked connections do not
    // transition to StateClosed.
    StateClosed
)

func (c ConnState) String() string {
    return stateName[c]
}

func (sh serverHandler) ServeHTTP(rw ResponseWriter, req *Request) {
    handler := sh.srv.Handler
    if handler == nil {
        handler = DefaultServeMux
    }
    if req.RequestURI == "*" && req.Method == "OPTIONS" {
        handler = globalOptionsHandler{}
    }
    handler.ServeHTTP(rw, req)
}

// ListenAndServe listens on the TCP network address srv.Addr and then
// calls Serve to handle requests on incoming connections.  If
// srv.Addr is blank, ":http" is used.
func (srv *Server) ListenAndServe() error {
    addr := srv.Addr
    if addr == "" {
        addr = ":http"
    }
    ln, err := net.Listen("tcp", addr)
    if err != nil {
        return err
    }
    return srv.Serve(tcpKeepAliveListener{ln.(*net.TCPListener)})
}

// Serve accepts incoming connections on the Listener l, creating a
// new service goroutine for each.  The service goroutines read requests and
// then call srv.Handler to reply to them.
func (srv *Server) Serve(l net.Listener) error {
    defer l.Close()
    var tempDelay time.Duration // how long to sleep on accept failure
    for {
        rw, e := l.Accept()
        if e != nil {
            if ne, ok := e.(net.Error); ok && ne.Temporary() {
                if tempDelay == 0 {
                    tempDelay = 5 * time.Millisecond
                } else {
                    tempDelay *= 2
                }
                if max := 1 * time.Second; tempDelay > max {
                    tempDelay = max
                }
                srv.logf("http: Accept error: %v; retrying in %v", e, tempDelay)
                time.Sleep(tempDelay)
                continue
            }
            return e
        }
        tempDelay = 0
        c, err := srv.newConn(rw)
        if err != nil {
            continue
        }
        c.setState(c.rwc, StateNew) // before Serve can return
        go c.serve()
    }
}

// SetKeepAlivesEnabled controls whether HTTP keep-alives are enabled.
// By default, keep-alives are always enabled. Only very
// resource-constrained environments or servers in the process of
// shutting down should disable them.
func (srv *Server) SetKeepAlivesEnabled(v bool) {
    if v {
        atomic.StoreInt32(&srv.disableKeepAlives, 0)
    } else {
        atomic.StoreInt32(&srv.disableKeepAlives, 1)
    }
}

// ListenAndServe listens on the TCP network address addr
// and then calls Serve with handler to handle requests
// on incoming connections.  Handler is typically nil,
// in which case the DefaultServeMux is used.
//
// A trivial example server is:
//
//	package main
//
//	import (
//		"io"
//		"net/http"
//		"log"
//	)
//
//	// hello world, the web server
//	func HelloServer(w http.ResponseWriter, req *http.Request) {
//		io.WriteString(w, "hello, world!\n")
//	}
//
//	func main() {
//		http.HandleFunc("/hello", HelloServer)
//		err := http.ListenAndServe(":12345", nil)
//		if err != nil {
//			log.Fatal("ListenAndServe: ", err)
//		}
//	}
func ListenAndServe(addr string, handler Handler) error {
    server := &Server{Addr: addr, Handler: handler}
    return server.ListenAndServe()
}

// ListenAndServeTLS acts identically to ListenAndServe, except that it
// expects HTTPS connections. Additionally, files containing a certificate and
// matching private key for the server must be provided. If the certificate
// is signed by a certificate authority, the certFile should be the concatenation
// of the server's certificate, any intermediates, and the CA's certificate.
//
// A trivial example server is:
//
//	import (
//		"log"
//		"net/http"
//	)
//
//	func handler(w http.ResponseWriter, req *http.Request) {
//		w.Header().Set("Content-Type", "text/plain")
//		w.Write([]byte("This is an example server.\n"))
//	}
//
//	func main() {
//		http.HandleFunc("/", handler)
//		log.Printf("About to listen on 10443. Go to https://127.0.0.1:10443/")
//		err := http.ListenAndServeTLS(":10443", "cert.pem", "key.pem", nil)
//		if err != nil {
//			log.Fatal(err)
//		}
//	}
//
// One can use generate_cert.go in crypto/tls to generate cert.pem and key.pem.
func ListenAndServeTLS(addr string, certFile string, keyFile string, handler Handler) error {
    server := &Server{Addr: addr, Handler: handler}
    return server.ListenAndServeTLS(certFile, keyFile)
}

// ListenAndServeTLS listens on the TCP network address srv.Addr and
// then calls Serve to handle requests on incoming TLS connections.
//
// Filenames containing a certificate and matching private key for the
// server must be provided if the Server's TLSConfig.Certificates is
// not populated. If the certificate is signed by a certificate
// authority, the certFile should be the concatenation of the server's
// certificate, any intermediates, and the CA's certificate.
//
// If srv.Addr is blank, ":https" is used.
func (srv *Server) ListenAndServeTLS(certFile, keyFile string) error {
    addr := srv.Addr
    if addr == "" {
        addr = ":https"
    }
    config := cloneTLSConfig(srv.TLSConfig)
    if config.NextProtos == nil {
        config.NextProtos = []string{"http/1.1"}
    }

    if len(config.Certificates) == 0 || certFile != "" || keyFile != "" {
        var err error
        config.Certificates = make([]tls.Certificate, 1)
        config.Certificates[0], err = tls.LoadX509KeyPair(certFile, keyFile)
        if err != nil {
            return err
        }
    }

    ln, err := net.Listen("tcp", addr)
    if err != nil {
        return err
    }

    tlsListener := tls.NewListener(tcpKeepAliveListener{ln.(*net.TCPListener)}, config)
    return srv.Serve(tlsListener)
}

// TimeoutHandler returns a Handler that runs h with the given time limit.
//
// The new Handler calls h.ServeHTTP to handle each request, but if a
// call runs for longer than its time limit, the handler responds with
// a 503 Service Unavailable error and the given message in its body.
// (If msg is empty, a suitable default message will be sent.)
// After such a timeout, writes by h to its ResponseWriter will return
// ErrHandlerTimeout.
func TimeoutHandler(h Handler, dt time.Duration, msg string) Handler {
    f := func() <-chan time.Time {
        return time.After(dt)
    }
    return &timeoutHandler{h, f, msg}
}

// ErrHandlerTimeout is returned on ResponseWriter Write calls
// in handlers which have timed out.
var ErrHandlerTimeout = errors.New("http: Handler timeout")

func (h *timeoutHandler) ServeHTTP(w ResponseWriter, r *Request) {
    done := make(chan bool, 1)
    tw := &timeoutWriter{w: w}
    go func() {
        h.handler.ServeHTTP(tw, r)
        done <- true
    }()
    select {
    case <-done:
        return
    case <-h.timeout():
        tw.mu.Lock()
        defer tw.mu.Unlock()
        if !tw.wroteHeader {
            tw.w.WriteHeader(StatusServiceUnavailable)
            tw.w.Write([]byte(h.errorBody()))
        }
        tw.timedOut = true
    }
}

func (tw *timeoutWriter) Header() Header {
    return tw.w.Header()
}

func (tw *timeoutWriter) Write(p []byte) (int, error) {
    tw.mu.Lock()
    defer tw.mu.Unlock()
    tw.wroteHeader = true // implicitly at least
    if tw.timedOut {
        return 0, ErrHandlerTimeout
    }
    return tw.w.Write(p)
}

func (tw *timeoutWriter) WriteHeader(code int) {
    tw.mu.Lock()
    defer tw.mu.Unlock()
    if tw.timedOut || tw.wroteHeader {
        return
    }
    tw.wroteHeader = true
    tw.w.WriteHeader(code)
}

func (ln tcpKeepAliveListener) Accept() (c net.Conn, err error) {
    tc, err := ln.AcceptTCP()
    if err != nil {
        return
    }
    tc.SetKeepAlive(true)
    tc.SetKeepAlivePeriod(3 * time.Minute)
    return tc, nil
}

func (globalOptionsHandler) ServeHTTP(w ResponseWriter, r *Request) {
    w.Header().Set("Content-Length", "0")
    if r.ContentLength != 0 {
        // Read up to 4KB of OPTIONS body (as mentioned in the
        // spec as being reserved for future use), but anything
        // over that is considered a waste of server resources
        // (or an attack) and we abort and close the connection,
        // courtesy of MaxBytesReader's EOF behavior.
        mb := MaxBytesReader(w, r.Body, 4<<10)
        io.Copy(ioutil.Discard, mb)
    }
}

func (eofReaderWithWriteTo) WriteTo(io.Writer) (int64, error) { return 0, nil }
func (eofReaderWithWriteTo) Read([]byte) (int, error)         { return 0, io.EOF }

func (h initNPNRequest) ServeHTTP(rw ResponseWriter, req *Request) {
    if req.TLS == nil {
        req.TLS = &tls.ConnectionState{}
        *req.TLS = h.c.ConnectionState()
    }
    if req.Body == nil {
        req.Body = eofReader
    }
    if req.RemoteAddr == "" {
        req.RemoteAddr = h.c.RemoteAddr().String()
    }
    h.h.ServeHTTP(rw, req)
}

func (c *loggingConn) Write(p []byte) (n int, err error) {
    log.Printf("%s.Write(%d) = ....", c.name, len(p))
    n, err = c.Conn.Write(p)
    log.Printf("%s.Write(%d) = %d, %v", c.name, len(p), n, err)
    return
}

func (c *loggingConn) Read(p []byte) (n int, err error) {
    log.Printf("%s.Read(%d) = ....", c.name, len(p))
    n, err = c.Conn.Read(p)
    log.Printf("%s.Read(%d) = %d, %v", c.name, len(p), n, err)
    return
}

func (c *loggingConn) Close() (err error) {
    log.Printf("%s.Close() = ...", c.name)
    err = c.Conn.Close()
    log.Printf("%s.Close() = %v", c.name, err)
    return
}

func (w checkConnErrorWriter) Write(p []byte) (n int, err error) {
    n, err = w.c.w.Write(p) // c.w == c.rwc, except after a hijack, when rwc is nil.
    if err != nil && w.c.werr == nil {
        w.c.werr = err
    }
    return
}
net/http/sniff.go:
// Copyright 2011 The Go Authors.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package http

// DetectContentType implements the algorithm described
// at http://mimesniff.spec.whatwg.org/ to determine the
// Content-Type of the given data.  It considers at most the
// first 512 bytes of data.  DetectContentType always returns
// a valid MIME type: if it cannot determine a more specific one, it
// returns "application/octet-stream".
func DetectContentType(data []byte) string {
    if len(data) > sniffLen {
        data = data[:sniffLen]
    }

    // Index of the first non-whitespace byte in data.
    firstNonWS := 0
    for ; firstNonWS < len(data) && isWS(data[firstNonWS]); firstNonWS++ {
    }

    for _, sig := range sniffSignatures {
        if ct := sig.match(data, firstNonWS); ct != "" {
            return ct
        }
    }

    return "application/octet-stream" // fallback
}
net/http/status.go:
// Copyright 2009 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package http

// HTTP status codes, defined in RFC 2616.
const (
    StatusContinue           = 100
    StatusSwitchingProtocols = 101

    StatusOK                   = 200
    StatusCreated              = 201
    StatusAccepted             = 202
    StatusNonAuthoritativeInfo = 203
    StatusNoContent            = 204
    StatusResetContent         = 205
    StatusPartialContent       = 206

    StatusMultipleChoices   = 300
    StatusMovedPermanently  = 301
    StatusFound             = 302
    StatusSeeOther          = 303
    StatusNotModified       = 304
    StatusUseProxy          = 305
    StatusTemporaryRedirect = 307

    StatusBadRequest                   = 400
    StatusUnauthorized                 = 401
    StatusPaymentRequired              = 402
    StatusForbidden                    = 403
    StatusNotFound                     = 404
    StatusMethodNotAllowed             = 405
    StatusNotAcceptable                = 406
    StatusProxyAuthRequired            = 407
    StatusRequestTimeout               = 408
    StatusConflict                     = 409
    StatusGone                         = 410
    StatusLengthRequired               = 411
    StatusPreconditionFailed           = 412
    StatusRequestEntityTooLarge        = 413
    StatusRequestURITooLong            = 414
    StatusUnsupportedMediaType         = 415
    StatusRequestedRangeNotSatisfiable = 416
    StatusExpectationFailed            = 417
    StatusTeapot                       = 418

    StatusInternalServerError     = 500
    StatusNotImplemented          = 501
    StatusBadGateway              = 502
    StatusServiceUnavailable      = 503
    StatusGatewayTimeout          = 504
    StatusHTTPVersionNotSupported = 505
)

// StatusText returns a text for the HTTP status code. It returns the empty
// string if the code is unknown.
func StatusText(code int) string {
    return statusText[code]
}
net/http/transfer.go:
// Copyright 2009 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package http

// ErrLineTooLong is returned when reading request or response bodies
// with malformed chunked encoding.
var ErrLineTooLong = internal.ErrLineTooLong

func (r errorReader) Read(p []byte) (n int, err error) {
    return 0, r.err
}

func (t *transferWriter) WriteHeader(w io.Writer) error {
    if t.Close {
        if _, err := io.WriteString(w, "Connection: close\r\n"); err != nil {
            return err
        }
    }

    // Write Content-Length and/or Transfer-Encoding whose values are a
    // function of the sanitized field triple (Body, ContentLength,
    // TransferEncoding)
    if t.shouldSendContentLength() {
        if _, err := io.WriteString(w, "Content-Length: "); err != nil {
            return err
        }
        if _, err := io.WriteString(w, strconv.FormatInt(t.ContentLength, 10)+"\r\n"); err != nil {
            return err
        }
    } else if chunked(t.TransferEncoding) {
        if _, err := io.WriteString(w, "Transfer-Encoding: chunked\r\n"); err != nil {
            return err
        }
    }

    // Write Trailer header
    if t.Trailer != nil {
        keys := make([]string, 0, len(t.Trailer))
        for k := range t.Trailer {
            k = CanonicalHeaderKey(k)
            switch k {
            case "Transfer-Encoding", "Trailer", "Content-Length":
                return &badStringError{"invalid Trailer key", k}
            }
            keys = append(keys, k)
        }
        if len(keys) > 0 {
            sort.Strings(keys)
            // TODO: could do better allocation-wise here, but trailers are rare,
            // so being lazy for now.
            if _, err := io.WriteString(w, "Trailer: "+strings.Join(keys, ",")+"\r\n"); err != nil {
                return err
            }
        }
    }

    return nil
}

func (t *transferWriter) WriteBody(w io.Writer) error {
    var err error
    var ncopy int64

    // Write body
    if t.Body != nil {
        if chunked(t.TransferEncoding) {
            if bw, ok := w.(*bufio.Writer); ok && !t.IsResponse {
                w = &internal.FlushAfterChunkWriter{bw}
            }
            cw := internal.NewChunkedWriter(w)
            _, err = io.Copy(cw, t.Body)
            if err == nil {
                err = cw.Close()
            }
        } else if t.ContentLength == -1 {
            ncopy, err = io.Copy(w, t.Body)
        } else {
            ncopy, err = io.Copy(w, io.LimitReader(t.Body, t.ContentLength))
            if err != nil {
                return err
            }
            var nextra int64
            nextra, err = io.Copy(ioutil.Discard, t.Body)
            ncopy += nextra
        }
        if err != nil {
            return err
        }
        if err = t.BodyCloser.Close(); err != nil {
            return err
        }
    }

    if !t.ResponseToHEAD && t.ContentLength != -1 && t.ContentLength != ncopy {
        return fmt.Errorf("http: ContentLength=%d with Body length %d",
            t.ContentLength, ncopy)
    }

    if chunked(t.TransferEncoding) {
        // Write Trailer header
        if t.Trailer != nil {
            if err := t.Trailer.Write(w); err != nil {
                return err
            }
        }
        // Last chunk, empty trailer
        _, err = io.WriteString(w, "\r\n")
    }
    return err
}

// ErrBodyReadAfterClose is returned when reading a Request or Response
// Body after the body has been closed. This typically happens when the body is
// read after an HTTP Handler calls WriteHeader or Write on its
// ResponseWriter.
var ErrBodyReadAfterClose = errors.New("http: invalid Read on closed Body")

func (b *body) Read(p []byte) (n int, err error) {
    b.mu.Lock()
    defer b.mu.Unlock()
    if b.closed {
        return 0, ErrBodyReadAfterClose
    }
    return b.readLocked(p)
}

func (b *body) Close() error {
    b.mu.Lock()
    defer b.mu.Unlock()
    if b.closed {
        return nil
    }
    var err error
    switch {
    case b.sawEOF:
        // Already saw EOF, so no need going to look for it.
    case b.hdr == nil && b.closing:
        // no trailer and closing the connection next.
        // no point in reading to EOF.
    case b.doEarlyClose:
        // Read up to maxPostHandlerReadBytes bytes of the body, looking for
        // for EOF (and trailers), so we can re-use this connection.
        if lr, ok := b.src.(*io.LimitedReader); ok && lr.N > maxPostHandlerReadBytes {
            // There was a declared Content-Length, and we have more bytes remaining
            // than our maxPostHandlerReadBytes tolerance. So, give up.
            b.earlyClose = true
        } else {
            var n int64
            // Consume the body, or, which will also lead to us reading
            // the trailer headers after the body, if present.
            n, err = io.CopyN(ioutil.Discard, bodyLocked{b}, maxPostHandlerReadBytes)
            if err == io.EOF {
                err = nil
            }
            if n == maxPostHandlerReadBytes {
                b.earlyClose = true
            }
        }
    default:
        // Fully consume the body, which will also lead to us reading
        // the trailer headers after the body, if present.
        _, err = io.Copy(ioutil.Discard, bodyLocked{b})
    }
    b.closed = true
    return err
}

func (bl bodyLocked) Read(p []byte) (n int, err error) {
    if bl.b.closed {
        return 0, ErrBodyReadAfterClose
    }
    return bl.b.readLocked(p)
}
net/http/transport.go:
// Copyright 2011 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// HTTP client implementation. See RFC 2616.
//
// This is the low-level Transport implementation of RoundTripper.
// The high-level interface is in client.go.

package http

// DefaultTransport is the default implementation of Transport and is
// used by DefaultClient. It establishes network connections as needed
// and caches them for reuse by subsequent calls. It uses HTTP proxies
// as directed by the $HTTP_PROXY and $NO_PROXY (or $http_proxy and
// $no_proxy) environment variables.
var DefaultTransport RoundTripper = &Transport{
    Proxy: ProxyFromEnvironment,
    Dial: (&net.Dialer{
        Timeout:   30 * time.Second,
        KeepAlive: 30 * time.Second,
    }).Dial,
    TLSHandshakeTimeout: 10 * time.Second,
}

// DefaultMaxIdleConnsPerHost is the default value of Transport's
// MaxIdleConnsPerHost.
const DefaultMaxIdleConnsPerHost = 2

// Transport is an implementation of RoundTripper that supports HTTP,
// HTTPS, and HTTP proxies (for either HTTP or HTTPS with CONNECT).
// Transport can also cache connections for future re-use.
type Transport struct {

    // Proxy specifies a function to return a proxy for a given
    // Request. If the function returns a non-nil error, the
    // request is aborted with the provided error.
    // If Proxy is nil or returns a nil *URL, no proxy is used.
    Proxy func(*Request) (*url.URL, error)

    // Dial specifies the dial function for creating unencrypted
    // TCP connections.
    // If Dial is nil, net.Dial is used.
    Dial func(network, addr string) (net.Conn, error)

    // DialTLS specifies an optional dial function for creating
    // TLS connections for non-proxied HTTPS requests.
    //
    // If DialTLS is nil, Dial and TLSClientConfig are used.
    //
    // If DialTLS is set, the Dial hook is not used for HTTPS
    // requests and the TLSClientConfig and TLSHandshakeTimeout
    // are ignored. The returned net.Conn is assumed to already be
    // past the TLS handshake.
    DialTLS func(network, addr string) (net.Conn, error)

    // TLSClientConfig specifies the TLS configuration to use with
    // tls.Client. If nil, the default configuration is used.
    TLSClientConfig *tls.Config

    // TLSHandshakeTimeout specifies the maximum amount of time waiting to
    // wait for a TLS handshake. Zero means no timeout.
    TLSHandshakeTimeout time.Duration

    // DisableKeepAlives, if true, prevents re-use of TCP connections
    // between different HTTP requests.
    DisableKeepAlives bool

    // DisableCompression, if true, prevents the Transport from
    // requesting compression with an "Accept-Encoding: gzip"
    // request header when the Request contains no existing
    // Accept-Encoding value. If the Transport requests gzip on
    // its own and gets a gzipped response, it's transparently
    // decoded in the Response.Body. However, if the user
    // explicitly requested gzip it is not automatically
    // uncompressed.
    DisableCompression bool

    // MaxIdleConnsPerHost, if non-zero, controls the maximum idle
    // (keep-alive) to keep per-host.  If zero,
    // DefaultMaxIdleConnsPerHost is used.
    MaxIdleConnsPerHost int

    // ResponseHeaderTimeout, if non-zero, specifies the amount of
    // time to wait for a server's response headers after fully
    // writing the request (including its body, if any). This
    // time does not include the time to read the response body.
    ResponseHeaderTimeout time.Duration

    // TODO: tunable on global max cached connections
    // TODO: tunable on timeout on cached connections

}

// ProxyFromEnvironment returns the URL of the proxy to use for a
// given request, as indicated by the environment variables
// HTTP_PROXY, HTTPS_PROXY and NO_PROXY (or the lowercase versions
// thereof). HTTPS_PROXY takes precedence over HTTP_PROXY for https
// requests.
//
// The environment values may be either a complete URL or a
// "host[:port]", in which case the "http" scheme is assumed.
// An error is returned if the value is a different form.
//
// A nil URL and nil error are returned if no proxy is defined in the
// environment, or a proxy should not be used for the given request,
// as defined by NO_PROXY.
//
// As a special case, if req.URL.Host is "localhost" (with or without
// a port number), then a nil URL and nil error will be returned.
func ProxyFromEnvironment(req *Request) (*url.URL, error) {
    var proxy string
    if req.URL.Scheme == "https" {
        proxy = httpsProxyEnv.Get()
    }
    if proxy == "" {
        proxy = httpProxyEnv.Get()
    }
    if proxy == "" {
        return nil, nil
    }
    if !useProxy(canonicalAddr(req.URL)) {
        return nil, nil
    }
    proxyURL, err := url.Parse(proxy)
    if err != nil || !strings.HasPrefix(proxyURL.Scheme, "http") {
        // proxy was bogus. Try prepending "http://" to it and
        // see if that parses correctly. If not, we fall
        // through and complain about the original one.
        if proxyURL, err := url.Parse("http://" + proxy); err == nil {
            return proxyURL, nil
        }
    }
    if err != nil {
        return nil, fmt.Errorf("invalid proxy address %q: %v", proxy, err)
    }
    return proxyURL, nil
}

// ProxyURL returns a proxy function (for use in a Transport)
// that always returns the same URL.
func ProxyURL(fixedURL *url.URL) func(*Request) (*url.URL, error) {
    return func(*Request) (*url.URL, error) {
        return fixedURL, nil
    }
}

// RoundTrip implements the RoundTripper interface.
//
// For higher-level HTTP client support (such as handling of cookies
// and redirects), see Get, Post, and the Client type.
func (t *Transport) RoundTrip(req *Request) (resp *Response, err error) {
    if req.URL == nil {
        req.closeBody()
        return nil, errors.New("http: nil Request.URL")
    }
    if req.Header == nil {
        req.closeBody()
        return nil, errors.New("http: nil Request.Header")
    }
    if req.URL.Scheme != "http" && req.URL.Scheme != "https" {
        t.altMu.RLock()
        var rt RoundTripper
        if t.altProto != nil {
            rt = t.altProto[req.URL.Scheme]
        }
        t.altMu.RUnlock()
        if rt == nil {
            req.closeBody()
            return nil, &badStringError{"unsupported protocol scheme", req.URL.Scheme}
        }
        return rt.RoundTrip(req)
    }
    if req.URL.Host == "" {
        req.closeBody()
        return nil, errors.New("http: no Host in request URL")
    }
    treq := &transportRequest{Request: req}
    cm, err := t.connectMethodForRequest(treq)
    if err != nil {
        req.closeBody()
        return nil, err
    }

    // Get the cached or newly-created connection to either the
    // host (for http or https), the http proxy, or the http proxy
    // pre-CONNECTed to https server.  In any case, we'll be ready
    // to send it requests.
    pconn, err := t.getConn(req, cm)
    if err != nil {
        t.setReqCanceler(req, nil)
        req.closeBody()
        return nil, err
    }

    return pconn.roundTrip(treq)
}

// RegisterProtocol registers a new protocol with scheme.
// The Transport will pass requests using the given scheme to rt.
// It is rt's responsibility to simulate HTTP request semantics.
//
// RegisterProtocol can be used by other packages to provide
// implementations of protocol schemes like "ftp" or "file".
func (t *Transport) RegisterProtocol(scheme string, rt RoundTripper) {
    if scheme == "http" || scheme == "https" {
        panic("protocol " + scheme + " already registered")
    }
    t.altMu.Lock()
    defer t.altMu.Unlock()
    if t.altProto == nil {
        t.altProto = make(map[string]RoundTripper)
    }
    if _, exists := t.altProto[scheme]; exists {
        panic("protocol " + scheme + " already registered")
    }
    t.altProto[scheme] = rt
}

// CloseIdleConnections closes any connections which were previously
// connected from previous requests but are now sitting idle in
// a "keep-alive" state. It does not interrupt any connections currently
// in use.
func (t *Transport) CloseIdleConnections() {
    t.idleMu.Lock()
    m := t.idleConn
    t.idleConn = nil
    t.idleConnCh = nil
    t.wantIdle = true
    t.idleMu.Unlock()
    for _, conns := range m {
        for _, pconn := range conns {
            pconn.close()
        }
    }
}

// CancelRequest cancels an in-flight request by closing its connection.
// CancelRequest should only be called after RoundTrip has returned.
func (t *Transport) CancelRequest(req *Request) {
    t.reqMu.Lock()
    cancel := t.reqCanceler[req]
    delete(t.reqCanceler, req)
    t.reqMu.Unlock()
    if cancel != nil {
        cancel()
    }
}

func (e *envOnce) Get() string {
    e.once.Do(e.init)
    return e.val
}

func (k connectMethodKey) String() string {
    // Only used by tests.
    return fmt.Sprintf("%s|%s|%s", k.proxy, k.scheme, k.addr)
}

func (e *httpError) Error() string   { return e.err }
func (e *httpError) Timeout() bool   { return e.timeout }
func (e *httpError) Temporary() bool { return true }

func (es *bodyEOFSignal) Read(p []byte) (n int, err error) {
    es.mu.Lock()
    closed, rerr := es.closed, es.rerr
    es.mu.Unlock()
    if closed {
        return 0, errors.New("http: read on closed response body")
    }
    if rerr != nil {
        return 0, rerr
    }

    n, err = es.body.Read(p)
    if err != nil {
        es.mu.Lock()
        defer es.mu.Unlock()
        if es.rerr == nil {
            es.rerr = err
        }
        err = es.condfn(err)
    }
    return
}

func (es *bodyEOFSignal) Close() error {
    es.mu.Lock()
    defer es.mu.Unlock()
    if es.closed {
        return nil
    }
    es.closed = true
    if es.earlyCloseFn != nil && es.rerr != io.EOF {
        return es.earlyCloseFn()
    }
    err := es.body.Close()
    return es.condfn(err)
}

func (gz *gzipReader) Read(p []byte) (n int, err error) {
    if gz.zr == nil {
        gz.zr, err = gzip.NewReader(gz.body)
        if err != nil {
            return 0, err
        }
    }
    return gz.zr.Read(p)
}

func (gz *gzipReader) Close() error {
    return gz.body.Close()
}

func (tlsHandshakeTimeoutError) Timeout() bool   { return true }
func (tlsHandshakeTimeoutError) Temporary() bool { return true }
func (tlsHandshakeTimeoutError) Error() string   { return "net/http: TLS handshake timeout" }

func (nr noteEOFReader) Read(p []byte) (n int, err error) {
    n, err = nr.r.Read(p)
    if err == io.EOF {
        *nr.sawEOF = true
    }
    return
}

func (fakeLocker) Lock()   {}
func (fakeLocker) Unlock() {}
SUBDIRECTORIES

	cgi
	cookiejar
	fcgi
	httptest
	httputil
	pprof

