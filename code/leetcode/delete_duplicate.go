package main

// Definition for singly-linked list.
type ListNode struct {
	Val  int
	Next *ListNode
}

func deleteDuplicates(head *ListNode) *ListNode {
	var preNode *ListNode
	for node := head; node != nil; node = node.Next {
		if preNode == nil || preNode.Val != node.Val {
			preNode = node
		} else {
			preNode.Next = node.Next
		}
	}
	return head
}
