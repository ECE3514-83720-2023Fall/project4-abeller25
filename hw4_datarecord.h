////////////////////////////////////////////////////////
// ECE 3514, Project 4, Ashton Bryce Eller
//
// File name: hw4_datarecord.h 
// Description: Class file that holds the functions for recording 
//				any tree data
// Date: 12/06/2023 
//

#ifndef DATARECORD_
#define DATARECORD_


#include <iostream>
#include <string>
#include "treeNode.h"
#include "prefixTree.h"

std::string visitNode(std::shared_ptr<treeNode> nodePtr);
std::string visitRoutingEntry(std::shared_ptr<treeNode> nodePtr);
#endif