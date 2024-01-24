#pragma once
#include "Sequence.h"
#include "List.h"
template <typename T> class LinkedListSequence : public Sequence<T> {
private:
	LinkedList<T>* list;
public:
	LinkedListSequence() {
		list = new LinkedList<T>();
	}

	LinkedListSequence(T* items, int count) { //	Копировать элементы из переданного массива
		list = new LinkedList<T>(items, count);
	}

	LinkedListSequence(const LinkedList <T>& other) {  // Копирующий конструктор
		list = new LinkedList<T>(other);
	}

	LinkedListSequence(const LinkedListSequence <T>& other) {  // Копирующий конструктор
		this->list = new LinkedList<T>(*other.list);
	}

	Sequence<T>* Create() override {
		return (Sequence<T>*) new LinkedListSequence<T>();
	}
	Sequence<T>* Copy() override {
		return (Sequence<T>*) new LinkedListSequence<T>(*this);
	}
	~LinkedListSequence() {
		delete list;
	}

	T& GetFirst() const override {
		//return this->list->Get(0);
		return this->list->GetFirst();
	}

	T& GetLast() const override {
		//return this->Get(list->GetLenght()-1);
		return this->list->GetLast();
	}

	T& Get(int index) const override {
		return this->list->Get(index);
	}

	int GetLength() const override {
		return this->list->GetLenght();
	}

	void Append(T item) override {
		this->list->Append(item);
	}

	void Prepend(T item) override {
		this->list->Prepend(item);
	}

	void InsertAt(T item, int index) override {
		this->list->InsertAt(item, index);
	}

	Sequence <T>* Concat(Sequence <T>* other) override {
		Sequence <T>* result = new LinkedListSequence<T>();
		for (int i = 0; i < this->GetLength(); i++)
			result->Append(this->Get(i));
		for (int i = 0; i < other->GetLength(); i++)
			result->Append(other->Get(i));
		return result;
	}

	Sequence <T>* GetSubsequence(int startIndex, int endIndex) override {
		if (startIndex < 0 || endIndex < 0 || startIndex >= this->GetLength() || endIndex >= this->GetLength()) {
			throw std::out_of_range("Out of range");
		}
		Sequence <T>* result = new LinkedListSequence<T>();
		for (int i = startIndex; i <= endIndex; i++) {
			result->Append(this->Get(i));
		}
		return result;
	}

	Sequence <T>* Map(T(*func)(T)) override {
		Sequence <T>* result = new LinkedListSequence<T>();
		for (int i = 0; i < this->GetLength(); i++) {
			result->Append(func(this->Get(i)));
		}
		return result;
	}

	Sequence <T>* Where(bool (*func)(T)) override {
		Sequence <T>* result = new LinkedListSequence<T>();
		for (int i = 0; i < this->GetLength(); i++) {
			if (func(this->Get(i))) {
				result->Append(this->Get(i));
			}
		}
		return result;
	}

	T Reduce(T(*func)(T, T), T start) override {
		for (int i = 0; i < this->GetLength(); i++) {
			start = func(this->Get(i), start);
		}
		return start;
	}

	Sequence <T>* Slice(int index, int number, Sequence<T>* seq) override {
		return nullptr;
	}
	/*if(abs(index) > this->GetLength()) {
		throw std::out_of_range("Out of range");
	}
	Sequence<int> * seq = new ArraySequence(new [] {1,2,3,4,5});
}*/

	T& operator[](int index) {
		if (index < 0 || index >= this->GetLength()) {
			throw std::out_of_range("Out of range");
		}
		Item<T>* ptr = this->list->GetFirstItem();
		for (int i = 0; i < index; i++) {
			ptr = ptr->next;
		}
		return ptr->data;
	}

	Sequence<T>* operator+(const LinkedListSequence<T>* other) {
		Sequence <T>* result = new LinkedListSequence<T>();
		for (int i = 0; i < this->GetLength(); i++)
			result->Append(this->Get(i));
		for (int i = 0; i < other->GetLength(); i++)
			result->Append(other->Get(i));
		return result;
	}

	Sequence<T>& operator+(const LinkedListSequence<T>& other) {
		for (int i = 0; i < other.GetLength(); i++)
			this->Append(other->Get(i));
		return *((Sequence<T>*)this);
	}
};