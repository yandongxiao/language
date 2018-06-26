package main

import "fmt"

type ListNode struct {
	Val  int
	Next *ListNode
}

func main() {
	node1 := ListNode{3, nil}
	node2 := ListNode{2, &node1}
	node3 := ListNode{1, &node2}
	node4 := ListNode{3, nil}
	node5 := ListNode{2, &node4}
	node6 := ListNode{1, &node5}
	head := mergeTwoLists(&node3, &node6)

	for head != nil {
		fmt.Println(head.Val)
		head = head.Next
	}
}

func mergeTwoLists(l1 *ListNode, l2 *ListNode) *ListNode {
	var head *ListNode
	var tail *ListNode
	for {
		var node *ListNode
		if l1 == nil && l2 == nil {
			break
		}

		if l1 == nil {
			node = l2
			l2 = l2.Next
		} else if l2 == nil {
			node = l1
			l1 = l1.Next
		} else {
			if l1.Val > l2.Val {
				node = l2
				l2 = l2.Next
			} else {
				node = l1
				l1 = l1.Next
			}
		}

		if head == nil {
			head = node
			tail = node
		} else {
			tail.Next = node
			tail = node
		}
	}
	return head
}
