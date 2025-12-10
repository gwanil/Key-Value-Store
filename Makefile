# 컴파일러 설정 (g++)
CXX = g++
# 컴파일 옵션 (-Wall: 경고 켜기, -g: 디버깅 정보 포함), -I include : "헤더 파일은 include 폴더에서 찾아라"
CXXFLAGS = -Wall -g -I include

# 실행 파일 이름
TARGET = main

# 소스 파일들 (여기에 .cpp 파일 다 적으면 됨)
SRCS = src/main.cpp src/KVStore.cpp

# 목적 파일들 (.cpp -> src/main.o)
OBJS = $(SRCS:.cpp=.o)

# 1. 'make' 치면 실행되는 기본 규칙
all: $(TARGET)

# 2. 실행 파일 만드는 규칙 (링킹)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# 3. .cpp를 .o로 만드는 규칙 (컴파일)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 4. 'make clean' 치면 청소하는 규칙
clean:
	rm -f src/*.o $(TARGET)