#include "../include/hash_table.hpp"

HashTable::HashTable() 
{
    buckets = std::vector<HashNode*>(8, nullptr);
    bucketCount = 8;
    size = 0;
}

HashTable::~HashTable() 
{
    for (int i = 0; i < bucketCount; i++) 
    {
        HashNode* current = buckets[i];
        while (current != nullptr)
        {
            HashNode* pTmp = current->next;
            delete current;
            current = pTmp;
        }
    }
}