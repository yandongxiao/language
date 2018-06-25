package main

import (
	"fmt"
	"github.com/garyburd/redigo/redis"
	"log"
)

func main() {
	client, err := redis.Dial("tcp", "localhost:6379")
	if err != nil {
		log.Println("can not connect to server")
		return
	}
	defer client.Close()

	psc := redis.PubSubConn{client} /* use client can not work */
	err = psc.Subscribe("1")
	if err != nil {
		log.Println("send subscribe failed")
		return
	}

	select {
	case psc:
		fmt.Println(psc.Receive())
	}
}
