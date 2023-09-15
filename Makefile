CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRC = DP_Survive.cpp
EXECUTABLE1 = DP_Survive

all: $(EXECUTABLE1)

$(EXECUTABLE1): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXECUTABLE1)

clean:
	rm -f $(EXECUTABLE1)
