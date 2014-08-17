CXX=g++
LD=g++

CXXFLAGS=-O3 -g -std=c++11
LDFLAGS=

PROG=dcg

OBJ=dcg.o

all: $(PROG)

$(PROG): $(OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	/bin/rm -rf $(PROG) $(OBJ)

$(OBJ): dcg.h


