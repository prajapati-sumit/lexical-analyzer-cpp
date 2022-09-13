# Makefile


# Compiler
CXX = g++

# Compiler flags (including debug info)
CXXFLAGS = -std=c++11

FSM:FSM.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

