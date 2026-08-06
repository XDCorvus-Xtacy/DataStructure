#include <iostream>
#include "include/hash_table.hpp"

int main()
{
    // 1단계: 기본 insert + 출력
    HashTable table;

    table.insert("apple", 100);
    table.insert("banana", 200);
    table.insert("cherry", 300);

    std::cout << "=== 초기 데이터 ===" << std::endl;
    table.printData();

    // 2단계: 덮어쓰기
    std::cout << "\n=== apple 값을 999로 덮어쓰기 ===" << std::endl;
    table.insert("apple", 999);
    table.printData();

    // 3단계: 삭제
    std::cout << "\n=== banana 삭제 ===" << std::endl;
    table.remove("banana");
    table.printData();

    std::cout << "\n=== 삭제 확인 (search) ===" << std::endl;
    std::cout << "banana 검색: " << table.search("banana") << std::endl;
    std::cout << "apple 검색: " << table.search("apple") << std::endl;

    // 4단계: 리사이즈
    std::cout << "\n=== 리사이즈 테스트: 데이터 추가 ===" << std::endl;
    std::cout << "추가 전 버킷 개수: " << table.getBucketCount() << std::endl;

    table.insert("date", 400);
    table.insert("egg", 500);
    table.insert("fig", 600);
    table.insert("grape", 700);
    table.insert("honey", 800);

    std::cout << "추가 후 버킷 개수: " << table.getBucketCount() << std::endl;
    table.printData();

    return 0;
}