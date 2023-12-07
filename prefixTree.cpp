////////////////////////////////////////////////////////
// ECE 3514, Project 4, Ashton Bryce Eller
//
// File name: prefixTree.cpp
// Description: Implementation file that holds the instantiations for adding 
//				removing nodes, and printing information from the given tree
// Date: 12/06/2023 
//



#include "prefixTree.h"
#include "treeNode.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

prefixTree::prefixTree() 
{
}  // end default constructor

prefixTree::prefixTree(std::string filename) {

	// opens file
	std::ifstream file(filename);

	if (!file.is_open())
	{
		// throw error if file cannot be opended
		throw std::runtime_error("Could not open file.");
	}

	std::string line;
	while (std::getline(file, line))
	{
		size_t colon = line.find(":");
		if (colon != std::string::npos)
		{
			// extract netId and port number
			std::string netId = line.substr(0, colon);
			int port = std::stoi(line.substr(colon + 1));

			// add the routing entry
			add(netId, port);
			std::cout << "Net Id: " << netId << " Port: " << port << std::endl;
		}
		else 
		{
			throw std::invalid_argument("Invalid line format");
		}
	}

	// close file
	file.close();

}



prefixTree::~prefixTree()
{
	clear();
}


std::shared_ptr<treeNode> prefixTree::findNode(std::shared_ptr<treeNode> currNode,
	const std::string& netid) const 
{
	if (currNode == nullptr) 
	{
		// Node cannot be found in tree
		return nullptr; 
	}

	if (currNode->getNetId() == netid)
	{
		// currNode's netid equals inputted netid
		return currNode; 
	}

	// Recursive case that will traverse the left subtree until node is found 
	// or there are no more nodes to left of inputted node
	std::shared_ptr<treeNode> left = findNode(currNode->getLeftChildPtr(), netid);
	if (left != nullptr)
	{
		return left;
	}

	// Recursive case that traverses right subtree until node is found,
	// or there are no nodes left, which then it returns a nullptr
	std::shared_ptr<treeNode> right = findNode(currNode->getRightChildPtr(), netid);
	return right; 

}

 int prefixTree::helpFindPort(std::shared_ptr<treeNode> currNode, 
	const std::string& ipaddr) const
{
	 std::cout << "Checking node " << currNode->getNetId() << ", " << currNode->getPort() << std::endl; 
	 // if root node is null, return -1
	 if (currNode == nullptr)
	 {
		 std::cout << "Node is null. Node: " << currNode->getNetId() << ", " << currNode->getPort() << std::endl;
		 return -1;
	 }

	 // check if node's netid is prefix of given ipaddr
	 if (ipaddr.find(currNode->getNetId()) == 0)
	 {
		 std::cout << "Checking this node. Node: " << currNode->getNetId() << ", " << currNode->getPort() << std::endl;
		 if (currNode->getPort() >= 0)
		 {
			 std::cout << "Valid routing entry found." << currNode->getNetId() << ", " << currNode->getPort() << std::endl;
			 // if valid routing entry, return port entry
			 return currNode->getPort();
		 }
	 }


	 // traverses left subtree
	 int left = helpFindPort(currNode->getLeftChildPtr(), ipaddr);
	 std::cout << "Valid routing entry found in LEFT subtree." << currNode->getNetId() << ", " << currNode->getPort() << std::endl;
	 // if valid routing entry found, return port
	 if (left != -1)
	 {
		 std::cout << "Valid routing entry found in RIGHT subtree." << currNode->getNetId() << ", " << currNode->getPort() << std::endl;
		 return left;
	 }
	

	 // return valid port entry or -1 if not found
	 int right = helpFindPort(currNode->getRightChildPtr(), ipaddr);
	 std::cout << "Valid routing entry found in RIGHT subtree." << currNode->getNetId() << ", " << currNode->getPort() << std::endl;
	 return right;

}



bool prefixTree::add(const std::string netid, const int port) 
{
	std::shared_ptr<treeNode> node = std::make_shared<treeNode>(netid, port);

	if (rootPtr == nullptr)
	{
		// if tree is empty, make the new node the root
		rootPtr = node; 
		return true;
	}
	else
	{
		std::shared_ptr<treeNode> curr = rootPtr;
		std::shared_ptr<treeNode> parent = nullptr; 

		// traverse tree until leaf node is found
		while (curr != nullptr)
		{
			parent = curr;

			if (netid.compare(curr->getNetId()) < 0)
			{
				// if netId is less than zero in comparison to root, return left child ptr
				curr = curr->getLeftChildPtr();
			}
			else
			{
				// otherwise, return right child ptr
				curr = curr->getRightChildPtr();
			}
		}
			
			
		if (parent != nullptr)
		{
			if (netid.compare(parent->getNetId()) < 0)
			{
				// add node as left child ptr if netid is less than 0 in comparison to parent
				parent->setLeftChildPtr(node);
			}
			else
			{
				// add node as right child ptr if netid is greater than 0 in comparison to parent
				parent->setRightChildPtr(node);
			}

			return true;
		}
		else
		{
			// if node does not exist, return false
			return false;
		}
	}
}

