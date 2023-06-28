#pragma once

#include "List.h"

template<typename T>
class Stack
{
	List<T> data;

private:
	//Check if the stack is empty
	bool IsEmpty() const {
		return data.Count() == 0;
	}

public:
	//Add a new element to the top of the stack
	void push(const T& input) {
		data.Add(input);
	}

	//Returns the top element and remove it
	T& Pop() {
		//If the stack is empty throw an exception
		if (IsEmpty()) {
			throw "The Stack is empty";
		}//if
		T out = data.Last();
		//Removes the last element of the list
		data.RemoveAt(data.Count() - 1);
		return out;
	}

	//Returns the size of the stack
	size_t Size() const {
		return data.Count();
	}
};
