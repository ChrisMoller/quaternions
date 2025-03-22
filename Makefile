   CFLAGS = -g
  LDFLAGS =
  GL_LIBS = -lm -lGL -lGLU -lglut



%.o:%.cc
	g++ -c $(CFLAGS) $<

all::rot

rot: rot.o Quat.o
	g++ -o $@ $(LDFLAGS) $^

test: test.o Quat.o
	g++ -o $@ $(LDFLAGS) $^

Quat.o: Quat.cc Quat.hh

libQuat.so: Quat.cc
	g++ -c -fPIC Quat.cc
	g++ -shared Quat.o -o $@
	rm -f Quat.o

libinst: libQuat.so
	install libQuat.so -m 744 $(HOME)/local/lib64

anim: anim.o
	g++ -o $@ $(LDFLAGS) $^ $(GL_LIBS)

clean:
	rm -f *.o *.so

veryclean: clean
	rm -f test
