#pragma once
template <typename Tkey>
class IHasher {
public:
    virtual int Hash(const Tkey& key) const = 0;
};