package main

import (
	"database/sql"
	"fmt"

	_ "github.com/go-sql-driver/mysql"
)

func main() {
	db, err := sql.Open("mysql", "cos:cos@tcp(124.238.192.209:5301)/test")
	if err != nil {
		fmt.Println(err.Error())
	}

	rows, err := db.Query("call Proc()")
	if err != nil {
		fmt.Println("error: ", err.Error())
	}
	defer rows.Close()

	var id, name string
	for rows.Next() {
		err := rows.Scan(&id, &name)
		if err != nil {
			fmt.Println(id, name)
		}
		fmt.Println(id, name)
	}
	err = rows.Err()
	if err != nil {
		fmt.Println(err)
	}

	err = db.QueryRow("call Proc()").Scan(&id, &name)
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println("-------", id, name)
}
