#pragma once
#include "Sequence.h"
#include "DynamicArray.h"
template <typename T> class ArraySequence : public Sequence<T> {
private:
	DynamicArray<T>* items;
	int length;
public:
	ArraySequence() {
		this->items = new DynamicArray<T>();
	}

	ArraySequence(std::nullptr_t) {
		this->items = new DynamicArray<T>();
	}

	ArraySequence(T* other, int count) { //	Копировать элементы из переданного массива
		this->items = new DynamicArray<T>(other, count);
	}

	ArraySequence(const DynamicArray<T>& other) {  // Копирующий конструктор
		this->items = new DynamicArray<T>(other);
	}

	ArraySequence(const ArraySequence<T>& other) { //Копирующий конструктор
		this->items = new DynamicArray<T>(*other.items);
	}

	ArraySequence(ArraySequence<T>&& other) {
		this->items = other.items;
		other.items = nullptr;
	}
	Sequence<T>* Create() override {
		return (Sequence<T>*) new ArraySequence<T>();
	}
	Sequence<T>* Copy() override {
		return (Sequence<T>*) new ArraySequence<T>(*this);
	}
	ArraySequence<T>& operator=(const ArraySequence<T>& other) {
		delete items;
		this->items = new DynamicArray<T>(*other.items);
		return *this;
	}

	ArraySequence<T>& operator=(ArraySequence<T>&& other) {
		delete items;
		this->items = other.items;
		other.items = nullptr;
		return *this;
	}

	~ArraySequence() {
		delete items;
	}

	T& GetFirst() const override {
		return this->items->Get(0);
	}

	T& GetLast() const override {
		return this->Get(items->GetSize() - 1);
	}

	T& Get(int index) const override {
		return this->items->Get(index);
	}

	int GetLength() const override {
		return this->items->GetSize();
	}


	void Append(T item) override {
		this->items->Resize(this->items->GetSize() + 1);
		this->items->Set(this->items->GetSize() - 1, item);

	}

	void Prepend(T item) override {
		this->items->Resize(this->items->GetSize() + 1);
		for (int i = this->items->GetSize() - 1; i > 0; i--) {
			this->items->Set(i, this->items->Get(i - 1));
		}
		this->items->Set(0, item);
	}

	void InsertAt(T item, int index) override {
		this->items->Resize(this->items->GetSize() + 1);
		for (int i = this->items->GetSize() - 1; i > index; i--) {
			this->items->Set(i, this->items->Get(i - 1));
		}
		this->items->Set(index, item);
	}

	void Remove(int index) {
		if (index < 0 || index >= this->GetLength()) {
			throw std::out_of_range("Out of range");
		}

		for (int i = index; i < this->GetLength() - 1; i++) {
			this->items->Get(i) = this->items->Get(i + 1);
		}

		this->items->Resize(this->items->GetSize() - 1);
	}

	void RemoveItem(T item) {
		for (int i = 0; i < this->GetLength(); i++) {
			if (items->Get(i) == item) {
				this->Remove(i);
				return;
			}
		}
	}

	Sequence <T>* Concat(Sequence <T>* other) override {
		Sequence <T>* result = new ArraySequence<T>();
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
		Sequence <T>* result = new ArraySequence<T>();
		for (int i = startIndex; i <= endIndex; i++) {
			result->Append(this->Get(i));
		}
		return result;
	}

	Sequence <T>* Map(T(*func)(T)) override {
		Sequence <T>* result = new ArraySequence<T>();
		for (int i = 0; i < this->GetLength(); i++) {
			result->Append(func(this->Get(i)));
		}
		return result;
	}

	Sequence <T>* Where(bool (*func)(T)) override {
		Sequence <T>* result = new ArraySequence<T>();
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
		if (std::abs(index) > this->GetLength() || index + number > this->GetLength()) {
			throw std::out_of_range("Out of range");
		}
		Sequence <T>* result = new ArraySequence<T>();
		int resInd = 0;
		if (index >= 0) {
			for (int i = 0; i < index; i++) {
				result->InsertAt(this->Get(i), resInd);
				resInd++;
			}
			for (int i = index + number; i < this->GetLength(); i++) {
				result->InsertAt(this->Get(i), resInd);
				resInd++;
			}
			if (seq->GetLength() != 0) {
				int seqInd = 0;
				for (int i = index; i <= index + seq->GetLength() - 1; i++) {
					result->InsertAt(seq->Get(seqInd), i);
					seqInd++;
				}
			}
		}
		return result;
	}

	T& operator[](int index) {
		if (index < 0 || index >= this->GetLength()) {
			throw std::out_of_range("Out of range");
		}
		return this->Get(index);
	}

	Sequence<T>* operator+(const ArraySequence<T>* other) {
		Sequence <T>* result = new ArraySequence<T>();
		for (int i = 0; i < this->GetLength(); i++)
			result->Append(this->Get(i));
		for (int i = 0; i < other->GetLength(); i++)
			result->Append(other->Get(i));
		return result;
	}

	Sequence<T>& operator+(const ArraySequence<T>& other) {
		for (int i = 0; i < other.GetLength(); i++)
			this->Append(other->Get(i));
		return *((Sequence<T>*)this);
	}

	bool operator==(const ArraySequence<T>& other) {
		if (this->GetLength() != other.GetLength())
			return false;
		for (int i = 0; i < this->GetLength(); i++)
			if (this->Get(i) != other.Get(i))
				return false;
		return true;
	}

	bool operator!=(const ArraySequence<T>& other) {
		return !(this->items == other.items);
	}

};

