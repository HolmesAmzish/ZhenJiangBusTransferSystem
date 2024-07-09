# 变量定义
CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = 
TARGET = ZhenJiangBusTransferSystem

# 源文件及对象文件
SRCS = src/main.cpp src/Controller/UserController.cpp src/Controller/RouteController.cpp src/Menu.cpp
OBJS = $(SRCS:.cpp=.o)

# 默认目标
all: $(TARGET)

# 链接目标
$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

# 生成对象文件
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/Controller/%.o: src/Controller/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
