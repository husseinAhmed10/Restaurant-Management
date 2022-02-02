#pragma once

#ifndef __KEYNODE_H_
#define __KEYNODE_H_

template < typename T>
class KeyNode
{
private:
	T item; // A data item
	KeyNode<T>* next; // Pointer to next node
	double Key;
public:
	KeyNode();
	KeyNode(const T& r_Item);	//passing by const ref.
	KeyNode(const T& r_Item, double K);
	KeyNode(const T& r_Item, KeyNode<T>* nextNodePtr);
	KeyNode(const T& r_Item, KeyNode<T>* nextNodePtr, double K);
	void setItem(const T& r_Item);
	void setNext(KeyNode<T>* nextNodePtr);
	T getItem() const;
	KeyNode<T>* getNext() const;
	void SetKey(double K);
	double getKey();
}; // end Node


template < typename T>
KeyNode<T>::KeyNode()
{
	next = nullptr;
}

template < typename T>
KeyNode<T>::KeyNode(const T& r_Item)
{
	item = r_Item;
	next = nullptr;
}

template < typename T>
KeyNode<T>::KeyNode(const T& r_Item,double K)
{
	item = r_Item;
	next = nullptr;
	Key = K;
}

template < typename T>
KeyNode<T>::KeyNode(const T& r_Item, KeyNode<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}
template < typename T>
KeyNode<T>::KeyNode(const T& r_Item, KeyNode<T>* nextNodePtr, double K)
{
	item = r_Item;
	next = nextNodePtr;
	Key = K;
}

template < typename T>
void KeyNode<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

template < typename T>
void KeyNode<T>::setNext(KeyNode<T>* nextNodePtr)
{
	next = nextNodePtr;
}


template < typename T>
T KeyNode<T>::getItem() const
{
	return item;
}

template < typename T>
KeyNode<T>* KeyNode<T>::getNext() const
{
	return next;
}
template < typename T>
void KeyNode<T>::SetKey(double K)
{
	Key = K;
}
template < typename T>
double KeyNode<T>::getKey()
{
	return Key;
}
#endif