#include"treeNode.h"
#include"prefixTree.h"
#include "hw4_datarecord.h"
#include<iostream>
#include<memory>


int main() {

	std::string file = "C:\\Users\\Bryce Eller\\project4-abeller25\\routing_table.txt";
	prefixTree myTree(file);
	
	std::cout << "-------------Tree ----------------------\n\n";
	std::cout << myTree.postorderTraverse(visitNode) << std::endl;
	std::cout << "----------------------------------------------\n\n";
	

	std::cout<<"end of the program \n";
	std::cin.get();

	return 0;

}

