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

int HashTable::hashFunction(std::string key)
{
    size_t hash = 0;              // 1. 누적 변수 초기화

    for (char c : key)            // 2. 각 글자 순회하며 인코딩
    {
        hash = hash * 31 + c;
    }

    return hash % bucketCount;    // 3. bucketCount로 나눈 나머지 리턴
}
