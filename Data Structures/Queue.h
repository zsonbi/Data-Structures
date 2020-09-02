#pragma once

#include "List.h"
template <typename T>
class Queue
{
	List<T> data;

private:
	//Check if the stack is empty
	bool IsEmpty() {
		return data.Count() == 0;
	}

public:
	//Add a new element to the top of the queue
	void push(T input) {
		data.Add(input);
	}

	//Returns the top element and remove it
	T Pop() {
		//If the stack is empty throw an exception
		if (IsEmpty()) {
			throw "The Queue is empty";
		}//if
		T out = data.First();
		//Removes the last element of the list
		data.RemoveAt(0);
		return out;
	}

	//Returns the size of the queue
	size_t Size() {
		return data.Count();
	}
};
