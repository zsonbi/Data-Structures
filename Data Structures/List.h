#pragma once

template<typename T>
struct Node {
	T data;
	Node* next;
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
			output = (*output).next;
		}
		return output;
	}

public:
	//Add a new element to the List
	void Add(const T& input) {
		struct Node<T>* node = new Node<T>();

		if (CurrentSize == 0) {
			Head = node;
			Tail = node;
		}
		else {
			(*Tail).next = node;
			Tail = node;
		}
		(*node).data = input;
		(*node).next = nullptr;

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

	//Returns the indexed element
	const T& operator[](size_t index) const {
		if (IsEmpty()) {
			throw "The List is empty";
		}

		if (CurrentSize <= index) {
			throw "Index out of Bounds";
		}

		return (*GetIndex(index)).data;
	}


	//Removes a specific object from the List
	void Remove(const T& input) {
		if (IsEmpty()) {
			throw "The List is empty";
		}

		//This will point to the object we want to remove
		Node<T>* pointer = Head;

		//If the first element is the object we want to remove
		if ((*pointer).data == input) {
			Head = (*pointer).next;
			delete pointer;
			CurrentSize--;
			return;
		}//if

		for (size_t i = 0; i < CurrentSize; i++)
		{
			//Test for if it's the last element
			if ((*pointer).next != nullptr) {
				if ((*(*pointer).next).data == input) {
					break;
				}//if
				//Make the pointer point to the next node
				pointer = (*pointer).next;
			}//if
			//If we reached the end without getting a match
			else
				throw "There is no element like this in the List";
		}//for

		if (Tail == (*pointer).next) {
			Tail = pointer;
			delete (*pointer).next;
			(*Tail).next = nullptr;
		}//if
		else {
			Node<T>* temp = (*(*pointer).next).next;
			delete (*pointer).next;
			(*pointer).next = temp;
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
			Head = (*Head).next;
			delete (pointer);
			--CurrentSize;
			return;
		}
		//Search for the element
		pointer = GetIndex(index - 1);

		//A temporary pointer to the object we want to remove
		Node<T>* tempPointer;
		tempPointer = (*pointer).next;
		(*pointer).next = (*tempPointer).next;
		//So that we replace the Tail if we removed the last element
		if (index == CurrentSize - 1) {
			Tail = pointer;
			(*Tail).next = nullptr;
		}

		delete (tempPointer);
		--CurrentSize;
	}

	//Returns the number of objects in the List
	size_t Count() const {
		return CurrentSize;
	}

	//BubbleSort Algorithm
	void BubbleSort() {
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
				if ((*pointer).data > (*(*pointer).next).data) {
					T temp = (*pointer).data;
					(*pointer).data = (*(*pointer).next).data;
					(*(*pointer).next).data = temp;
					sorted = false;
				}//if
				pointer = (*pointer).next;
			}//for
		}
	}

	//Fast Sort
	void SelectionSort() {
		//If we try to sort an empty array throw an exception
		if (IsEmpty()) {
			throw "The List is empty";
		}

		Node<T>* prev = nullptr;
		Node<T>* biggest = nullptr;
		Node<T>* beforeBiggest = nullptr;
		Node<T>* travel = nullptr;

		//Going through the List
		for (size_t i = 0; i < CurrentSize; i++)
		{
			travel = GetIndex(i);
			biggest = travel;
			for (size_t j = i; j < CurrentSize; j++)
			{
				if ((*biggest).data < (*travel).data) {
					biggest = travel;
					beforeBiggest = GetIndex(j - 1);
				}
				travel = (*travel).next;
			}
			(*beforeBiggest).next = (*biggest).next;
			if (prev == nullptr) {
				(*biggest).next = Head;
				prev = biggest;
				Head = biggest;
			}
			else {
				(*biggest).next = (*prev).next;
				(*prev).next = biggest;
				prev = biggest;
			}
		}
		Tail = biggest;
	}

	//See if the List contains that element
	bool Contains(const T& input) const {
		//Pointer which we will traverse the list
		Node<T>* pointer = Head;

		for (size_t i = 0; i < CurrentSize; i++)
		{
			//If we found an element which matches our input return true
			if ((*pointer).data == input) {
				return true;
			}//if

			//point to the next element
			pointer = (*pointer).next;
		}//for

		//if there were no element which matches the input return false
		return false;
	}

	//Returns the First element of the list
	const T& First() const {
		return (*Head).data;
	}

	//Returns the First element of the list
	T& First() {
		return (*Head).data;
	}

	//Returns the Last element of the list
	const T& Last() const {
		return (*Tail).data;
	}

	//Returns the Last element of the list
	T& Last() {
		return (*Tail).data;
	}
};
