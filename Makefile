all: main.cpp
	g++ -g -Wall -Wextra -o bestfit main.cpp

build: main.cpp
	g++ -g -Wall -Wextra -o bestfit main.cpp

run: main.cpp
	./bestfit

# windows
clean:
	del bestfit.exe