CXX=g++

settest: set.o settest.o
	$(CXX) set.o settest.o -o settest

set.o: set.cpp set.h
	$(CXX) -c set.cpp

settest.o: settest.cpp set.h
	$(CXX) -c settest.cpp
clean:
	rm -f *.o settest
