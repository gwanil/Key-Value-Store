#include "KVStore.h"    // 헤더 파일을 가져와서 클래스 사용

// [해시 함수]
int KVStore::hashFunction(string key) {
    int hash = 0;

    for (char ch : key) {
        hash += ch;
    }

    return hash % capacity;
}

//  [생성자 구현]
KVStore::KVStore(int size) {
    this->capacity = size;

    table = new Node*[capacity];

    for (int i=0; i<capacity; i++) {
        table[i] = nullptr;
    }
}

//  [소멸자 구현]
KVStore::~KVStore() {

    for (int i=0; i<capacity; i++) {
        Node* current = table[i];

        while (current != nullptr)
        {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        
    }
    delete[] table;

    cout << "[System] 메모리 해제 완료" << endl;
}

//  [Put 구현]