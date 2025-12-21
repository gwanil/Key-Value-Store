# 컴파일러 설정 (C++은 g++)
CXX = g++
CXXFLAGS = -Wall -std=c++14 -Iinclude  # -Iinclude: 헤더 파일 위치 지정

# 소스 파일과 객체 파일 정의
SRCS = src/main.cpp src/KVStore.cpp
OBJS = $(SRCS:src/%.cpp=obj/%.o)
TARGET = kv_engine

# 기본 타겟
all: $(TARGET)

# 실행 파일 생성 규칙
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^
	@echo "Build Complete! Run: ./$(TARGET)"

# 객체 파일(.o) 생성 규칙 (src/*.cpp -> obj/*.o)
obj/%.o: src/%.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 청소 규칙 (make clean)
clean:
	rm -f obj/*.o $(TARGET)
	rm -rf obj