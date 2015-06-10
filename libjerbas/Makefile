## file libjerbas/Makefile
CXX=clang
RM= rm -vf
WARNFLAGS= -Wall -Wextra
PREPROFLAGS= -I/usr/local/include
OPTIMFLAGS= -O1 -g
CXXFLAGS=  -std=c++14 $(WARNFLAGS) $(PREPROFLAGS) $(OPTIMFLAGS)

SOURCE_FILES= $(wildcard *.cc)
PICOBJECT_FILES= $(patsubst %.cc, %.pic.o,  $(SOURCE_FILES))
.PHONY: all clean

all: libjerbas.so

libjerbas.so: $(PICOBJECT_FILES)
	$(LINK.cc) -shared -o $@ $^
%.pic.o: %.cc jerbas.hh
	$(COMPILE.cc) -fPIC $< -o $@

clean:
	$(RM) *.o *~ *.so 
