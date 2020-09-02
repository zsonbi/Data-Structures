#pragma once

template<typename T>
struct Node {
	T data;
	Node* Next;
};

template<typename T>
class List
{
private:
	size_t CurrentSize = 0;//Number of Elements in the List
	Node<T>* Head = nullptr;//Pointer to the Head
	Node<T>* Tail = nullptr;//Pointer to the Tail

	//Checks if the list is empty
	bool IsEmpty() {
		return CurrentSize == 0;
	}

	//Gets the indexed element's pointer
	Node<T>* GetIndex(size_t index) {
		Node<T>* output = Head;
		for (size_t i = 0; i < index; i++)
		{
			output = (*output).Next;
		}
		return output;
	}

public:
	//Add a new element to the List
	void Add(T input) {
		struct Node<T>* node = (Node<T>*)malloc(sizeof(Node<T>));

		if (CurrentSize == 0) {
			Head = node;
			Tail = node;
		}
		else {
			(*Tail).Next = node;
			Tail = node;
		}
		(*node).data = input;
		(*node).Next = nullptr;

		CurrentSize++;
	}

	//Returns the indexed element
	T& operator [](size_t index) {
		if (IsEmpty()) {
			throw "The List is empty";
		}

		if (CurrentSize <= index) {
			throw "Index out of Bounds";
		}

		return (*GetIndex(index)).data;
	}

	//Removes a specific object from the List
	void Remove(T input) {
		if (IsEmpty()) {
			throw "The List is empty";
		}

		//This will point to the object we want to remove
		Node<T>* pointer = Head;

		//If the first element is the object we want to remove
		if ((*pointer).data == input) {
			Head = (*pointer).Next;
			delete pointer;
			CurrentSize--;
			return;
		}//if

		for (size_t i = 0; i < CurrentSize; i++)
		{
			//Test for if it's the last element
			if ((*pointer).Next != nullptr) {
				if ((*(*pointer).Next).data == input) {
					break;
				}//if
				//Make the pointer point to the next node
				pointer = (*pointer).Next;
			}//if
			//If we reached the end without getting a match
			else
				throw "There is no element like this in the List";
		}//for

		if (Tail == (*pointer).Next) {
			Tail = pointer;
			delete (*pointer).Next;
			(*Tail).Next = nullptr;
		}//if
		else {
			Node<T>* temp = (*(*pointer).Next).Next;
			delete (*pointer).Next;
			(*pointer).Next = temp;
		}//else
		CurrentSize--;
	}

	//Removes an object from the List at the specified index
	void RemoveAt(size_t index) {
		//Throws an error if the list is empty
		if (IsEmpty()) {
			throw "The List is empty";
		}
		//Pointer to the element before the element to remove
		Node<T>* pointer = Head;
		//So if we need to remove the first element
		if (index == 0) {
			Head = (*Head).Next;
			delete (pointer);
			--CurrentSize;
			return;
		}
		//Search for the element
		pointer = GetIndex(index - 1);

		//A temporary pointer to the object we want to remove
		Node<T>* tempPointer;
		tempPointer = (*pointer).Next;
		(*pointer).Next = (*tempPointer).Next;
		//So that we replace the Tail if we removed the last element
		if (index == CurrentSize - 1) {
			Tail = pointer;
			(*Tail).Next = nullptr;
		}

		delete (tempPointer);
		--CurrentSize;
	}

	//Returns the number of objects in the List
	size_t Count() {
		return CurrentSize;
	}

	//BubbleSort Algorithm
	void Sort() {
		//If we try to sort an empty array throw an exception
		if (IsEmpty()) {
			throw "The List is empty";
		}

		bool sorted = false;
		while (!sorted) {
			sorted = true;
			//This will be our pointer for traversal
			Node<T>* pointer = Head;
			//Go through the list
			for (size_t i = 0; i < CurrentSize - 1; i++)
			{
				//If we find a smaller element than the current one we swap their data
				if ((*pointer).data > (*(*pointer).Next).data) {
					T temp = (*pointer).data;
					(*pointer).data = (*(*pointer).Next).data;
					(*(*pointer).Next).data = temp;
					sorted = false;
				}//if
				pointer = (*pointer).Next;
			}//for
		}
	}

	//See if the List contains that element
	bool Contains(T input) {
		//Pointer which we will traverse the list
		Node<T>* pointer = Head;

		for (size_t i = 0; i < CurrentSize; i++)
		{
			//If we found an element which matches our input return true
			if ((*pointer).data == input) {
				return true;
			}//if

			//point to the next element
			pointer = (*pointer).Next;
		}//for

		//if there were no element which matches the input return false
		return false;
	}

	//Returns the First element of the list
	T First() {
		return (*Head).data;
	}

	//Returns the Last element of the list
	T Last() {
		return (*Tail).data;
	}
};
