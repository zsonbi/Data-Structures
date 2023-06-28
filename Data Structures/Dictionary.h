#pragma once
#ifndef DICTIONARY_H_INCLUDED
#define DICTIONARY_H_INCLUDED
#include <functional>
#include <iostream>
#define BUCKET_THRESHOLD 0.7f //If the usedBuckets is above this resize the table
/// <summary>
/// Creates a new dictionary
/// </summary>
/// <typeparam name="K">Type of the key</typeparam>
/// <typeparam name="T">Type of the element</typeparam>
template <typename K, typename T>
class Dictionary {
private:
	struct KeyValuePair {
		int key;
		T value;
	};
private:
	const static unsigned char baseSize = 8;

	const KeyValuePair tombStone = { -1 };	//This is a placeholder for deleted cells
	const KeyValuePair emptyCell = { -2 };	//This is a placeholder for empty cells

	int currentSize; //The current size of the hash table
	KeyValuePair* buckets; //The buckets where the data is stored
	float usedBuckets = 0.0f; //The percentage of how much of the buckets are used

public:
	Dictionary() {
		currentSize = baseSize;
		buckets = new KeyValuePair[baseSize];

		for (size_t i = 0; i < currentSize; i++)
		{
			buckets[i] = emptyCell;
		}
	}

	//Frees up the memory
	~Dictionary() {
		delete[] buckets;
	}

private:
	/// <summary>
	/// Creates the hash
	/// </summary>
	/// <param name="input"></param>
	/// <returns>The hash</returns>
	int Hash(K input)
	{
		return std::hash<K>()(input);
	}

	/// <summary>
	/// Adds an element to the dictionary
	/// </summary>
	/// <param name="key">The key(hash) which will be used by the table</param>
	/// <param name="element">The element we want to add</param>
	/// <returns>The key</returns>
	void AddElement(int key, const T& element) {
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
	/// Resizes the dictionary
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

public:

	/// <summary>
	/// Adds an element to the dictionary
	/// </summary>
	/// <param name="key">The key which will be used by the table</param>
	/// <param name="element">The element we want to add</param>
	/// <returns>The key</returns>
	void Add(K key, const T& element) {
		size_t index;
		int hash = Hash(key);
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
	}

	/// <summary>
	/// Checks if the dictionary contains that key
	/// </summary>
	/// <param name="key">The key to search for</param>
	/// <returns>true if it has that key false if it isn't</returns>
	bool ContainsKey(const K& key) {
		size_t index;
		int hash = Hash(key);
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
				return false;
			}
			else if (buckets[index].key == hash) {
				return true;
			}

			index = (index + 1) % currentSize;
		}
	}

	/// <summary>
	/// Removes an element from the dictionary
	/// </summary>
	/// <param name="key">The element's key</param>
	/// <returns>
	/// 0-success
	/// 1-not found
	/// </returns>
	unsigned char RemoveByKey(const K& key) {
		size_t index;
		int hash = Hash(key);
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
	/// Get an element from the dictionary
	/// </summary>
	/// <param name="key">The key how we will determine the element</param>
	/// <returns>The element if the table contains it NULL if it isn't</returns>
	T& GetElement(const K& key) {
		int hash = Hash(key);
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
				throw "The cell is empty";

			}
			else if (buckets[index].key == hash) {
				return buckets[index].value;
			}

			index = (index + 1) % currentSize;
		}
	}

	/// <summary>
	/// Get an element from the dictionary
	/// </summary>
	/// <param name="key">The key how we will determine the element</param>
	/// <returns>The element if the table contains it NULL if it isn't</returns>
	const T& GetElement(const K& key) const {
		int hash = Hash(key);
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
				throw "The cell is empty";

			}
			else if (buckets[index].key == hash) {
				return buckets[index].value;
			}

			index = (index + 1) % currentSize;
		}
	}

	/// <summary>
	/// Get an element from the dictionary
	/// </summary>
	/// <param name="key">The key how we will determine the element</param>
	/// <returns>The element if the table contains it NULL if it isn't</returns>
	inline T& operator[](const K& key) {
		return GetElement(key);
	}

	/// <summary>
	/// Get an element from the dictionary
	/// </summary>
	/// <param name="key">The key how we will determine the element</param>
	/// <returns>The element if the table contains it NULL if it isn't</returns>
	inline const T& operator[](const K& key) const {
		return GetElement(key);
	}
};

#endif
