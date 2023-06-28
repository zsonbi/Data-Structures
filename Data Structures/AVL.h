#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

#define NOTFOUNDELEMENT NULL

template<typename T>
class AVL
{
private:
	//A single AVL node
	struct Node
	{
	public:
		//Key of the node
		int key;
		//The data which the node stores
		T data;
		//Left node (the lover key value)
		Node* leftNode;
		//Right node (the higher key value)
		Node* rightNode;
		//The height of the given subtree
		int height;
		/// <summary>
		/// Creates a new node
		/// </summary>
		/// <param name="key">Key of the node</param>
		/// <param name="data">Data of the node</param>
		Node(int key, T data) {
			this->data = data;
			this->key = key;
			this->leftNode = nullptr;
			this->rightNode = nullptr;
		}
	};
	//Root node of the AVL tree
	Node* m_Root = nullptr;
	//The number of nodes in the tree
	int count = 0;


public:
	//----------------------------------------------------------------------------------------
	//Constructor
	AVL()
	{
	}

	//---------------------------------------------------------------------------------
	//Destructor
	~AVL()
	{
		FreeAll(m_Root);
	}

	//-------------------------------------------------------------------------------------
	/// <summary>
	/// Insert the key value pair into the AVL
	/// </summary>
	/// <param name="key">The key of the node this will be used to determine the node's place</param>
	/// <param name="val">The value of the node</param>
	/// <returns>true->succeeded, false->failed</returns>
	bool Insert(int key, const T& val) {
		Node* newNode = nullptr;
		//If it's the first node set it as the tree
		if (nullptr == m_Root) {
			this->m_Root = new Node(key, val);
			newNode = this->m_Root;
		}
		//Insert it at the appropiate side
		else {
			//Traverse the tree and find the parent of the new node
			Node* lastNode = GetLastNode(key, m_Root);
			//Error detection
			if (nullptr == lastNode) {
				return false;
			}
			if (lastNode->key > key) {
				lastNode->leftNode = new Node(key, val);
				newNode = lastNode->leftNode;
			}
			else {
				lastNode->rightNode = new Node(key, val);
				newNode = lastNode->rightNode;
			}
		}
		//Error detection
		if (newNode != nullptr) {
			//Rebalance tree
			do
			{
				UpdateHeight(m_Root);
			} while (Rebalance(m_Root, m_Root));
			count++;
			return true;
		}
		else {
			return false;
		}
	}

	//----------------------------------------------------------------------------------------
	/// <summary>
	/// Deletes the node with the given key (in case of multiple keys the first occurance will be deleted)
	/// </summary>
	/// <param name="key">The key of the node to be deleted</param>
	/// <returns>True->success, false->failure</returns>
	bool Delete(int key) {
		//If there are no nodes in the tree
		if (nullptr == m_Root)
		{
			return false;
		}
		//Find the node and it's parent
		Node* parent;
		Node* lastNode = foundNode(key, m_Root, &parent);
		//Delete it
		DeleteGivenNode(lastNode, parent);
		//Rebalance the tree
		do
		{
			UpdateHeight(m_Root);
		} while (Rebalance(m_Root, m_Root));
		return true;
	}

	//----------------------------------------------------------------------------------------
	/// <summary>
	/// Search the AVL for the given key and return it's value
	/// </summary>
	/// <param name="key">the key to the node</param>
	/// <returns>The node's value, in case the key is not in the tree return NULL</returns>
	T* Search(int key) {
		if (nullptr == m_Root)
		{
			return nullptr;
		}
		Node* parent;
		Node* lastNode = foundNode(key, m_Root, &parent);
		if (nullptr != lastNode)
		{
			return &lastNode->data;
		}
		else
		{
			return nullptr;
		}
	}

	//----------------------------------------------------------------------------------------
	/// <summary>
	/// Gets the height of the tree
	/// </summary>
	/// <returns>The height</returns>
	int HeightOfTree() {
		return this->m_Root->height;
	}

	//----------------------------------------------------------------------------------------
	/// <summary>
	/// Gets the number of nodes in the tree
	/// </summary>
	/// <returns>Node count</returns>
	int NumberOfNodes() {
		return count;
	}
private:

	//----------------------------------------------------------------------------------------
	/// <summary>
	/// Deletes the given node
	/// </summary>
	/// <param name="node">The node to delete</param>
	/// <param name="parent">It's parent</param>
	void DeleteGivenNode(Node* node, Node* parent) {

		Node* newChild = nullptr;
		//If the node has 2 childs
		if (nullptr != node->leftNode) {
			if (nullptr != node->rightNode) {
				//Find the new sucessor to the node
				Node* successor = node->rightNode;
				Node* successorParent = node;
				while (successor->leftNode != nullptr) {
					successorParent = successor;
					successor = successor->leftNode;
				}

				//Update the key and the data of the node to delete
				node->key = successor->key;
				node->data = successor->data;
				//Update the node to the delete to the successor's node since the data and key is already moved
				node = successor;
				parent = successorParent;
			}

		}
		//If it only has a right child
		else if (nullptr != node->rightNode) {
			newChild = node->rightNode;
		}
		//If it only has a left child (or no child)
		else {
			newChild = node->leftNode;
		}
		//Update the Root if there was no parent found
		if (parent == nullptr) {
			m_Root = newChild;
		}
		//Update the proper node of the parent to the new child node
		else if (parent->leftNode == node) {
			parent->leftNode = newChild;
		}
		else {
			parent->rightNode = newChild;
		}
		//Free the memory
		delete node;
		count--;
	}

