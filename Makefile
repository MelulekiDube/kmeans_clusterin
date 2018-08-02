#Make file for project_maker
#Created on: Thu Feb 19 00:18:08 1970

#Meluleki Dube
CPP =g++
CPPFLAGS =-std=c++11
TARGET=k_means
SRC=point.cpp cluster.cpp main.cpp
OBJECTS=point.o cluster.o main.o 


$(TARGET): $(OBJECTS)
	$(CPP) $(OBJECTS)-o $@ $(CPPFLAGS)

$(OBJECTS): $(SRC)
	$(CPP) $< -c $(SRC) $(CPPFLAGS)

run:
	./$(TARGET)

clean:
	rm -f -r *.o bin/*.o *.exe

# end of Makefile