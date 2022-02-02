#pragma once
#ifndef __PRIORITYQUEUE_H_
#define __PRIORITYQUEUE_H_
#include "KeyNode.h"
template <typename T>
class PriorityQueue :
	public KeyNode<T>
{
protected:
	KeyNode<T>* backPtr;
	KeyNode<T>* frontPtr;
public:
	PriorityQueue();
	bool isEmpty() const;
	virtual bool enqueue(const T& newEntry, double newKey);
	bool dequeue(T& frntEntry);
	bool peekFront(T& frntEntry)  const;
	T* toArray(int& count);	//returns array of T (array if items)
	virtual ~PriorityQueue();
	ORD_TYPE GetType();
	bool findID(int ID);
};

template <typename T>
PriorityQueue<T>::PriorityQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
	KeyNode<T>::SetKey(0);
}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool PriorityQueue<T>::isEmpty() const
{
	if (frontPtr == nullptr)
		return true;
	else
		return false;
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/



/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool PriorityQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	KeyNode<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = nullptr;

	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;


	return true;

}

/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peekFront
gets the front of this queue. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
return: flase if Queue is empty
*/
template <typename T>
bool PriorityQueue<T>::peekFront(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
}

/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: toArray
returns an array of "T"
Output: count: the length of the returned array (zero if Queue is empty)
returns: The array of T. (nullptr if Queue is empty)
*/

template <typename T>
T* PriorityQueue<T>::toArray(int& count)
{
	count = 0;

	if (!frontPtr)
		return nullptr;
	//counting the no. of items in the Queue
	KeyNode<T>* p = frontPtr;
	while (p)
	{
		count++;
		p = p->getNext();
	}


	T* Arr = new T[count];
	p = frontPtr;
	for (int i = 0; i < count; i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;
}
template <typename T>
bool PriorityQueue<T>::enqueue(const T& newEntry, double newKey)
{
	KeyNode<T>* newNodePtr = new KeyNode<T>(newEntry, newKey);

	// Insert the new node
	if (PriorityQueue<T>::isEmpty())
	{
		frontPtr = newNodePtr;
		backPtr = newNodePtr;// The queue is empty\

	}
	else if (backPtr && backPtr->getKey() > newKey)
	{
		backPtr->setNext(newNodePtr); // The queue was not empty
		backPtr = newNodePtr;
	}

	else if (newKey > frontPtr->getKey())
	{
		newNodePtr->setNext(frontPtr);
		frontPtr = newNodePtr;
	}
	else
	{
		KeyNode<T>* temp = frontPtr;
		while (temp && temp->getNext() && temp->getNext()->getKey() >= newKey)
		{
			temp = temp->getNext();
		}
		newNodePtr->setNext(temp->getNext());
		temp->setNext(newNodePtr); // New node is at back
	}
	return true;
}
template <typename T>
ORD_TYPE PriorityQueue<T>::GetType()
{
	Order* O;
	peakfront(O);
	return O->GetType();
}

template <typename T>
bool PriorityQueue<T>::findID(int ID)
{
	int size = 0;
	int count = 0;
	Order** find = toArray(size);
	for (int i = 0; i < size; i++)
	{
		if (find[i]->GetID() == ID)
			count++;
	}
	if (count == 0)
		return false;
	else
		return true;
}
#endif