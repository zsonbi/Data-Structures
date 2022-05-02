#pragma once
#ifndef HASH_TABLE_H_INCLUDED
#define HASH_TABLE_H_INCLUDED

#include <functional>
#include <iostream>
#define BUCKET_THRESHOLD 0.7f //If the usedBuckets is above this resize the table

template <typename T>
class HashTable {
private:
	struct KeyValuePair {
		int key;
		T value;
	};
private:
	const static unsigned char baseSize = 8;
	const KeyValuePair tombStone = { -1 };
	const KeyValuePair emptyCell = { -2 };

	int currentSize; //The current size of the hash table
	KeyValuePair* buckets; //The buckets where the data is stored
	float usedBuckets = 0.0f; //The percentage of how much of the buckets are used

public:
	HashTable() {
		currentSize = baseSize;
		buckets = new KeyValuePair[baseSize];

		for (size_t i = 0; i < currentSize; i++)
		{
			buckets[i] = emptyCell;
		}
	}

	int Hash(T input)
	{
		return std::hash<T>()(input);
	}

	/// <summary>
	/// Adds an element to the hash table
	/// </summary>
	/// <param name="element">The element we want to add</param>
	/// <returns>The key</returns>
	int AddElement(T element) {
		int hash = Hash(element);
		size_t index;
		//Handle negative hash
		if (hash < 0) {
			index = abs(hash) % currentSize;
		}
		else
		{
			index = hash % currentSize;
		}

		while (buckets[index].key != emptyCell.key && buckets[index].key != tombStone.key) {
			index = (index + 1) % currentSize;
		}

		if (buckets[index].key != tombStone.key) {
			usedBuckets += 1.0f / currentSize;
		}

		buckets[index] = KeyValuePair{ hash,element };
		if (usedBuckets >= BUCKET_THRESHOLD) {
			ResizeTable(currentSize << 1);
		}
		return hash;
	}

	/// <summary>
/// Adds an element to the hash table
/// </summary>
/// <param name="key">The key(hash) which will be used by the table</param>
/// <param name="element">The element we want to add</param>
/// <returns>The key</returns>
	void AddElement(int key, T element) {
		size_t index;
		//Handle negative hash
		if (key < 0) {
			index = abs(key) % currentSize;
		}
		else
		{
			index = key % currentSize;
		}

		while (buckets[index].key != emptyCell.key && buckets[index].key != tombStone.key) {
			index = (index + 1) % currentSize;
		}

		if (buckets[index].key != tombStone.key) {
			usedBuckets += 1.0f / currentSize;
		}

		buckets[index] = KeyValuePair{ key,element };
		if (usedBuckets >= BUCKET_THRESHOLD) {
			ResizeTable(currentSize << 1);
		}
	}

	/// <summary>
	/// Removes an element from the table
	/// </summary>
	/// <param name="element">The element which was added</param>
	/// <returns>
	/// 0-success
	/// 1-not found
	/// </returns>
	unsigned char RemoveElement(T element) {
		int hash = Hash(element);
		size_t index;
		//Handle negative hash
		if (hash < 0) {
			index = abs(hash) % currentSize;
		}
		else
		{
			index = hash % currentSize;
		}
		while (true) {
			if (buckets[index].key == emptyCell.key) {
				return 1;
			}
			else if (buckets[index].key == hash) {
				buckets[index] = tombStone;

				return 0;
			}

			index = (index + 1) % currentSize;
		}

		return 255;
	}

	/// <summary>
	/// Checks if the table contains that key
	/// </summary>
	/// <param name="key">The key to search for</param>
	/// <returns>true if it has that key false if it isn't</returns>
	bool ContainsKey(int key) {
		size_t index;
		//Handle negative hash
		if (key < 0) {
			index = abs(key) % currentSize;
		}
		else
		{
			index = key % currentSize;
		}
		while (true) {
			if (buckets[index].key == emptyCell.key) {
				return false;
			}
			else if (buckets[index].key == key) {
				return true;
			}

			index = (index + 1) % currentSize;
		}
	}

	/// <summary>
	/// Removes an element from the table
	/// </summary>
	/// <param name="key">The element's key</param>
	/// <returns>
	/// 0-success
	/// 1-not found
	/// </returns>
	unsigned char RemoveByKey(int key) {
		size_t index;
		//Handle negative hash
		if (key < 0) {
			index = abs(key) % currentSize;
		}
		else
		{
			index = key % currentSize;
		}
		while (true) {
			if (buckets[index].key == emptyCell.key) {
				return 1;
			}
			else if (buckets[index].key == key) {
				buckets[index] = tombStone;

				return 0;
			}

			index = (index + 1) % currentSize;
		}

		return 255;
	}

	/// <summary>
	/// Get an element from the table
	/// </summary>
	/// <param name="key">The key how we will determine the element</param>
	/// <returns>The element if the table contains it NULL if it isn't</returns>
	T GetElement(int key) {
		size_t index;
		//Handle negative hash
		if (key < 0) {
			index = abs(key) % currentSize;
		}
		else
		{
			index = key % currentSize;
		}
		while (true) {
			if (buckets[index].key == emptyCell.key) {
				return NULL;
			}
			else if (buckets[index].key == key) {
				return buckets[index].value;
			}

			index = (index + 1) % currentSize;
		}
	}

	/// <summary>
	/// Resizes the table
	/// </summary>
	/// <param name="size">The new size</param>
	void ResizeTable(size_t size) {
		int oldSize = currentSize;
		currentSize = size;
		usedBuckets = 0.0f;
		KeyValuePair* oldBuckets = buckets;
		buckets = new KeyValuePair[size];

		for (size_t i = 0; i < currentSize; i++)
		{
			buckets[i] = emptyCell;
		}

		for (int i = 0; i < oldSize; i++)
		{
			if (oldBuckets[i].key != emptyCell.key && oldBuckets[i].key != tombStone.key) {
				AddElement(oldBuckets[i].key, oldBuckets[i].value);
			}
		}

		delete[] oldBuckets;
	}
};

#endif