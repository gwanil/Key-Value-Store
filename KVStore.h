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
        //  [캡슐화] 외부에서 db, table처럼 함부로 접근 못하게 막음
        int capacity;   //  저장소의 전체 크기 (버킷 수)
        Node** table;   //  [이중 포인터] Node 포인터들의 배열을 가르키는 변수

        //  [내부 함수] 해시 함수는 내부에서만 쓰임 (private)
        int hashFunction(string key);

    public:
        //  [생성자] 클래스가 만들어질 때(초기화) 호출
        KVStore(int size);
        //  [소멸자] 클래스가 사라질 때(메모리 해제) 호출
        ~KVStore();

        //  [공개 함수] 외부(main)에서 사용할 기능들
        void put(string key, string value);     // 저장/수정
        string get(string key);                 // 조회
        void remove(string key);                // 삭제

};

#endif  //   3. "if문의 끝 (1 세트)"