package main

import "github.com/Sirupsen/logrus"

func main() {
	logger := logrus.New()
	entry := logrus.NewEntry(logger)
	entry.Debug("debug")
}
