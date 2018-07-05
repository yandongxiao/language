package main

import "fmt"

// Definition for singly-linked list.
type ListNode struct {
	Val  int
	Next *ListNode
}

func deleteDuplicates(head *ListNode) *ListNode {
	var preNode *ListNode
	var lastPreNode *ListNode
	counter := 0
	for node := head; node != nil; node = node.Next {
		if preNode == nil || preNode.Val == node.Val {
			preNode = node
			counter++
		} else if counter > 1 {
			preNode = node
			counter = 1
		} else if counter == 1 {
			if lastPreNode == nil {
				lastPreNode = preNode
				head = lastPreNode
			} else {
				lastPreNode.Next = preNode
				lastPreNode = preNode
			}
			preNode = node
		}
	}
	println(counter)
	if counter == 1 {
		if lastPreNode == nil {
			lastPreNode = preNode
			head = lastPreNode
		} else {
			lastPreNode.Next = preNode
			lastPreNode = preNode
			lastPreNode.Next = nil
		}
		return head
	}

	if lastPreNode == nil {
		return nil
	}

	lastPreNode.Next = nil
	return head
}

func main() {
	//l4 := &ListNode{1, nil}
	l3 := &ListNode{2, nil}
	l2 := &ListNode{2, l3}
	l1 := &ListNode{1, l2}
	head := deleteDuplicates(l1)
	for {
		if head != nil {
			fmt.Println(head.Val)
			head = head.Next
			continue
		}
		break
	}
}
