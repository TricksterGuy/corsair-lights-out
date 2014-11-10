OUTPUT := corsair-lights-out
CXXFLAGS := -O2 -s -Wall -std=c++11
#CXXFLAGS := -g -Wall -std=c++11
LDFLAGS := -lncurses

all : $(OUTPUT)

$(OUTPUT) : main.o keylib.o
	g++ $^ -o $@ $(LDFLAGS)

clean :
	rm -rf *.o $(OUTPUT)
