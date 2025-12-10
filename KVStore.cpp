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
void KVStore::put(string key, string value) {
    int index = hashFunction(key);
    Node* newNode = new Node(key, value);

    if(table[index] == nullptr) {
        table[index] = newNode;
    }
    else {
        Node* current = table[index];
        while (current != nullptr) {
            if(current->key == key){
                current->value = value;
                delete newNode;
                return;
            }
            if(current->next == nullptr) break;
            current = current->next;
        }
        current->next = newNode;
    }
}

//  [Get 구현]
string KVStore::get(string key) {
    int index = hashFunction(key);
    Node* current = table[index];

    while (current != nullptr) {
        if(current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return "";
}

//  [Remove 구현]
void KVStore::remove(string key) {
    int index = hashFunction(key);
    Node* current = table[index];
    Node* prev = nullptr;

    while (current != nullptr) {
        if(current->key == key) {
            if(prev == nullptr) {
                table[index] = current->next;
            }
            else {
                prev->next = current->next;
            }
            delete current;
            cout << "[Info] 삭제 완료: " << key << endl;
            return;
        }
        prev = current;
        current = current->next;
    }
    cout << "[ERROR] key 없음: " << key << endl;
}

void KVStore::printAll() {
    cout << "\n=== [최종 저장소 상태 Dump] ===" << endl;

    bool isEmpty = true;

    for (int i = 0; i < capacity; i++) {
        Node* current = table[i];

        if(current != nullptr) {
            isEmpty = false;
            cout << "Bucket [ " << i << "] : ";

            while (current != nullptr) {
                cout << "{" << current->key << " : " << current->value << "}";

                if (current->next != nullptr) {
                    cout << " -> ";
                }
                current = current->next;
            }
            cout << endl;
        }
    }

    if (isEmpty) {
        cout << "(비어있음)" << endl;
    }
    cout << "=====================================\n" << endl;
}