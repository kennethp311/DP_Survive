CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

all: DP_Survive Test_File_Generator

DP_Survive: DP_Survive.cpp
	$(CXX) $(CXXFLAGS) DP_Survive.cpp -o DP_Survive

Test_File_Generator: Test_File_Generator.cpp
	$(CXX) $(CXXFLAGS) Test_File_Generator.cpp -o Test_File_Generator

clean:
	rm -f DP_Survive Test_File_Generator
