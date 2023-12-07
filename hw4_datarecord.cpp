////////////////////////////////////////////////////////
// ECE 3514, Project 4, Ashton Bryce Eller
//
// File name: hw4_datarecord.cpp
// Description: Implementation file that instantiates the 
//				logic to accurately record data to form a 
//				prefix tree
// Date: 12/06/2023 
//



#include "hw4_datarecord.h"
#include <string>

std::string visitNode(std::shared_ptr<treeNode> nodePtr) {

	// assume treeNode has function to get its netId and port
	if (nodePtr != nullptr)
	{
		return nodePtr->getNetId() + ":" + std::to_string(nodePtr->getPort()) + "\n";
	}
	else
	{
		return "";
	}
	
}

std::string visitRoutingEntry(std::shared_ptr<treeNode> nodePtr) {

	// assume treeNode has function to get its netId and port
	if (nodePtr != nullptr && nodePtr->getPort() >= 0)
	{
		return nodePtr->getNetId() + ":" +
			std::to_string(nodePtr->getPort()) + "\n";
	}
	else
	{
		return "";
	}
}