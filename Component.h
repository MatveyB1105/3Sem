#pragma once
#include <iostream>

template<typename ID, typename T>
class Node {
private:
	ID id;
	T data;
	int degree;
public:
	Node() 
		: id(ID())
		, data(T())
		, degree(0)
	{
	}
	Node(ID id, T data) {
		this->data = data;
		this->id = id;
		this->degree = 0;
	}
	Node(const Node<ID,T>& other) {
		this->data = other.data;
		this->id = other.id;
		this->degree = other.degree;
	}
	ID GetId() {
		return id;
	}
	T GetData() {
		return data;
	}
	void SetDegree(int number) {
		degree = number;
	}
	Node<ID,T>& operator=(const Node<ID,T>& other) {
		this->data = data;
		this->id = id;
		this->degree = degree;
		return *this;
	}
	bool operator==(const Node<ID,T>& other) {
		if (other.data == this->data && other.id == this->id) { return true; }
		else { return false; }
	}
	bool operator!=(const Node<ID,T>& other) {
		if (other.data != this->data || other.id != this->id) { return true; }
		else { return false; }
	}
	bool IsEqual(const Node<ID,T>& other) {
		return (*this == other);
	}
	friend std::ostream& operator<<(std::ostream& stream, const Node<ID, T>& node)
	{
		stream << "(" << node.id << "; " << node.data << ")";

		return stream;
	}
};

template<typename ID, typename T, typename E>
class Edge {
private:
	E data;
	Node<ID, T>* start;
	Node<ID, T>* end;
public:
	Edge() {
		start = nullptr;
		end = nullptr;
	}
	Edge(E data2, Node<ID, T>* start2, Node<ID, T>* end2) {
		data = data2;
		start = start2;
		end = end2;
	}
	Edge(const Edge<ID, T, E>& other) {
		this->data = other.data;
		this->start = other.start;
		this->end = other.end;
	}
	Node<ID, T>* GetStartPoint() {
		return start;
	}
	Node<ID, T>* GetEndPoint() {
		return end;
	}
	Node<ID, T> GetStart() {
		return *(this->start);
	}
	Node<ID, T> GetEnd() {
		return *(this->end);
	}
	E& GetData() {
		return data;
	}
	bool operator==(const Edge<ID, T, E>& other) {
		if (other.start == this->start && other.end == this->end && other.data == this->data) { return true; }
		else { return false; }
	}
	bool operator!=(const Edge<ID, T, E>& other) {
		if (other.start != this->start || other.end != this->end || other.data != this->data) { return true; }
		else { return false; }
	}
	~Edge() {
		delete start;
		delete end;
	}
};