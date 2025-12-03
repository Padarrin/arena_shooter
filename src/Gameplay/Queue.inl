#include "Queue.hpp"


template<typename T, typename COMPARE>
inline Node<T>* Queue_<T, COMPARE>::operator[](int index)
{
	int length = Size();
	if (IsEmpty() == false && index < length)
	{
		std::priority_queue<Node<T>*, std::vector<Node<T>*>, CompareASTAR<T>> queue = GetQueueCopy();
		for (int i = 0; i < length; i++)
		{
			if (i == index)
			{
				return queue.Top();
			}
			queue.Pop();
		}
	}
	return nullptr;
}

template<typename T, typename COMPARE>
inline int Queue_<T, COMPARE>::GetIndexElement(Node<T>* node)
{
	int length = Size();
	if (IsEmpty() == false)
	{
		std::priority_queue<Node<T>*, std::vector<Node<T>*>, CompareASTAR<T>> queue = GetQueueCopy();
		for (int i = 0; i < length; i++)
		{
			Node<T>* curente = queue.Top();
			if (curente == node)
			{
				return i;
			}
			queue.Pop();
		}
	}
	return nullptr;
}

