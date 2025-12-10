#include <iostream>
#include <fstream>
#include <sstream>
#include "KVStore.h"

using namespace std;

// int main() {
//     KVStore db(5);

//     cout << "---프로젝트 테스트 시작---" << endl;

//     db.put("apple", "사과");
//     db.put("lemone", "레몬");
//     db.put("banana", "바나나");

//     cout << "apple" << db.get("apple") << endl;
//     cout << "lemone" << db.get("lemone") << endl;

//     db.remove("banana");

//     string result = db.get("banana");
//     if(result == "") {
//         cout << "banana 삭제 확인됨" << endl;
//     }
//     return 0;
// }

int main() {
    KVStore db(100);

    ifstream file("command.txt");
    if(!file.is_open()) {
        cout << "[ERROR] command.txt 파일을 찾을 수 없습니다!" << endl;
        return 0;
    }

    cout << "---파일 자동 처리 시작--" << endl;

    string line, cmd, key, value;

    while (getline(file, line)) {
        stringstream ss(line);
        ss >> cmd >> key;

        if(cmd == "PUT") {
            ss >> value;
            db.put(key, value);
            cout << "[CMD] PUT " << key << " = " << value << endl;
        }
        else if(cmd == "GET") {
            string res = db.get(key);
            cout << "[CMD] GET " << key << " -> 결과: " << (res == ""?"(없음)":res) << endl;
        }
        else if(cmd == "REMOVE") {
            db.remove(key);
            cout << "[CMD] REMOVE " << key << endl;
        }
    }

    file.close();
    cout << "---모든 작업 완료---" << endl;

    db.printAll();
    
    return 0;
}