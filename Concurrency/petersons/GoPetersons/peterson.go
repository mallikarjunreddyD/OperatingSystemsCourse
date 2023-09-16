package main

import (
	"fmt"
	"sync"
	"time"
)

var Turn int8
var Flag [2]bool
var wg sync.WaitGroup

func main() {
	Flag[0] = false
	Flag[1] = false
	wg.Add(2)
	go Producer()
	go Consumer()
	wg.Wait()
}
func Producer() {
	defer wg.Done()
	for {
		Flag[0] = true
		Turn = 1
		for Flag[1] && Turn == 1 {
			fmt.Println("Producer: Waiting to enter critical section")
		}
		fmt.Println("Producer: Entering critical section")
		time.Sleep(3 * time.Second)
		fmt.Println("Producer: Exiting critical section")
		Flag[0] = false
		time.Sleep(2 * time.Second)
	}
}
func Consumer() {
	defer wg.Done()
	for {
		Flag[1] = true
		Turn = 0
		for Flag[0] && Turn == 0 {
			fmt.Println("Consumer: Waiting to enter critical section")
		}
		fmt.Println("Consumer: Entering critical section")
		time.Sleep(10 * time.Second)
		fmt.Println("Consumer: Exiting critical section")
		Flag[1] = false
		time.Sleep(2 * time.Second)
	}
}
