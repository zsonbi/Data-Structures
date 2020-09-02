#pragma once

template<typename T, size_t S>
class Array
{
private:
	T my_Data[S];

public:
	//The size (this will be calculated during the compile time)
	constexpr size_t Length() const { return S; }

	//Returns the indexed data value from the array
	T& operator[](size_t index) { return my_Data[index]; }

	//Returns the pointer to the array
	T* Data() { return my_Data; }

	//Sorts the array in an Ascending order
	void OrderByAscending() {
		bool sorted;
		do
		{
			sorted = true;
			for (size_t i = 0; i < Length() - 1; i++)
			{
				if (my_Data[i] > my_Data[i + 1]) {
					T temp = my_Data[i];
					my_Data[i] = my_Data[i + 1];
					my_Data[i + 1] = temp;
					sorted = false;
				}
			}
		} while (!sorted);
	}

	//Sorts the array in an Ascending order
	void OrderByDescending() {
		bool sorted;
		do
		{
			sorted = true;
			for (size_t i = 0; i < Length() - 1; i++)
			{
				if (my_Data[i] < my_Data[i + 1]) {
					T temp = my_Data[i];
					my_Data[i] = my_Data[i + 1];
					my_Data[i + 1] = temp;
					sorted = false;
				}
			}
		} while (!sorted);
	}
};
