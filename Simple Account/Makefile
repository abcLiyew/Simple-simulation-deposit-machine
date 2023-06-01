tel:=main
src:=$(wildcard *.cpp)
OBJ:=$(patsubst %.cpp,%.o,$(src))
head:=$(wildcard *.h)

CXXF=-c -Wall

$(tel):$(OBJ)
	g++ -o $@ $^

%.o:%.cpp $(head)
	g++ $(CXXF) $< -o $@

.PHONY:clean
clean:
	del *.o  *.exe