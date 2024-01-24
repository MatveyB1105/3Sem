#include <iostream>
#include "HashTable.h"

int main() {
	IDictionary<int, int>* hash1 = new HashTable<int, int>(2);
	hash1->Add({ 0,17 });
	hash1->Add({ 1,2 });
	hash1->Remove(1);
	hash1->Remove(1);
	return 0;
}