CPP      = g++
CC       = gcc

BIN      = pso.out
OBJ      = pso.o $(LINKOBJ)
LINKOBJ  = pso_algo.o parameter.o solution.o alea.o

TESTOBJ  = test.o $(LINKOBJ)
TEST     = test.out

CXXFLAGS = -std=c++11 -Wall -pg -g3 -O3
CFLAGS   = -Wall -O3

all: $(BIN) 
#$(TEST)

$(BIN): $(OBJ)
	$(CPP) $(OBJ) -o $(BIN) -pg

pso.o: pso.cpp
	$(CPP) -c pso.cpp -o pso.o $(CXXFLAGS)
	
pso_algo.o: pso_algo.cpp
	$(CPP) -c pso_algo.cpp -o pso_algo.o $(CXXFLAGS)

#bechmark_fuc.o: bechmark_fuc.cpp
#	$(CPP) -c bechmark_fuc.cpp -o bechmark_fuc.o $(CXXFLAGS)
	
parameter.o: parameter.cpp
	$(CPP) -c parameter.cpp -o parameter.o $(CXXFLAGS)
	
solution.o: solution.cpp
	$(CPP) -c solution.cpp -o solution.o $(CXXFLAGS)
	
alea.o: alea.cpp
	$(CPP) -c alea.cpp -o alea.o $(CXXFLAGS)
	
clean: 
	rm -f $(OBJ) $(BIN) $(TEST)
	
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
#test
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

$(TEST): $(TESTOBJ)	
	$(CPP) $(TESTOBJ) -o $(TEST)
	
test.o: test.cpp
	$(CPP) -c test.cpp -o test.o $(CXXFLAGS)

help:
	@echo "1  RUN_TIME"
	@echo "2  ITERATION"
	@echo "3  POPULATION"
	@echo "4  FUNC_NUM"
	
		
