#pragma once

#include "Pair.h"
template <typename Tkey, typename Tvalue>
class IDictionary {
public:
	virtual int GetCount() const = 0;

	virtual int GetCapacity() const = 0;

	virtual Tvalue Get(const Tkey& key) const = 0;

	virtual bool ContainsKey(const Tkey& key) const = 0;

	virtual IDictionary<Tkey, Tvalue>* Add(Pair<Tkey, Tvalue> record) = 0;

	virtual void Remove(const Tkey& key) = 0;
};