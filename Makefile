CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRC = DP_Survive.cpp
EXECUTABLE = DP_Survive

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)
