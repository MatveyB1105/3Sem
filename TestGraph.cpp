#include <iostream>
#include "Graph.h"
#include "STLHasher.h"
using namespace std;

int main() {
	IHasher<int>* hash = new STLHasher<int>();
	Graph<int, int, int> graph1(hash);
	Node<int, int> node(1, 15);
	graph1.AddNode(node);
	std::cout << node.GetData();
	graph1.PrintNode();
	return 0;
}