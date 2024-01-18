all: main

CXX = clang++
SANITIZER = -fsanitize=address -fno-omit-frame-pointer
OPT = -O3

CXXFLAGS = -std=c++17 -pedantic-errors -g -Wall -Wextra
# If you want to see more warnings, comment the line above and uncomment the line below
#CXXFLAGS = -std=c++17 -pedantic-errors -g -Wall -Wextra -Wconversion -Wsign-compare -Wnon-virtual-dtor -Wshadow -Weffc++ -Wold-style-cast -Woverloaded-virtual

SRCS = main.cpp
STUDENT = student_code_2.h
main: $(SRCS) $(STUDENT)
	$(CXX) $(OPT) $(CXXFLAGS) $(SRCS) -o "$@"

memtest: $(SRCS) $(STUDENT) 
	$(CXX) $(OPT) $(CXXFLAGS) $(SANITIZER) $(SRCS) -o "$@"

main-debug: $(SRCS) $(STUDENT) 
	$(CXX) $(CXXFLAGS) $(SRCS) -o "$@"

clean:
	rm -f main main-debug memtest