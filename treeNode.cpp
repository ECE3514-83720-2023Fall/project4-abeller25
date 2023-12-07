////////////////////////////////////////////////////////
// ECE 3514, Project 4, Ashton Bryce Eller
//
// File name: treeNode.cpp 
// Description: Implementation file that holds the instantiations for  
//				getting netIds, port, and childPtrs for a tree node
// Date: 12/06/2023 
//


#include "treeNode.h"



treeNode::treeNode() : rtEntry({ "", -1 }), leftChildPtr(nullptr), rightChildPtr(nullptr), removed(0)
{
	
}

treeNode::treeNode(const std::string netId_in,  int port_in) 
	: rtEntry({ netId_in, port_in }), leftChildPtr(nullptr), rightChildPtr(nullptr), removed(0)
{
	
}

void treeNode::setNetId(const std::string netId_in) 
{
	rtEntry.netId = netId_in; 
}
void treeNode::setPort(const int port_in) 
{
	rtEntry.port = port_in; 
}

void treeNode::markAsRemoved()
{
	// set removed value to true
	removed = true;
}

bool treeNode::isRemoved() const
{
	// returns if node has been removed
	return removed;
}

std::string treeNode::getNetId() const 
{
	return rtEntry.netId;
}
 int treeNode::getPort() const 
{
	 return rtEntry.port;	
}

 RoutingEntry treeNode::getRoutingEntry() const
 {
	 return rtEntry;
 }

bool treeNode::isLeaf() const 
{
	return (leftChildPtr == nullptr && rightChildPtr == nullptr);
}

std::shared_ptr<treeNode> treeNode::getLeftChildPtr() const 
{
	return leftChildPtr;	
}
std::shared_ptr<treeNode>  treeNode::getRightChildPtr() const
{
	return rightChildPtr;
}

void treeNode::setLeftChildPtr(std::shared_ptr<treeNode> leftPtr) 
{
	leftChildPtr = leftPtr;
}

void treeNode::setRightChildPtr(std::shared_ptr<treeNode> rightPtr)
{
	rightChildPtr = rightPtr;
}