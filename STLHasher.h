#pragma once
#include "IHasher.h"
#include <functional>
template <typename Tkey>
class STLHasher : public IHasher<Tkey> {
public:
    int Hash(const Tkey& key) const {
        return std::hash<Tkey>{}(key);
    }
};