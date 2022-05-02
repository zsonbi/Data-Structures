// Data Structures.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "Stack.h"
#include "Queue.h"
#include "DynamicArray.h"
#include "HashTable.h"

int main()
{
	List<int> list;
	list.Add(4);
	list.Add(45);
	list.Add(5);
	list.Add(53);
	list.Add(10);
	list.Add(10);
	list.Add(10);
	list.Add(10);
	list.Add(10);
	list[0] = 3;
	for (size_t i = 0; i < list.Count(); i++)
	{
		std::cout << list[i] << std::endl;
	}
	std::cout << "-----------" << std::endl;
	list.SelectionSort();
	for (size_t i = 0; i < list.Count(); i++)
	{
		std::cout << list[i] << std::endl;
	}

	std::cout << "Hello World!\n";

	//hashtable test
	HashTable<int> hashTable;

	int tenHash = hashTable.AddElement(10);
	hashTable.AddElement(523);
	hashTable.AddElement(6);
	hashTable.AddElement(663);
	hashTable.AddElement(6631);
	hashTable.AddElement(6635);
	hashTable.AddElement(65);
	hashTable.AddElement(676325);
	hashTable.AddElement(663225);
	hashTable.AddElement(6665);
	hashTable.AddElement(668225);
	int idkHash = hashTable.AddElement(624);

	std::cout << hashTable.GetElement(tenHash) << std::endl;
	std::cout << hashTable.GetElement(idkHash) << std::endl;

	hashTable.RemoveElement(663);
	hashTable.RemoveElement(66325);
	hashTable.RemoveElement(624);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file