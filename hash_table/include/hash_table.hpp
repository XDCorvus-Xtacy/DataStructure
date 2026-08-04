#pragma once
#include <string>
#include <vector>

struct HashNode 
{
    std::string key;
    int value;
    HashNode* next;

    HashNode(std::string k, int v) 
    {
        key = k;
        value = v;
        next = nullptr;
    }
};

class HashTable 
{
private:
    std::vector<HashNode*> buckets;   // 버킷 배열 (각 칸이 연결 리스트 시작)
    int bucketCount;                  // 버킷 개수
    int size;                         // 담긴 데이터 개수
    int hashFunction(std::string key, int count);

public:
    HashTable();                                   // 생성자
    ~HashTable();                                  // 소멸자
    void insert(std::string key, int value);       // 넣기
    int search(std::string key);                   // 찾기
    void remove(std::string key);                  // 지우기
    void resize();
};