	//----------------------------------------------------------------------------------------
	/// <summary>
	/// Rebalances the AVL tree
	/// </summary>
	/// <param name="currNode">The node which is checked for imbalances</param>
	/// <param name="parentNode">The parent of the current node</param>
	/// <returns>true->There was node balancing, false->There was no node balancing</returns>
	bool Rebalance(Node* currNode, Node* parentNode) {
		//Recursion exit condition
		if (currNode == nullptr) {
			return false;
		}
		//Calculate the difference of the 2 heights of the node's subtrees
		int rootDiff = CalcDiff(currNode);
		//If the node's rootDiff is bigger than 1 then it is left heavy
		if (rootDiff > 1) {
			int childDiff = CalcDiff(currNode->leftNode);

			if (childDiff == 1) {
				LLRotation(currNode, parentNode);
			}
			else if (childDiff == -1) {
				LRRotation(currNode, parentNode);
			}
			//If we can't decide which rotation to use try it with the child
			else {
				Rebalance(currNode->leftNode, currNode);
			}
			return true;
		}
		//If the node's rootDiff is bigger than (-1) then it is right heavy
		else if (rootDiff < -1) {
			int childDiff = CalcDiff(currNode->rightNode);

			if (childDiff == 1) {
				RLRotation(currNode, parentNode);
			}
			else if (childDiff == -1) {
				RRRotation(currNode, parentNode);
			}
			//If we can't decide which rotation to use try it with the child

			else {
				Rebalance(currNode->rightNode, currNode);
			}
			return true;
		}
		//If it is balanced continue the recursion
		else {
			bool leftRes = false;
			bool rightRes = false;
			if (nullptr != currNode->leftNode)
			{
				leftRes = Rebalance(currNode->leftNode, currNode);
			}
			if (!leftRes && nullptr != currNode->rightNode) {
				rightRes = Rebalance(currNode->rightNode, currNode);
			}
			return leftRes || rightRes;
		}
	}

	//----------------------------------------------------------------------------------------------------
	/// <summary>
	/// Calculates a node's chilren's height difference
	/// </summary>
	/// <param name="nodeToCalc">The node to calculate</param>
	/// <returns>The difference optimally [(-2),2]</returns>
	int CalcDiff(Node* nodeToCalc) {
		int res;
		//Check for nullptrs
		if (nullptr == nodeToCalc->leftNode) {
			if (nullptr == nodeToCalc->rightNode) {
				res = 0;
			}
			else {
				res = 0 - nodeToCalc->rightNode->height;
			}
		}
		else
		{
			if (nullptr == nodeToCalc->rightNode) {
				res = nodeToCalc->leftNode->height;
			}
			else {
				res = nodeToCalc->leftNode->height - nodeToCalc->rightNode->height;
			}
		}
		return res;
	}

	//----------------------------------------------------------------------------------------
	/// <summary>
	/// Do a right right rotation
	/// </summary>
	/// <param name="rootNode">The root for the rotation</param>
	/// <param name="parentNode">The parent of the root</param>
	void RRRotation(Node* rootNode, Node* parentNode) {
		//Rotate the nodes
		Node* newRoot = rootNode->rightNode;
		Node* tempLeftNode = newRoot->leftNode;
		newRoot->leftNode = rootNode;
		//Reset the rightNode of the root so we not create a circular reference
		rootNode->rightNode = nullptr;
		//If there was 2 nodes for the rootNode get a new plate for the node
		if (nullptr != tempLeftNode)
		{
			Node* curr = newRoot;
			do
			{
				if (curr->key > tempLeftNode->key)
				{
					if (nullptr == curr->leftNode) {
						curr->leftNode = tempLeftNode;
						break;
					}
					else {
						curr = curr->leftNode;
					}
				}
				else {
					if (nullptr == curr->rightNode) {
						curr->rightNode = tempLeftNode;
						break;
					}
					else {
						curr = curr->rightNode;
					}
				}
			} while (true);
		}
		//If it is needed update the root
		if (rootNode == m_Root) {
			m_Root = newRoot;
		}
		//Otherwise update the parent't children
		else {
			if (parentNode->leftNode == rootNode) {
				parentNode->leftNode = newRoot;
			}
			else {
				parentNode->rightNode = newRoot;
			}
		}

	}

