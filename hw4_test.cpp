
#define CATCH_CONFIG_MAIN			// this line tells Catch to provide a main() function
#define CATCH_CONFIG_COLOUR_NONE


#include "catch.hpp"
#include "prefixTree.h"
#include "treeNode.h"
#include "hw4_datarecord.h"

using namespace std;

TEST_CASE("Test Creating an Empty Tree", "[constructor]") {
	
	// default constructor
	treeNode node; 
	REQUIRE(node.getNetId() == "");
	REQUIRE(node.getPort() == -1);
	REQUIRE(node.getLeftChildPtr() == nullptr);
	REQUIRE(node.getRightChildPtr() == nullptr);
	
	// paramaterized constructor
	treeNode param_node("Test_ID", 50);
	REQUIRE(param_node.getNetId() == "Test_ID");
	REQUIRE(param_node.getPort() == 50);
	REQUIRE(param_node.getLeftChildPtr() == nullptr);
	REQUIRE(param_node.getRightChildPtr() == nullptr);
}
// To DO

TEST_CASE("Test Functions Surrounding NetID and Port Configuration", "[treeNode]")
{
	treeNode node; 

	// set both NetID and Port to any chosen value
	node.setNetId("newID");
	node.setPort(25);

	// check to make sure NetID and Port are correctly set
	REQUIRE(node.getNetId() == "newID");
	REQUIRE(node.getPort() == 25); 

	// test out that Routing Entry returns same values
	RoutingEntry route = node.getRoutingEntry();
	REQUIRE(route.netId == "newID");
	REQUIRE(route.port == 25); 

	// ensure routing entry returns same values, even for parameterized constructor
	treeNode param_node("ParamID", 39);

	RoutingEntry param_route = param_node.getRoutingEntry();
	REQUIRE(param_route.netId == "ParamID");
	REQUIRE(param_route.port == 39);
}

TEST_CASE("Test Leaf, LeftPtr, and RightPtr Functions", "[treeNode]")
{
	// test if the isLeaf() funciton correctly identifies leaf nodes
	treeNode leaf;
	REQUIRE(leaf.isLeaf());

	shared_ptr<treeNode> leftLeafPtr = leaf.getLeftChildPtr();
	shared_ptr<treeNode> rightLeafPtr = leaf.getRightChildPtr();

	REQUIRE(leftLeafPtr == nullptr);
	REQUIRE(rightLeafPtr == nullptr);

	// test if set left/right pointers works, and changes a leaf node to no longer be a leaf node
	treeNode leftLeaf("Left", 13);
	treeNode rightLeaf("Right", 10);

	leaf.setLeftChildPtr(make_shared<treeNode>(leftLeaf));
	leaf.setRightChildPtr(make_shared<treeNode>(rightLeaf));
	REQUIRE_FALSE(leaf.isLeaf());

	// test if left/right child ptr's return correct information
	leftLeafPtr = leaf.getLeftChildPtr();
	rightLeafPtr = leaf.getRightChildPtr();

	REQUIRE(leftLeafPtr != nullptr);
	REQUIRE(leftLeafPtr->getNetId() == "Left");
	REQUIRE(leftLeafPtr->getPort() == 13);

	REQUIRE(leftLeafPtr != nullptr);
	REQUIRE(rightLeafPtr->getNetId() == "Right");
	REQUIRE(rightLeafPtr->getPort() == 10);
}

TEST_CASE("Test Prefix Tree Constructor", "[prefixTree]")
{
	// default constructor
	prefixTree prefix;
	REQUIRE(prefix.isEmpty());
}

TEST_CASE("Test Add and getRoutingEntry functions", "[prefixTree")
{
	prefixTree prefix;
	REQUIRE(prefix.isEmpty());

	// test the add function 
	REQUIRE(prefix.add("First", 1));
	REQUIRE(prefix.add("Second", 2));
	REQUIRE(prefix.add("Third", 3));

	// test the getRoutingEntry function
	RoutingEntry route1 = prefix.getRoutingEntry("First");
	REQUIRE(route1.netId == "First");
	REQUIRE(route1.port == 1);

	RoutingEntry route2 = prefix.getRoutingEntry("Second");
	REQUIRE(route2.netId == "Second");
	REQUIRE(route2.port == 2);

	RoutingEntry route3 = prefix.getRoutingEntry("Third");
	REQUIRE(route3.netId == "Third");
	REQUIRE(route3.port == 3);

}


TEST_CASE("Test Both Remove and Clear Functions", "[prefixTree]")
{
	prefixTree prefix;
	REQUIRE(prefix.isEmpty());

	REQUIRE(prefix.add("First", 1));
	REQUIRE(prefix.add("Second", 2));
	REQUIRE(prefix.add("Third", 3));

	// test that remove() will not remove a non-existent node
	REQUIRE_FALSE(prefix.remove("Fourth"));

	// test that remove() completely removes a node
	REQUIRE(prefix.remove("Second"));
}

TEST_CASE("Test the postOrderTraverse Function", "[prefixTree]")
{
	prefixTree prefix; 

	REQUIRE(prefix.add("First", 1));
	REQUIRE(prefix.add("Second", 2));
	REQUIRE(prefix.add("Third", 3));

	auto visit = [](shared_ptr<treeNode> nodePtr)
		{
			return nodePtr->getNetId() + " ";
		};

	string result = prefix.postorderTraverse(visit);

	REQUIRE(result == "Third Second First ");
}

//TEST_CASE("Test the findPort function using a .txt file", "[prefixTree")
//{
//	string file = "C:\\Users\\Bryce Eller\\project4-abeller25\\routing_table.txt";
//	prefixTree prefix(file);
//
//	REQUIRE(prefix.findPort("0001") == 0);
//	//REQUIRE(prefix.findPort("0100") == 1);
//	//REQUIRE(prefix.findPort("10") == 2);
//	REQUIRE(prefix.findPort("000") == 3);
//	REQUIRE(prefix.findPort("") == 4);
//}

