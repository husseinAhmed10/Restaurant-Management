#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"
#include "..\Rest\Order.h"
#include "..\Rest\Cook.h"

template <typename T>
class LinkedList
{
protected:
	Node<T>* Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
public:


	LinkedList()
	{
		Head = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	void PrintList()	const
	{
		Node<T>* p = Head;

		while (p)
		{
			cout << p->getItem() << " ";
			p = p->getNext();
		}
		cout << endl;
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	*
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T& data)
	{
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;

	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}

	//[0] IsEmpty
	// Check if the head points to null

	bool isEmpty()
	{
		if (Head == nullptr)
			return 1;
		return 0;
	}

	//[1]InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(const T& data)
	{
		if (Head == nullptr)
		{
			InsertBeg(data);
			return;
		}
		Node<T>* R = new Node<T>(data);
		Node<T>* H = Head;
		while (H->getNext())
		{
			H = H->getNext();
		}
		H->setNext(R);
	}
	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
	T* Find(int Key)
	{
		Node<T>* H = Head;
		while (H)
		{
			if (H->getItem() == Key)
				return H;
			H = H->getNext();
		}
		return nullptr;
	}

	//[3]CountOccurance
	//returns how many times a certain value appeared in the list
	int CountOccurance(const T& value)
	{
		int count = 0;
		Node<T>* H = Head;
		while (H)
		{
			if (H->getItem() == value)
				count++;
			H = H->getNext();
		}
		return count;
	}

	//[4] DeleteFirst
	//Deletes the first node in the list
	void DeleteFirst()
	{
		if (Head == nullptr)
			return;
		Node<T>* H = Head;
		Head = H->getNext();
		delete H;
	}


	//[5] DeleteLast
	//Deletes the last node in the list
	void DeleteLast()
	{
		if (Head->getNext() == nullptr)
		{
			delete Head;
			Head = nullptr;
			return;
		}
		Node<T>* H = Head;
		while (H->getNext()->getNext())
		{
			H = H->getNext();
		}
		Node<T>* Dptr = H->getNext();
		H->setNext(nullptr);
		delete Dptr;
	}

	//[6] DeleteNode
	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(const T& value)
	{

		Node<T>* H = Head;
		if (Head->getItem() == value)
		{
			Head = Head->getNext();
			delete H;
			H = nullptr;
			return true;
		}
		while (H->getNext())
		{
			if (H->getNext()->getItem() == value)
			{
				Node<T>* Dptr = H->getNext();
				H->setNext(Dptr->getNext());
				delete Dptr;
				return true;
			}
			H = H->getNext();
		}
		return false;
	}

	//[7] DeleteNodes
	//deletes ALL node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNodes(const T& value)
	{
		Node<T>* H = Head;
		int count = 0;
		while (H)
		{
			if (H->getItem() == value && H == Head)
			{
				H = H->getNext();
				delete Head;
				Head = H;
				count++;
			}

			else if (H->getNext() != nullptr && H->getNext()->getItem() == value)
			{
				Node<T>* Dptr = H->getNext();
				H->setNext(Dptr->getNext());
				delete Dptr;
				count++;
			}
			else
				H = H->getNext();
		}
		if (count == 0)
			return false;
		else
			return true;
	}
	//[8]Merge
	//Merges the current list to another list L by making the last Node in the current list 
	//point to the first Node in list L
	void Merge(LinkedList& L)
	{
		if (Head == nullptr)
		{
			Head = L.Head;
			L.Head = nullptr;
			return;
		}
		Node<T>* H = Head;
		while (H->getNext())
		{
			H = H->getNext();
		}
		H->setNext(L.Head);
		L.Head = nullptr;
	}
	//[9] Reverse
	//Reverses the linked list (without allocating any new Nodes)
	void Reverse()
	{
		Node<T>* H = Head;
		if (!H || !(H->getNext()))
			return;
		Node<T>* newHead = Head;
		while (H->getNext()->getNext())
		{
			H = H->getNext();
			newHead = H->getNext();
		}
		H->getNext()->setNext(H);
		while (Head->getNext())
		{
			Node<T>* Traverse = Head;
			while (Traverse->getNext()->getNext()->getNext() != Traverse->getNext())
			{
				Traverse = Traverse->getNext();
			}
			Traverse->getNext()->setNext(Traverse);
			if (Head->getNext()->getNext() == Head)
			{
				Head->setNext(nullptr);
			}
		}
		Head = newHead;
	}

	bool CheckID(int id) {                  // This function takes an id , returns 1 if it's found, 0 if not
		Node<T>* p = Head;
		while (p) {
			if (p->getItem().GetID() == id)
				return true;
			p = p->getNext();
		}
		return false;
	}

	void DeleteHead(T& value)
	{
		if (isEmpty())
			return;
		Node<T>* H = Head;
		value = Head->getItem();
		Head = Head->getNext();
		delete H;
		H = nullptr;
	}

	Cook* GetCookFromID(int id)
	{                          // this function takes an ID and returns a ptr to the cook possessing that ID
		Node<T>* p = Head;                                 //if he is found, and returns nullptr if not
		bool s = CheckID(id);
		while (p && s == 1) {
			Cook* c = &(p->getItem());
			if (c->GetID() == id) {
				return c;
			}
			p = p->getNext();
		}
		return nullptr;
		// could not find a cook with that id
	}


	void RemoveCook(int id) {                       //remove the cook of a certain ID
		Node<T>* p = Head;
		bool s = CheckID(id);
		while (p && s == 1) {
			Cook c = p->getItem();

			if (c.GetID() == id && p == Head) {
				Head = p->getNext();
				delete p;
				return;
			}

			if (p->getNext()) {
				Cook b = p->getNext()->getItem();
				if (b.GetID() == id) {
					Node<T>* s = p->getNext();
					p->setNext(s->getNext());
					delete s;
				}
			}
			p = p->getNext();
		}
	}                                                               //checked


	Cook* RemoveCookToAdd(int id) {                      // this function removes the cook from a list and returns a ptr to that cook
		Node<T>* p = Head;                               // so that it could be added to another list
		bool s = CheckID(id);
		if (s == 1 && p) {
			Cook* n = new Cook;
			n = GetCookFromID(id);
			return n;
		}
		return nullptr;
	}


	// Returns The number of the Cook
	int GetNumberOfCooks() {
		Node<T>* p = Head;
		int c = 0;
		while (p) {
			c++;
			p = p->getNext();
		}
		return c;
	}


	void Add(const T& data)                           //checked
	{
		Node<T>* R = new Node<T>(data);
		R->setNext(Head);
		Head = R;

	}


	void Clear() {                      //checked
		Node<T>* p = Head;
		while (Head)
		{
			p = Head->getNext();
			delete Head;
			Head = p;
		}
	}

	T* toArray(int& count)
	{
		count = 0;

		if (!Head)
			return nullptr;
		//counting the no. of items in the Queue
		Node<T>* p = Head;
		while (p)
		{
			count++;
			p = p->getNext();
		}


		T* Arr = new T[count];
		p = Head;
		for (int i = 0; i < count; i++)
		{
			Arr[i] = p->getItem();
			p = p->getNext();
		}
		return Arr;
	}
	//checks if there are any finished orders in the linked list
	//if yes returns true
	T* CheckFinishedOrder()
	{
		int count = 0;
		int size = 0;
		Order** list = toArray(size);
		for (int i = 0; i < size; i++)
		{
			if (list[i]->getStatus() == DONE)
				count++;
		}
		if (count == 0)
			return false;
		return true;
	}
	T* ReturnFinishedOrder()
	{
		int size = 0;
		Order* Finished;
		Node<T>* H = Head;
		Order* traverse = H;
		while (H)
		{
			if (traverse->getStatus() == DONE)
				return traverse;
			H = H->getNext();
			traverse = H;
		}
		if (count == 0)
			return false;
		return true;
	}

	T RemoveAndReturnfirstNode()
	{
		if (!Head) return nullptr;
		Node<T>* H = Head;
		Head = Head->getNext();
		return H->getItem();
	}


	T FirstCooktoInjure() {
		Node<T>* p = Head;
		if (p == nullptr)
			return nullptr;

		T a = (p->getItem());
		if (a->MakeInjured() == true) {
			p->setItem(a);
			return  a;
		}
		while (p && p->getNext()) {
			T b = (p->getNext()->getItem());
			if (b->MakeInjured() == true) {
				p->getNext()->setItem(b);
				return b;
			}
			p = p->getNext();
		}
	}




	void Remove(T item) {

		Node<T>* p = Head;
		if (p == nullptr)
			return;

		T c = (p->getItem());

		if (c == item) {
			Head = p->getNext();
			delete p;
			return;
		}

		while (p && p->getNext()) {
			c = (p->getNext()->getItem());
			if (c == item) {
				Node<T>* temp = p->getNext();
				p->setNext(temp->getNext());
				delete temp;
			}
			p = p->getNext();
		}

	}
	
	bool RemoveAndAddNodes(Queue<T> &M, const T value)
	{
		Node<T>* H = Head;
		int count = 0;
		while (H)
		{
			if (H->getItem() == value && H == Head)
			{
				H = H->getNext();
				M.enqueue(Head->getItem());
				Head = H;
				count++;
			}

			else if (H->getNext() != nullptr && H->getNext()->getItem() == value)
			{
				Node<T>* Dptr = H->getNext();
				H->setNext(Dptr->getNext());
				M.enqueue(Dptr->getItem());
				count++;
			}
			else
				H = H->getNext();
		}
		if (count == 0)
			return false;
		else
			return true;
	}
	


};


#endif	
