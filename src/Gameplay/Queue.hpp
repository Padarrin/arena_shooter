#pragma once
#include <queue>
#include "Compare.h"

template<typename T>
class Node;

template<typename T, typename COMPARE>
class Queue_
{
protected:
	std::priority_queue<Node<T>*, std::vector<Node<T>*>, COMPARE> mQueue;
public:

	Queue_() { mQueue = std::priority_queue<Node<T>*, std::vector<Node<T>*>, COMPARE>(); }
	Queue_(std::priority_queue<Node<T>*, std::vector<Node<T>*>, COMPARE> queue) { mQueue = queue; }

	Node<T>* Top() { return mQueue.top(); };
	void Pop() { mQueue.pop(); };
	int Size() { return mQueue.size(); };

	void Push(Node<T>* node) { mQueue.push(node); };
	bool IsEmpty() { return mQueue.empty(); };
	void Clear() { mQueue = std::priority_queue<Node<T>*, std::vector<Node<T>*>, COMPARE>(); };

	void Swap(Queue_& _Right) { mQueue.swap(_Right.GetQueueRef()); }

	Node<T>* operator[](int index);

	int GetIndexElement(Node<T>* node);

	std::priority_queue<Node<T>*, std::vector<Node<T>*>, COMPARE> GetQueueCopy() { return mQueue; };
	std::priority_queue<Node<T>*, std::vector<Node<T>*>, COMPARE>& GetQueueRef() { return mQueue; };
	std::priority_queue<Node<T>*, std::vector<Node<T>*>, COMPARE>* GetQueuePointer() { return &mQueue; };


};

#include "Queue.inl"