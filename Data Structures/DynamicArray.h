#pragma once
template<typename T>
class DynamicArray
{
	T* mydata = nullptr;
	size_t currSize = 0;
	size_t maxSize;

private:
	void ChangeSize(size_t newSize) {
		T* temp = new T[newSize];
		//Copy the contents of the previous array
		for (size_t i = 0; i < currSize; i++)
		{
			(*(temp + i)) = *(mydata + i);
		}//for
		//delete the previous data
		delete[] mydata;
		mydata = temp;
		//Change the maxsize
		maxSize = newSize;
	}

	void Trim(size_t input) {
		T* temp = new T[maxSize];
		size_t index = 0;
		//Copy the contents of the previous array but skip the nullptrs
		for (size_t i = 0; i < currSize; i++)
		{
			if (i == input) {
				continue;
			}

			(*(temp + index)) = *(mydata + i);
			index++;
		}//for
		//delete the previous data
		delete[] mydata;
		mydata = temp;
	}

public:
	//Constructor
	DynamicArray() {
		//Create a 2 size array
		ChangeSize(2);
	}

	//Indexing the data
	T& operator[](size_t index) {
		if (currSize < index) {
			throw "Index out of bounds";
		}
		return *(mydata + index);
	}

	//Indexing the data
	const T& operator[](size_t index) const {
		if (currSize < index) {
			throw "Index out of bounds";
		}
		return *(mydata + index);
	}


	//Return the current number of elements in the Vector
	size_t Length() const {
		return currSize;
	}

	//Returns the current max size of the array
	size_t MaxSize() const {
		return maxSize;
	}

	//Add a new element to the array
	void Add(const T& input) {
		if (currSize == maxSize) {
			ChangeSize(maxSize * 2);
		}
		*(mydata + currSize) = input;
		//Increment the current size of the array
		currSize++;
	}

	//Remove an element from the specific index
	void RemoveAt(size_t index) {
		if (currSize < index || index < 0) {
			throw "Index out of bounds";
		}
		//Copy the array and leave the element out which we want to remove
		Trim(index);
	}

	//Remove a specific element from the array
	void Remove(const T& input) {
		size_t index = -1;
		//Search for the input
		for (size_t i = 0; i < currSize; i++)
		{
			if (*(mydata + i) == input) {
				index = i;
				break;
			}//if
		}//for
		//Error handling
		if (index == -1) {
			throw "there is no such element in the array";
		}//if
		//Copy the array and leave the element out which we want to remove
		Trim(index);
	}

	//Make the array size the same as the number of elements in it
	void TrimToFit() {
		ChangeSize(currSize);
	}
};
