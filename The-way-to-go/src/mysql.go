package main

import (
	"log"

	"database/sql"
	_ "github.com/go-sql-driver/mysql"
)

var (
	id   int
	name string
)

func main() {
	db, err := sql.Open("mysql",
		"cos:cos@tcp(124.238.192.209:5301)/test")
	if err != nil {
		log.Fatal(err)
	}
	defer db.Close()

	tx, err := db.Begin()
	if err != nil {
		log.Fatal(err)
	}
	defer tx.Rollback()
	stmt, err := tx.Prepare("INSERT INTO book VALUES (100, 100)")
	if err != nil {
		log.Fatal(err)
	}
	defer stmt.Close() // danger!

	stmt.Exec()

	err = tx.Commit()
	if err != nil {
		log.Fatal(err)
	}

}
