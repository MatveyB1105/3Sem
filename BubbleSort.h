#pragma once

#include "Sequence.h"
#include <functional>
#include "ISorter.h"

template <typename T>
class BubbleSorter : public ISorter<T>
{
public:
	void Sort(Sequence<T>* sequence, std::function<int(const T&, const T&)> comp) override
	{
		if (sequence->GetLength() == 0)
		{
			return;
		}
		for (int i = 0; i < sequence->GetLength(); i++) {
			for (int j = 0; j < sequence->GetLength() - 1; j++) {
				if (comp(sequence->Get(j), sequence->Get(j + 1)) > 0) {
					std::swap(sequence->Get(j), sequence->Get(j + 1));
				}
			}
		}
	}
	Sequence<T>* SortCopy(Sequence<T>* sequence, std::function<int(const T&, const T&)> comp) override
	{
		if (sequence->GetLength() == 0)
		{
			return sequence->Create();
		}
		Sequence<T>* copy = sequence->Copy();
		for (int i = 0; i < copy->GetLength(); i++) {
			for (int j = 0; j < copy->GetLength() - 1; j++) {
				if (comp(copy->Get(j), copy->Get(j + 1)) > 0) {
					std::swap(copy->Get(j), copy->Get(j + 1));
				}
			}
		}
		return copy;
	}
private:
};