#pragma once
#include <stdexcept>
#include <iostream>
template <typename T> class DynamicArray {
private:
	T* data;
	int length;
public:

	DynamicArray() {
		data = new T[1];
		data[0] = T();
		length = 0;
	}

	DynamicArray(T* other, int count) { // Копировать элементы из переданного массива

		data = new T[count];
		length = count;
		for (int i = 0; i < length; i++) {
			data[i] = other[i];
		}

	}

	DynamicArray(int size) {

		data = new T[size];
		length = size;
		for (int i = 0; i < length; i++) {
			data[i] = T();
		}
	}

	DynamicArray(const DynamicArray<T>& other) {
		length = other.length;
		data = new T[length];
		for (int i = 0; i < length; i++) {
			this->data[i] = other.Get(i);
			//this->data[i] = other.data[i];
		}
	}

	DynamicArray(DynamicArray<T>&& other) {
		length = other.length;
		data = other.data;
		other.data = nullptr;
		other.length = 0;
	}

	~DynamicArray() {
		delete[] data;
	}

	T& Get(int index) const {
		if (index < 0 || index >= length) {
			throw std::out_of_range("Out of range");
		}
		return this->data[index];
	}

	int GetSize() const {

		return this->length;
	}

	void Set(int index, T value) {

		if (index < 0 || index >= length) {
			throw std::out_of_range("Out of range");
		}
		this->data[index] = value;

	}

	void Resize(int newSize) {
		if (newSize < 0) {
			throw std::invalid_argument("new size less than 0");
		}
		T* newData = new T[newSize];
		int tempLength = (newSize > length) ? length : newSize;
		for (int i = 0; i < tempLength; i++) {
			newData[i] = data[i];
		}
		delete[] data;
		if (tempLength < newSize) {
			for (int i = tempLength; i < newSize; i++) {
				newData[i] = T();
			}
		}
		this->data = newData;
		this->length = newSize;
	}

	DynamicArray<T>& operator=(const DynamicArray<T>& other) {
		delete[] data;
		length = other.length;
		data = new T[length];
		for (int i = 0; i < length; i++) {
			this->data[i] = other.Get(i);
		}
		return *this;
	}

	DynamicArray<T>& operator=(DynamicArray<T>&& other) {
		delete[] data;
		length = other.length;
		data = other.data;
		other.data = nullptr;
		other.length = 0;
		return *this;
	}

	T& operator[](int index) {
		if (index < 0 || index >= length) {
			throw std::out_of_range("Out of range");
		}
		return this->data[index];
	}

	DynamicArray<T>* operator+(const DynamicArray<T>* other) {
		DynamicArray<T>* result = new DynamicArray<T>(this->GetSize() + other->GetSize());
		for (int i = 0; i < this->GetSize(); i++) {
			this->Set(i, this->Get(i));
		}
		for (int i = this->GetSize(); i < result->GetSize(); i++) {
			this->Set(i, this->Get(i));
		}
		return result;
	}

	DynamicArray<T>& operator+(const DynamicArray<T>& other) {
		int oldSize = this->GetSize();
		this->Resize(oldSize + other.GetSize());
		for (int i = oldSize; i < this->GetSize(); i++) {
			this->Set(i, other.Get(i));
		}
		return *this;
	}

	bool operator==(const DynamicArray<T>& other) {
		if (this->length != other.length)
			return false;
		for (int i = 0; i < this->length; i++)
			if (this->data[i] != other.data[i])
				return false;
		return true;
	}

	bool operator!=(const DynamicArray<T>& other) {
		return !(*this == other);
	}

	friend std::ostream& operator << (std::ostream& stream, const DynamicArray<T>& arr) {
		for (int i = 0; i < arr.GetSize(); i++) {
			stream << arr.Get(i) << std::endl;
		}
		return stream;
	}
};