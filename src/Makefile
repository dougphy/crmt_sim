EXEC := mutoy
SRC  := $(wildcard *.cxx)
OBJ  := $(patsubst %.cxx,%.o,$(SRC))

CXX      := g++
CPPFLAGS := -g -O3 -std=c++11 $(shell root-config --cflags)
LDFLAGS  := -g $(shell root-config --ldflags)
LDLIBS   := $(shell root-config --libs)

$(EXEC): $(OBJ)
	@echo Linking into $@ ... Done ;$(CXX) $(LDFLAGS) $(LDLIBS) -o $@ $^
	@cd ..;ln -s src/$(EXEC) mutoy

%.o: %.cxx
	@echo Compiling source file $< ... ;$(CXX) $(CPPFLAGS) -c $<;

%.o: %.h

.PHONY: clean cleanroot

clean:
	@echo Cleaning...
	-@rm -f ../src/*.o
	-@rm -f ../src/$(EXEC)
	-@rm -f ../mutoy