	//----------------------------------------------------------------------------------------
	/// <summary>
	/// Do a left left rotation
	/// </summary>
	/// <param name="rootNode">The root for the rotation</param>
	/// <param name="parentNode">The parent of the root</param>
	void LLRotation(Node* rootNode, Node* parentNode) {
		//Rotate the nodes
		Node* newRoot = rootNode->leftNode;
		Node* tempRightNode = newRoot->rightNode;
		newRoot->rightNode = rootNode;
		//Reset the leftNode of the root so we not create a circular reference
		rootNode->leftNode = nullptr;
		//If there was 2 nodes for the rootNode get a new plate for the node
		if (nullptr != tempRightNode)
		{
			Node* curr = newRoot;
			do
			{
				if (curr->key > tempRightNode->key)
				{
					if (nullptr == curr->leftNode) {
						curr->leftNode = tempRightNode;
						break;
					}
					else {
						curr = curr->leftNode;
					}
				}
				else {
					if (nullptr == curr->rightNode) {
						curr->rightNode = tempRightNode;
						break;
					}
					else {
						curr = curr->rightNode;
					}
				}
			} while (true);
		}
		//If it is needed update the root
		if (rootNode == m_Root) {
			m_Root = newRoot;
		}
		//Otherwise update the parent't children
		else {
			if (parentNode->leftNode == rootNode) {
				parentNode->leftNode = newRoot;
			}
			else {
				parentNode->rightNode = newRoot;
			}
		}

	}

	//-------------------------------------------------------------------------------------------
	/// <summary>
	/// Right left rotation contains an LL rotation and an RR Rotation
	/// </summary>
	/// <param name="rootNode">The root for the rotation</param>
	/// <param name="parentNode">The parent of the root</param>
	void RLRotation(Node* rootNode, Node* parentNode) {
		LLRotation(rootNode->rightNode, rootNode);
		RRRotation(rootNode, parentNode);
	}

	//-------------------------------------------------------------------------------------------
	/// <summary>
	/// Left right rotation contains an RR rotation and an LL Rotation
	/// </summary>
	/// <param name="rootNode">The root for the rotation</param>
	/// <param name="parentNode">The parent of the root</param>
	void LRRotation(Node* rootNode, Node* parentNode) {
		RRRotation(rootNode->leftNode, rootNode);
		LLRotation(rootNode, parentNode);
	}

	//----------------------------------------------------------------------------------------------
	/// <summary>
	/// Updates the height of every node in the tree
	/// </summary>
	/// <param name="currNode">The current node in the recursion</param>
	/// <returns>The height which the currNode was calculated</returns>
	int UpdateHeight(Node* currNode) {
		if (nullptr == currNode) {
			return 0;
		}
		int leftChildHeight = UpdateHeight(currNode->leftNode);
		int rightChildHeight = UpdateHeight(currNode->rightNode);

		if (leftChildHeight >= rightChildHeight) {
			currNode->height = 1 + leftChildHeight;
		}
		else {
			currNode->height = 1 + rightChildHeight;
		}
		return currNode->height;

	}

	//--------------------------------------------------------------------------------------------
	/// <summary>
	/// Frees the memory the tree has allocated
	/// </summary>
	/// <param name="currNode">The current node in the recursion</param>
	void FreeAll(Node* currNode) {
		if (nullptr == currNode) {
			return;
		}
		FreeAll(currNode->leftNode);
		FreeAll(currNode->rightNode);

		delete currNode;
	}


	//----------------------------------------------------------------------------------------------
	/// <summary>
	///Get the node with the exact key
	/// </summary>
	/// <param name="key">The key to search for</param>
	/// <param name="currNode">The current node</param>
	/// <param name="parent">Reference to the parent</param>
	/// <returns>The node with the key if found or nullptr if we couldn't find it and the parent</returns>
	Node* foundNode(int key, Node* currNode, Node** parent) {
		*parent = nullptr;
		if (nullptr == currNode)
		{
			return nullptr;
		}
		do
		{


			if (currNode->key == key) {
				return currNode;
			}
			*parent = currNode;
			if (currNode->key > key) {
				if (nullptr != currNode->leftNode) {
					currNode = currNode->leftNode;
				}
				else {
					return nullptr;
				}
			}
			else {
				if (nullptr != currNode->rightNode) {
					currNode = currNode->rightNode;
				}
				else {
					return nullptr;
				}
			}
		} while (true);
	}

	//----------------------------------------------------------------------------------------------
	/// <summary>
	/// Gets the node which could be the parent of the key we want to insert
	/// </summary>
	/// <param name="key">The key</param>
	/// <param name="currNode">The current node</param>
	/// <returns>The node which will be the parent or nullptr if the tree is empty</returns>
	Node* GetLastNode(int key, Node* currNode) {
		//Error detection
		if (nullptr == currNode)
		{
			return nullptr;
		}
		//Go left if the key is smaller than the node's
		if (currNode->key > key) {
			if (nullptr != currNode->leftNode) {
				return GetLastNode(key, currNode->leftNode);
			}
			else {
				return currNode;
			}
		}
		//Or go right
		else {
			if (nullptr != currNode->rightNode) {
				return GetLastNode(key, currNode->rightNode);
			}
			else {
				return currNode;
			}
		}
	}
};



#endif // !AVL_H_INCLUDED
