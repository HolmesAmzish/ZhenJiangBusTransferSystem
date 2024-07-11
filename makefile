CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = 
TARGET = ZhenJiangBusTransferSystem

SRCS = src/main.cpp src/Controller/UserController.cpp src/Controller/RouteController.cpp src/Menu.cpp src/View.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/Controller/%.o: src/Controller/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
