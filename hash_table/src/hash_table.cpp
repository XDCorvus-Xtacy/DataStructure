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

void HashTable::insert(std::string key, int value)
{
    int index = hashFunction(key);

    HashNode* current = buckets[index];
    while (current != nullptr)
    {
        if (current->key == key)
        {
            current->value = value;
            return;
        }
        current = current->next;
    }

    HashNode* newNode = new HashNode(key, value);
    newNode->next = buckets[index];
    buckets[index] = newNode;
    size++;
}

int HashTable::search(std::string key)
{
    int index = hashFunction(key);
    HashNode* current = buckets[index];
    while (current != nullptr)
    {
        if (current->key == key)
        {
            return current->value;
        }
        current = current->next;
    }
    return -1;
}

void HashTable::remove(std::string key)
{
    int index = hashFunction(key);
    HashNode* current = buckets[index];
    HashNode* prev = nullptr;

    while (current != nullptr)
    {
        if (current->key == key)
        {
            if (prev == nullptr)
            {
                buckets[index] = current->next;
            }
            else
            {
                prev->next = current->next;
            }

            delete current;
            size--;
            return;
        }
        prev = current;
        current = current->next;
    }
}