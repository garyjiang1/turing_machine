
proj2: proj2.o TM.o
	$(CXX) -o proj2 $(CXXFLAGS) proj2.o TM.o

proj2.o: proj2.cc 

TM.o: TM.cc TM.h

clean:
	@/bin/rm -f *~ \#*\# core* proj2 *.o
