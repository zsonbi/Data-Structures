// Data Structures.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "Stack.h"
#include "Queue.h"
#include "DynamicArray.h"
#include "HashTable.h"
#include "Dictionary.h"
#include "AVL.h"

int main()
{
	//Tests
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

	std::cout << "-------------------------------Hash Table-----------------------------\n";

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

	std::cout << hashTable.ContainsKey(tenHash) << std::endl;
	std::cout << hashTable.ContainsKey(idkHash) << std::endl;
	std::cout << hashTable.ContainsKey(42) << std::endl;
	std::cout << "Indexing: " << hashTable[tenHash] << std::endl;

	hashTable.RemoveElement(663);
	hashTable.RemoveElement(66325);
	hashTable.RemoveElement(624);

	std::cout << "--------------------------------------Dictionary-----------------------------------------" << std::endl;
	Dictionary<int, long> dictionary;
	dictionary.Add(10, 5200);
	dictionary.Add(15, 5362);
	dictionary.Add(18, 5201);
	dictionary.Add(62, 5201);
	dictionary.Add(31, 5201);
	dictionary.Add(131, 5201);
	dictionary.Add(162, 5261);

	dictionary.RemoveByKey(162);

	std::cout << "ContainsKey (should be true):" << dictionary.ContainsKey(10) << std::endl;
	std::cout << "ContainsKey (should be true):" << dictionary.ContainsKey(15) << std::endl;
	std::cout << "ContainsKey (should be true):" << dictionary.ContainsKey(18) << std::endl;
	std::cout << "ContainsKey (should be true):" << dictionary.ContainsKey(62) << std::endl;
	std::cout << "ContainsKey (should be true):" << dictionary.ContainsKey(31) << std::endl;
	std::cout << "ContainsKey (should be false):" << dictionary.ContainsKey(32361) << std::endl;
	std::cout << "ContainsKey (should be false):" << dictionary.ContainsKey(31512) << std::endl;
	std::cout << "ContainsKey (should be false):" << dictionary.ContainsKey(31231) << std::endl;

	std::cout << "Indexing:[10 - 5200] " << dictionary[10] << std::endl;
	std::cout << "Indexing:[15 - 5362] " << dictionary[15] << std::endl;
	std::cout << "Indexing:[18 - 5201] " << dictionary[18] << std::endl;
	std::cout << "Indexing:[62 - 5201] " << dictionary[62] << std::endl;
	std::cout << "Indexing:[31 - 5201] " << dictionary[31] << std::endl;
	std::cout << "Indexing:[131 - 5201] " << dictionary[131] << std::endl;

	//AVL tests
	std::cout << "--------------------------------------AVL-----------------------------------------" << std::endl;
	AVL<int> avl;
	avl.Insert(10, 15);
	avl.Insert(20, 60);
	avl.Insert(30, 50);
	int res = *avl.Search(20);
	if (res == 60) {
		std::cout << "Passed test 1" << std::endl;
	}
	else {
		std::cout << "Failed test 1" << std::endl;
	}

	avl.Delete(10);
	avl.Delete(20);
	avl.Delete(30);
	if (avl.NumberOfNodes() == 0) {
		std::cout << "Passed test 2" << std::endl;
	}
	else {
		std::cout << "Failed test 2" << std::endl;
	}

	avl.Insert(50, 10);
	avl.Insert(25, 10);
	avl.Insert(15, 10);
	avl.Insert(30, 10);
	avl.Insert(20, 10);

	if (avl.HeightOfTree() == 3) {
		std::cout << "Passed test 3" << std::endl;
	}
	else {
		std::cout << "Failed test 3" << std::endl;
	}
	avl.Delete(20);
	if (avl.HeightOfTree() == 3) {
		std::cout << "Passed test 4" << std::endl;
	}
	else {
		std::cout << "Failed test 4" << std::endl;
	}
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