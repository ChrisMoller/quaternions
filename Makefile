   CFLAGS = -g
  LDFLAGS =

%.o:%.cc
	g++ -c $(CFLAGS) $<

all::rot

rot: rot.o Quat.o
	g++ -o $@ $(LDFLAGS) $^

test: test.o Quat.o
	g++ -o $@ $(LDFLAGS) $^

Quat.o: Quat.cc Quat.hh

clean:
	rm -f *.o

veryclean: clean
	rm -f test
