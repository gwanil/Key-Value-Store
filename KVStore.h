// #pragma onec

//  헤더 가드 
//  헤더 파일이 중복으로 불어와져서 에러가 나는 것을 방치함
//  KVSTORE_H가 정의 안 되어 있으면 -> 정의하고 아래 내용 읽기 
#ifndef KVSTORE_H   //  1. "만약 정의가 안됐다면"
#define KVSTORE_H   //  2. 정의함

/*
    ... (헤더 파일 내용: 구조체, 클래스 선언) ...
    ... (이 내용은 처음에만 컴파일러가 읽기 됨) ...
*/

#include <string>
#include <iostream>

using namespace std;

//  [구조체 Node]
//  설명: 데이터 한 덩어리를 나타냄 (Linked List의 알맹이)
//  C언어와 달리 생서자 (Node(...))를 넣어 초기화를 편하게함
struct Node
{
    string key;     //  key (검색 키)
    string value;   //  value (실제 값)
    Node* next;     //  다음 노드의 주소를 가리키는 포인터 (충돌 시 연결용)

//  [Node 생성자]
//  Node *n = new Node("k", "v") 할 때 자동으로 실행되어 변수를 채움
    Node(string k, string v) : key(k), value(v), next(nullptr) {}
};

//  [클래스 선언]
//  설명: 데이터 저장소의 '설계도'
class KVStore {
    private:
        int capacity;
        Node** table;

        int hashFunction(string key);

    public:
        KVStore(int size);
        ~KVStore();

        void put(string key, string value);
        string get(string key);
        void remove(string key);

};

#endif  // 3. "if문의 끝 (1 세트)"