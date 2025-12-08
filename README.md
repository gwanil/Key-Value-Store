# C++ In-Memory Key-Value Store

## 1. 프로젝트 소개
C++의 **자료구조(Hash Table)**와 **메모리 관리(Dynamic Allocation)** 역량을 기르기 위해 구현한 인메모리 키-밸류 저장소입니다.
리눅스 환경에서 개발되었으며, **Linked List를 이용한 Chaining 기법**으로 해시 충돌(Collision)을 처리했습니다.

## 2. 개발 환경
* **OS:** Windows 11 (WSL2 - Ubuntu)
* **Language:** C++ (Class 기반 객체지향 설계)
* **Tools:** VS Code, Git/GitHub

## 3. 핵심 기능 & 기술적 포인트
* **자료구조:** Hash Table 직접 구현 (배열 + 포인터)
* **충돌 처리:** Chaining 기법 (Linked List) 사용하여 데이터 유실 방지
* **메모리 관리:** * `new`/`delete`를 활용한 동적 할당 관리
    * 소멸자(`~Destructor`)를 통한 완벽한 메모리 해제 (Memory Leak 방지)
* **모듈화:** 헤더(.h)와 소스(.cpp) 분할 컴파일 구조 적용

## 4. 트러블 슈팅 (배운 점)
* **문제:** 데이터 삭제(`remove`) 후에도 메모리 사용량이 줄어들지 않는 현상 발생
* **원인:** 노드의 연결(`next`)만 끊고, 실제 메모리(`delete`)를 해제하지 않음
* **해결:** `delete current`를 명시하여 힙 메모리 누수 해결

## 5. 실행 방법
```bash
g++ main.cpp KeyValueStore.cpp -o main
./main