#pragma once 
#include "IHasher.h"
#include "Pair.h"
#include "STLHasher.h"
#include "IDictionary.h"
#include "ArraySequence.h"
#include "DynamicArray.h"

#define Default 10
template <typename Tkey, typename Tvalue>
class HashTable : public IDictionary<Tkey, Tvalue> {
private:
    DynamicArray<ArraySequence<Pair<Tkey, Tvalue>>>* hashtable;
    IHasher<Tkey>* hasher;
    int count;
    int Hash(const Tkey& key) const {
        return hasher->Hash(key) % this->GetCapacity();
    }
public:
    HashTable() {
        count = 0;
        hashtable = new DynamicArray<ArraySequence<Pair<Tkey, Tvalue>>>(Default);
        hasher = new STLHasher<Tkey>();
    }
    HashTable(IHasher<Tkey>* other) {
        count = 0;
        hashtable = new DynamicArray<ArraySequence<Pair<Tkey, Tvalue>>>(Default);
        hasher = other;
    }
    HashTable(int capacity) {
        count = 0;
        hashtable = new DynamicArray<ArraySequence<Pair<Tkey, Tvalue>>>(capacity);
        hasher = new STLHasher<Tkey>();
    }

    HashTable(const HashTable<Tkey, Tvalue>& other) {
        hashtable = other.hashtable;
        hasher = other.hasher;
        count = other.count;
    }

    HashTable(HashTable<Tkey, Tvalue>&& other) {
        hashtable = std::exchange(other.hashtable, nullptr);
        hasher = std::exchange(other.hasher, nullptr);
        count = std::exchange(other.count, 0);
    }

    ~HashTable() {
        delete hashtable;
        delete hasher;
    }

    HashTable<Tkey, Tvalue>& operator=(const HashTable<Tkey, Tvalue>& other) {
        delete hashtable;
        hashtable = other.hashtable;
        delete hasher;
        hasher = other.hasher;
        count = other.count;
    }

    int GetCount() const {
        return count;
    }

    int GetCapacity() const {
        return hashtable->GetSize();
    }

    Tvalue Get(const Tkey& key) const {
        ArraySequence<Pair<Tkey, Tvalue>>& list = (*hashtable)[Hash(key)];
        for (int i = 0; i < list.GetLength(); i++) {
            Pair<Tkey, Tvalue>& record = list.Get(i);
            if (record.GetLeft() == key) {
                return record.GetRight();
            }
        }
        throw std::out_of_range("Value was not found");
    }

    bool ContainsKey(const Tkey& key) const {
        ArraySequence<Pair<Tkey, Tvalue>>& list = (*hashtable)[Hash(key)];
        for (int i = 0; i < list.GetLength(); i++) {
            Pair<Tkey, Tvalue>& record = list.Get(i);
            if (record.GetLeft() == key) {
                return true;
            }
        }
        return false;
    }

    IDictionary<Tkey, Tvalue>* Add(Pair<Tkey, Tvalue> record) {
        if (hashtable->GetSize() == 0) {
            hashtable->Resize(Default);
        }
        if (ContainsKey(record.GetLeft())) {
            throw std::invalid_argument("Key already is in table");
        }
        if (count > 0.8 * this->GetCapacity()) {
            DynamicArray<ArraySequence<Pair<Tkey, Tvalue>>>* newtable = new DynamicArray<ArraySequence<Pair<Tkey, Tvalue>>>(hashtable->GetSize() * 2);
            for (int i = 0; i < hashtable->GetSize(); i++) {
                ArraySequence<Pair<Tkey, Tvalue>>& list = hashtable->Get(i);
                for (int i = 0; i < list.GetLength(); i++) {
                    Pair<Tkey, Tvalue>& Pair = list.Get(i);
                    ((*newtable)[hasher->Hash(Pair.GetLeft()) % newtable->GetSize()]).Append(Pair);
                }
            }
            delete hashtable;
            hashtable = newtable;
        }
        ((*hashtable)[Hash(record.GetLeft())]).Append(record);
        this->count++;
        return this;
    }

    void Remove(const Tkey& key) {
        if (ContainsKey(key) == false) {
            throw std::out_of_range("Key was not found");
        }
        else {
            ArraySequence<Pair<Tkey, Tvalue>>& list = (*hashtable)[Hash(key)];
            for (int i = 0; i < list.GetLength(); i++) {
                if ((list[i]).GetLeft() == key) {
                    list.Remove(i);
                    break;
                }
            }
            this->count--;
        }
    }
};