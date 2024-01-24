#pragma once

#include "IDictionary.h"
#include "HashTable.h"
#include "ArraySequence.h"
#include "IHasher.h"
#include "Component.h"
#include "Pair.h"

template<typename T, typename ID, typename E>
class Graph {
private:
	IDictionary<ID, ArraySequence<Edge<ID, T, E>>>* AdjacencyOut;
	IDictionary<ID, Node<ID, T>>* nodes;
	IDictionary<ID, ArraySequence<Edge<ID, T, E>>>* AdjacencyIn;
	ArraySequence<ID>* array_id;
public:
	Graph(IHasher<ID>* hash) {
		AdjacencyOut = new HashTable<ID, ArraySequence<Edge<ID, T, E>>>(hash);
		AdjacencyIn = new HashTable<ID, ArraySequence<Edge<ID, T, E>>>(hash);
		nodes = new HashTable<ID, Node<ID, T>>(hash);
		array_id = new ArraySequence<ID>();
	}
	Graph(Graph<T, ID, E>& other) {
		AdjacencyOut = other.AdjacencyOut;
		AdjacencyIn = other.AdjacencyIn;
		nodes = other.nodes;
		array_id = other.array_id;
	}
	Graph(Graph<T, ID, E>&& other) {
		AdjacencyOut = std::move(other.AdjacencyOut);
		AdjacencyIn = std::move(other.AdjacencyIn);
		nodes = std::move(other.nodes);
		array_id = std::move(other.array_id);
	}
	~Graph() {
		delete AdjacencyOut;
		delete AdjacencyIn;
		delete nodes;
		delete array_id;
	}
	void AddEdge(Edge<ID, T, E> other) {
		if (!AdjacencyOut->ContainsKey(other.GetStartPoint()->GetId())) {
			nodes = nodes->Add({ other.GetStartPoint()->GetId(), other.GetStart() });
			array_id->Append(other.GetStartPoint()->GetId());
			ArraySequence<Edge<ID, T, E>> newadjacencyout;
			newadjacencyout.Append(other);
			AdjacencyOut = AdjacencyOut->Add({ other.GetStartPoint()->GetId(), newadjacencyout });
		} 
		else {
			ArraySequence< Edge<ID, T, E>> currentadjacencyout = AdjacencyOut->Get(other.GetStartPoint()->GetId());
			currentadjacencyout.Append(other);
		}
		if (!AdjacencyIn->ContainsKey(other.GetEndPoint()->GetId())) {
			nodes = nodes->Add({ other.GetEndPoint()->GetId(), other.GetEnd() });
			array_id->Append(other.GetEndPoint()->GetId());
			ArraySequence<Edge<ID, T, E>> newadjacencyin;
			newadjacencyin.Append(other);
			AdjacencyIn = AdjacencyIn->Add({ other.GetEndPoint()->GetId(), newadjacencyin });
		}
		else {
			ArraySequence< Edge<ID, T, E>> currentadjacencyin = AdjacencyIn->Get(other.GetEndPoint()->GetId());
			currentadjacencyin.Append(other);
		}
	}
	void AddNode(Node<ID, T> other) {
		if (!nodes->ContainsKey(other.GetId())) {
			Pair<ID, Node<ID, T>> pair = { other.GetId(), other };
			Node<ID, T> test = other;
			std::cout << pair;
			nodes = nodes->Add({ other.GetId(), test });
			array_id->Append(other.GetId());
		}
		else {
			throw std::out_of_range("This node was added");
		}
	}
	void AddNodes(std::initializer_list<Node<ID, T>> other) {
		for (auto a : other) {
			if (!nodes->ContainsKey(a.GetId())) {
				nodes = nodes->Add({ other.GetId(), a });
				array_id->Append(a.GetId());
			}
		}
	}
	void AddEdges(std::initializer_list<Edge<ID, T, E>> other) {
		for (auto a : other) {
			if (!AdjacencyOut->ContainsKey(a.GetStart()->GetId())) {
				nodes = nodes->Add({ a.GetStartPoint()->GetId(), a.GetStart() });
				array_id->Append(a.GetStartPoint()->GetId());
				ArraySequence<Edge<ID, T, E>> newadjacencyout;
				newadjacencyout.Append(a);
				AdjacencyOut = AdjacencyOut->Add({ a.GetStartPoint()->GetId(), newadjacencyout });
			}
			else {
				ArraySequence< Edge<ID, T, E>>& currentadjacencyout = AdjacencyOut->Get(a.GetStart()->GetId());
				currentadjacencyout.Append(a);
			}
			if (!AdjacencyIn->ContainsKey(a.GetEnd()->GetId())) {
				nodes = nodes->Add({ a.GetEndPoint()->GetId(), a.GetEnd() });
				array_id->Append(a.GetEndPoint()->GetId());
				ArraySequence<Edge<ID, T, E>> newadjacencyin;
				newadjacencyin.Append(a);
				AdjacencyIn = AdjacencyIn->Add({ a.GetEndPoint()->GetId(), newadjacencyin });
			}
			else {
				ArraySequence< Edge<ID, T, E>>& currentadjacencyin = AdjacencyIn->Get(a.GetEnd()->GetId());
				currentadjacencyin.Append(a);
			}
		}
	}
	void RemoveEdge(Edge<ID, T, E> other) {
		if (!AdjacencyOut->ContainsKey(other.GetStartPoint()->GetId())) {
			return;
		}
		else {
			ArraySequence<Edge<ID, T, E>>& currentadjacencyout = AdjacencyOut->Get(other.GetStartPoint()->GetId());
			for (int i = 0; i < currentadjacencyout.GetLength(); i++) {
				if (currentadjacencyout.Get(i) == other) {
					currentadjacencyout.Remove(i);
				}
			}
		}
		if (!AdjacencyIn->ContainsKey(other.GetEndPoint()->GetId())) {
			return;
		}
		else {
			ArraySequence<Edge<ID, T, E>>& currentadjacencyin = AdjacencyIn->Get(other.GetEndPoint()->GetId());
			for (int i = 0; i < currentadjacencyin.GetLength(); i++) {
				if (currentadjacencyin.Get(i) == other) {
					currentadjacencyin.Remove(i);
				}
			}
		}
	}
	void RemoveNode(Node<ID, T>& other) {
		if (!nodes->ContainsKey(other.GetId())) {
			return;
		}
		else {
			std::cout << "Lover";
			AdjacencyOut->Remove(other.GetId());
			std::cout << "1";
			AdjacencyIn->Remove(other.GetId());
			std::cout << "2";
			nodes->Remove(other.GetId());
			std::cout << "3";
			array_id->RemoveItem(other.GetId());
			std::cout << "4";
		}
	}
	void SetDegree() {
		for (int i = 0; i < array_id->GetLength(); i++) {
			Node<ID, T>& node = nodes->Get(array_id->Get(i));
			ArraySequence<Edge<ID, T, E>>& currentadjacencyin = AdjacencyIn->Get(array_id->Get(i));
			ArraySequence<Edge<ID, T, E>>& currentadjacencyout = AdjacencyOut->Get(array_id->Get(i));
			node.SetDegree(currentadjacencyin.GetLength() + currentadjacencyout.GetLength());
		}
	}
	void PrintNode() {
		for (int i = 0; i < array_id->GetLength(); i++) {
			Node<ID, T> node = nodes->Get(array_id->Get(i));
			std::cout << "(" << array_id->Get(i) << ";" << node.GetData() << ")" << std::endl;
		}
	}
};