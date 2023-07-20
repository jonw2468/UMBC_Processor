CXX = g++
CXXFLAGS = -Wall -g
IODIR =../../proj5_IO/

proj5: Process.o Lstack.o Processor.o proj5.cpp
	$(CXX) $(CXXFLAGS) Processor.o Process.o Lstack.cpp proj5.cpp -o proj5

Processor.o: Processor.h Processor.cpp Lstack.o Process.o
	$(CXX) $(CXXFLAGS) -c Processor.cpp

Lstack.o: Lstack.cpp
	$(CXX) $(CXXFLAGS) -c Lstack.cpp

Process.o: Process.h Process.cpp
	$(CXX) $(CXXFLAGS) -c Process.cpp

clean:
	rm *.o*
	rm *~ 

run1:
	./proj5 proj5_data1.txt

run2:
	./proj5 proj5_data2.txt

run3:
	./proj5 proj5_data3.txt

val1:
	valgrind ./proj5 proj5_data1.txt

val2:
	valgrind ./proj5 proj5_data2.txt

val3:
	valgrind ./proj5 proj5_data3.txt

##Used for specifically TESTING Lstack
lstack:
	g++ -Wall lstack_test.cpp Lstack.cpp -o lstack_test

test:
	valgrind ./lstack_test

##Used for grading and testing
##Copies all test files into current directory
copy:
	cp $(IODIR)proj5* .

##Compiles the lqueue test
tf1:
	g++ -Wall proj5_tf_lqueue.cpp Lstack.cpp -o tf1
