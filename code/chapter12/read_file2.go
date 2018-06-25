package main

import (
	"encoding/csv"
	"fmt"
	"io"
	"strconv"
	"strings"
)

type Data struct {
	title    string
	price    float64
	quantity int
}

func main() {
	data := `"The ABC of Go";25.5;1500
"Functional Programming with Go";56;280
"Go for It";45.9;356
"The; Go Way";55;500
`

	reader := csv.NewReader(strings.NewReader(data))
	reader.Comma = ';'

	for {
		record, err := reader.Read()
		if err != nil {
			if err != io.EOF {
				fmt.Println("解析失败", err)
			}
			return
		}

		records := []*Data{}

		price, _ := strconv.ParseFloat(record[1], 0)
		quantity, _ := strconv.Atoi(record[2])
		records = append(records, &Data{record[0], price, quantity})
		for _, data := range records {
			fmt.Println(data.title, data.price, data.quantity)
		}
	}
}
