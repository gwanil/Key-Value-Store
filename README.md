# Lightweight In-Memory Key-Value Store (C++)

![Language](https://img.shields.io/badge/language-C++-orange.svg)
![Platform](https://img.shields.io/badge/platform-Linux-lightgrey.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

## 📖 Project Overview
**Lightweight In-Memory Key-Value Store**는 리눅스 환경에서 대용량 데이터를 메모리상에서 빠르게 처리할 수 있도록 설계된 **경량 데이터베이스 엔진**입니다.

Redis의 아키텍처를 모티브로 하여 C++로 직접 구현하였으며, `PUT`, `GET`, `DELETE` 등 핵심 기능을 자료구조 레벨에서 최적화했습니다. 단순한 기능 구현을 넘어, **디스크 지속성(Persistence)** 기능을 통해 프로그램 종료 후에도 데이터가 유실되지 않도록 설계하여 **시스템 안정성**과 **데이터 무결성**을 확보했습니다.

---

## 🚀 Key Features

* **High Performance:** 해시 테이블(Hash Table) 기반의 $O(1)$ 시간 복잡도를 가지는 빠른 데이터 검색 및 저장.
* **Data Persistence:** 메모리(RAM)에 있는 데이터를 디스크(File)로 저장(`Flush`)하고, 재시작 시 복구(`Load`)하는 기능 구현.
* **Collision Handling:** **Chaining 기법**을 적용하여 해시 충돌(Hash Collision) 발생 시에도 데이터 유실 없이 안정적으로 저장.
* **Command Interface:** 사용자가 직관적으로 명령어를 입력할 수 있는 CLI(Command Line Interface) 환경 제공.
* **Memory Management:** RAII 패턴 및 소멸자(Destructor)를 활용한 철저한 메모리 누수(Memory Leak) 방지.

---

## 🛠 Architecture

```mermaid
graph LR
    A["User / Client"] -->|Command (PUT/GET)| B("Query Processor")
    B -->|"Operation"| C{"KV Engine (Hash Map)"}
    C -->|"Read/Write"| D[RAM ("Memory")]
    C -->|"Flush/Load"| E[Disk ("File System")]

```

1. **Query Processor**: 사용자의 입력 명령어를 파싱하여 엔진에 전달합니다.
2. **KV Engine**: 해시 함수를 통해 데이터가 저장될 버킷(Bucket)의 인덱스를 계산합니다.
3. **Persistence Layer**: 프로그램 종료 시 메모리 상의 데이터를 파일(`data.db`)로 직렬화(Serialization)하여 저장합니다.

---

## 💻 Tech Stack

* **Language:** C++ (C++14 Standard)
* **OS:** Linux (Ubuntu 20.04+)
* **Data Structure:** Custom Hash Map (Linked List for Chaining)
* **Build Tool:** GNU Make (`Makefile`)

---

## 📂 Directory Structure

```bash
KVStore_Engine/
├── include/
│   └── KVStore.h      # 클래스 선언 및 자료구조 정의
├── src/
│   ├── main.cpp       # 메인 엔트리 (CLI 인터페이스)
│   └── KVStore.cpp    # PUT/GET/DELETE 및 파일 입출력 로직   
├── obj/               # 빌드된 오브젝트 파일 (.o)
├── data/              # 데이터 저장소 (persistence file)
├── Makefile           # 빌드 자동화 스크립트
└── README.md          # 프로젝트 문서

```

---

## 🔧 How to Build & Run

### 1. Build

`make` 명령어를 통해 소스 코드를 컴파일합니다.

```bash
$ make
# 빌드 완료! ./kv_engine 으로 실행하세요.

```

### 2. Run

빌드된 엔진을 실행하면 CLI 모드로 진입합니다.

```bash
$ ./kv_engine

```

### 3. Usage Example

```bash
[CMD] GET banana -> 결과: 바나나
[Info] 삭제 완료: apple
[CMD] REMOVE apple
[CMD] GET apple -> 결과: (없음)
---모든 작업 완료---

=== [최종 저장소 상태 Dump] ===
Bucket [9] : {banana : 바나나}
Bucket [79] : {computer : 컴퓨터}
=====================================

[System] 메모리 해제 완료

```

---

## 🔍 Implementation Details (For Interview)

### 1. Hash Collision Resolution (Chaining)

해시 테이블의 충돌 문제를 해결하기 위해 **Chaining(연결 리스트)** 방식을 채택했습니다.

* 충돌 발생 시, 해당 버킷의 Linked List 뒤에 노드를 추가하는 방식으로 구현하여 데이터 유실을 원천 차단했습니다.
* 이를 통해 최악의 경우(Worst Case) $O(N)$이지만, 평균적으로 **$O(1)$의 조회 성능**을 유지하도록 설계했습니다.

### 2. Custom File Persistence

C++의 `fstream`을 활용하여 메모리 데이터를 디스크로 덤프(Dump)하는 기능을 구현했습니다.

* **직렬화(Serialization):** `Key_Length + Key + Value_Length + Value` 형태의 바이너리 포맷으로 저장하여, 저장 용량을 최적화하고 파싱 속도를 높였습니다.

### 3. Memory Safety

C++ 프로젝트의 핵심인 메모리 관리를 위해, 프로그램 종료 시 해시 테이블의 모든 노드를 순회하며 `delete` 하는 소멸자를 명시적으로 구현하여 **Valgrind 테스트 시 메모리 누수 0(Zero)**를 달성했습니다.

---

## 👤 Author

* **Name:** Jeong Gwan-il
* **Role:** Backend & System Software Developer
* **Contact:** jeonggwanil@gmail.com