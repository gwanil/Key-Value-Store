# C++ In-Memory Key-Value Store

## 1. 프로젝트 소개 (Overview)
**RocksDB(LSM-Tree)와 NAND Flash 스토리지 연구 경험**을 바탕으로, 데이터베이스 엔진의 가장 기본이 되는 **인메모리 해시 테이블(Hash Table)** 구조를 밑바닥(Scratch)부터 직접 구현한 프로젝트입니다.

단순한 기능 구현을 넘어 **Linux 시스템 프로그래밍 환경(Makefile, 분할 컴파일)**과 **테스트 자동화(File I/O)**를 적용하여, 실제 현업 수준의 유지보수성과 확장성을 고려한 구조로 설계했습니다.

## 2. 개발 환경 (Environment)
* **OS:** Windows 11 (WSL2 - Ubuntu Linux)
* **Language:** C++ (OOP, Pointer, Memory Management)
* **Build System:** **Makefile** (Automated Build)
* **Version Control:** Git / GitHub

## 3. 핵심 기술 및 구현 내용 (Technical Highlights)

### ⚙️ 아키텍처 및 자료구조
* **Hash Table & Chaining:** 배열(Array)과 연결 리스트(Linked List)를 결합하여 해시 충돌(Collision)을 효율적으로 해결했습니다.
* **Double Pointer (`Node**`):** 이중 포인터를 활용하여 버킷(Bucket) 배열과 노드 간의 메모리 연결 구조를 직접 제어했습니다.
* **Modular Design:** 헤더(`include/`)와 소스(`src/`)를 분리하여 의존성을 낮추고 코드 가독성을 높였습니다.

### 🛠️ 빌드 및 테스트 자동화
* **Makefile 적용:** `make` 명령어 하나로 의존성 체크 및 증분 컴파일(Incremental Build)이 가능하도록 빌드 시스템을 구축했습니다.
* **Workload Automation:** `command.txt` 파일을 파싱하여 대량의 데이터 삽입/삭제/조회 명령을 자동으로 수행하는 테스트 러너(Test Runner)를 구현했습니다.
* **Memory Dump:** `printAll()` 기능을 통해 현재 메모리에 적재된 데이터의 구조(Bucket Index 및 Chaining 상태)를 시각적으로 검증할 수 있습니다.

## 4. 폴더 구조 (Directory Structure)
표준 C++ 프로젝트 구조를 준수하여 유지보수성을 높였습니다.
```text
KV_STORE/
├── include/         # 헤더 파일 모음 (.h)
│   └── KVStore.h    # 클래스 및 노드 구조체 선언
├── src/             # 소스 파일 모음 (.cpp)
│   ├── main.cpp     # 프로그램 진입점 (파일 읽기 및 테스트 실행)
│   └── KVStore.cpp  # 핵심 로직 구현 (Put, Get, Remove)
├── command.txt      # 테스트용 명령어 리스트 (Workload)
├── Makefile         # 빌드 자동화 스크립트
└── README.md        # 프로젝트 기술 명세서
````

## 5. 실행 방법 (How to Run)

터미널에서 아래 명령어들을 순서대로 입력하여 빌드 및 실행할 수 있습니다.

**1. 빌드 (Compile)**
`make` 명령어를 통해 소스 코드를 컴파일하고 실행 파일을 생성합니다.

```bash
make
```

**2. 실행 (Execute)**
생성된 `main` 파일을 실행하면 `command.txt`에 적힌 명령어를 자동으로 처리합니다.

```bash
./main
```

**3. 청소 (Clean)**
빌드 과정에서 생성된 오브젝트 파일(.o)과 실행 파일을 삭제합니다.

```bash
make clean
```

## 6\. 트러블 슈팅 (Troubleshooting & Learnings)

### 🔍 Issue 1: 데이터 저장 실패 (Logic Error)

  * **문제:** `put` 함수 호출 후에도 데이터가 저장되지 않고 덤프 시 '비어있음'이 출력되는 현상 발생.
  * **원인:** 포인터 연결 시 대입 연산자(`=`) 대신 비교 연산자(`==`)를 사용하는 오타 발생 (`table[index] == newNode`). 컴파일러 문법 오류가 아니어서 발견이 어려웠음.
  * **해결:** 코드 리뷰를 통해 오타를 수정하고, 저장소 상태를 전체 출력하는 `printAll()` 덤프 함수를 구현하여 데이터 적재 상태를 시각적으로 확인함.

### 🔍 Issue 2: 폴더 구조 분리 후 빌드 오류 (Linker Error)

  * **문제:** 소스 코드를 `src`와 `include` 폴더로 분리하자 컴파일러가 헤더 파일을 찾지 못하는 에러 발생.
  * **해결:** `Makefile`의 컴파일 옵션에 `-I include` 플래그를 추가하여, 컴파일러가 헤더 파일 경로를 명시적으로 참조하도록 설정함.

### 🔍 Issue 3: 메모리 누수 방지 (Memory Leak)

  * **문제:** `new`로 할당된 노드들이 프로그램 종료 후에도 메모리에 남아있는 잠재적 누수 가능성.
  * **해결:** 클래스 소멸자(`~Destructor`)에서 해시 테이블의 모든 버킷을 순회하며 연결 리스트의 노드들을 `delete` 하는 로직을 구현하여 안전하게 자원을 해제함.

-----

**Author:** [ Gwan-il Jeong ]
**Contact:** [ jeonggwanil@gmail.com ]