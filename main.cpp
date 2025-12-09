#include <iostream>
#include "KVStore.h"

using namespace std;

int main() {
    KVStore db(5);

    cout << "---프로젝트 테스트 시작---" << endl;

    db.put("apple", "사과");
    db.put("lemone", "레몬");
    db.put("banana", "바나나");

    cout << "apple" << db.get("apple") << endl;
    cout << "lemone" << db.get("lemone") << endl;

    db.remove("banana");

    string result = db.get("banana");
    if(result == "") {
        cout << "banana 삭제 확인됨" << endl;
    }
    return 0;
}