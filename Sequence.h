#pragma once
#include <iostream>
#include <cassert>
#include <stdexcept>
template <typename T> class Sequence {
public:
    virtual ~Sequence() {};

    virtual Sequence<T>* Create() = 0;

    virtual Sequence<T>* Copy() = 0;

    virtual T& GetFirst() const = 0;

    virtual T& GetLast() const = 0;

    virtual T& Get(int index) const = 0;

    virtual int GetLength() const = 0;

    virtual void Append(T item) = 0;

    virtual void Prepend(T item) = 0;

    virtual void InsertAt(T item, int index) = 0;

    virtual Sequence <T>* Concat(Sequence <T>* other) = 0;

    virtual Sequence <T>* GetSubsequence(int startIndex, int endIndex) = 0;

    virtual Sequence <T>* Slice(int index, int number, Sequence<T>* seq) = 0;

    virtual Sequence <T>* Map(T(*func)(T)) = 0;

    virtual Sequence <T>* Where(bool (*func)(T)) = 0;

    virtual T Reduce(T(*func)(T, T), T start) = 0;

    friend std::ostream& operator << (std::ostream& stream, const Sequence<T>* seq) {
        stream << "{";
        for (int i = 0; i < seq->GetLength() - 1; i++) {
            stream << seq->Get(i) << ", ";
        }
        stream << seq->GetLast() << "}" << std::endl;
        return stream;
    }

    virtual T& operator[](int index) = 0;

   
};