int prefixTree::findPort(std::string ipaddr) const
{
	// starts search from root of tree
	return helpFindPort(rootPtr, ipaddr);
}


std::shared_ptr<treeNode> prefixTree::findSuccessor(std::shared_ptr<treeNode> curr)
{
	// find leftmost node of the current node
	while (curr->getLeftChildPtr() != nullptr)
	{
		curr = curr->getLeftChildPtr();
	}
	return curr; 
}


bool prefixTree::removeHelper(std::shared_ptr<treeNode>& curr, const std::string& prefix)
{
	if (curr == nullptr)
	{
		// no prefix found
		return false; 
	}

	// check if prefix is prefix of current node's netId
	if (curr->getNetId() == prefix)
	{
		// prefix found, remove it 
		removeNode(curr);
	}
	else if (prefix < curr->getNetId())
	{
		// search in left/right trees
		 return removeHelper(curr->getLeftChildPtr(), prefix);
	}
	else
	{
		 return removeHelper(curr->getRightChildPtr(), prefix);
	}
}

bool prefixTree::removeNode(std::shared_ptr<treeNode>& node)
{
	if (node->isLeaf())
	{
		// node is leaf, remove it
		node = nullptr;
	}
	else if (node->getLeftChildPtr() == nullptr)
	{
		// node only has right child, replace it with right child
		node = node->getRightChildPtr();
	}
	else if (node->getRightChildPtr() == nullptr)
	{
		// node only has left child, replace it with left child
		node = node->getLeftChildPtr();
	}
	else
	{
		// if node has both a left and right child, find in-order successor
		std::shared_ptr<treeNode> successor = findSuccessor(node->getRightChildPtr());

		// copy data to current node
		node->setNetId(successor->getNetId()); 
		node->setPort(successor->getPort()); 

		// remove node
		removeNode(node->getRightChildPtr());
	}

	return true; 
}

bool prefixTree::remove(const std::string prefix)
{
	if (rootPtr == nullptr)
	{
		// tree is empty, nothing to remove
		return false;
	}

	return removeHelper(rootPtr, prefix);
}

void prefixTree::clearHelper(std::shared_ptr<treeNode>& curr)
{
	if (curr != nullptr)
	{
		// recursively clear the left and right subtrees
		clearHelper(curr->getLeftChildPtr());
		clearHelper(curr->getRightChildPtr());

		// delete the current node
		curr = nullptr; 
	}
}

void prefixTree::clear()
{
	clearHelper(rootPtr);
	rootPtr = nullptr; 
}


std::string prefixTree::postorderTraverseHelper(std::string visit(std::shared_ptr<treeNode> NodePtr), std::shared_ptr<treeNode> treePtr) const
{
	if (treePtr == nullptr)
	{
		// tree is empty
		return ""; 
	}

	std::string result = postorderTraverseHelper(visit, treePtr->getLeftChildPtr());
	result += postorderTraverseHelper(visit, treePtr->getRightChildPtr());
	result += visit(treePtr);

	return result;
}



RoutingEntry  prefixTree::getRoutingEntry(const std::string netId) const 
{
	std::shared_ptr<treeNode> node = findNode(rootPtr, netId);

	if (node != nullptr)
	{
		// node with the given netId was found, return its routing entry
		return node->getRoutingEntry();
	}

	// Node not found, return a default RoutingEntry
	return RoutingEntry{ "", -1 };
}

std::string prefixTree::postorderTraverse(std::string visit(std::shared_ptr<treeNode> NodePtr)) const {
	return postorderTraverseHelper(visit, rootPtr);
}



int prefixTree::getHeightHelper(std::shared_ptr<treeNode> subTreePtr) const
{
	return -1;
}

int prefixTree::getNumberOfNodesHelper(std::shared_ptr<treeNode> subTreePtr) const
{
	return -1;
}





bool prefixTree::isEmpty() const 
{
	return (rootPtr == nullptr);
}

int getHeightHelper(std::shared_ptr<treeNode> subTreePtr)
{
	// if currNode is null, return -1 (empty tree)
	if (subTreePtr == nullptr)
	{
		return -1; 
	}

	// calculate height of each subtree
	int left = getHeightHelper(subTreePtr->getLeftChildPtr());
	int right = getHeightHelper(subTreePtr->getRightChildPtr());

	// return max height plus one (rootPtr) 
	return 1 + std::max(left, right);
}

int prefixTree::getHeight() const
{
	return getHeightHelper(rootPtr); 
}


int getNumberOfNodesHelper(std::shared_ptr<treeNode> subTreePtr)
{
	// if curr node is null, return 0
	if (subTreePtr == nullptr)
	{
		return 0;
	}

	// Recursive: count current node + nodes in left/right subtrees
	return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr()) +
		getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
}

int prefixTree::getNumberOfNodes() const
{
	return getNumberOfNodesHelper(rootPtr);
}


