package main

import (
	"log"
	"os"
	"os/signal"
	"syscall"
)

func main() {
	if err := syscall.Mkfifo("exit-fifo", 0666); err != nil && !os.IsExist(err) {
		log.Fatal(err)
	}
	_, err := os.OpenFile("exit-fifo", syscall.O_WRONLY|syscall.O_CLOEXEC, 0)
	if err != nil {
		log.Fatal(err)
	}
	s := make(chan os.Signal)
	signal.Notify(s, syscall.SIGTERM)
	<-s
}
