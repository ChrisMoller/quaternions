   CFLAGS = -g
  LDFLAGS =
     INCS = -I$(HOME)/.local/include/
#     LIBS = -L $(HOME)/.local/lib64 -lQuat
#     LIBS = -L . -lQuat
     LIBS = -lgsl -lgslcblas -lm
  GL_LIBS = -lm -lGL -lGLU -lglut



%.o:%.cc
	g++ -c $(CFLAGS) $(INCS) $<

libinst: libQuat.so
	install libQuat.so -m 744 $(HOME)/.local/lib64
	install Quat.hh -m 744 $(HOME)/.local/include/libquat

libQuat.so: Quat.cc
	g++ -c -fPIC Quat.cc
	g++ -shared Quat.o -o $@
	rm -f Quat.o

Quat.o: Quat.cc Quat.hh
	g++ -c $(CFLAGS) $<

rot: rot.o libQuat.so
	g++ -o $@ $(LDFLAGS) $< $(LIBS)

test: test.o Quat.o eigens.o
	g++ -o $@ $(LDFLAGS) $^ $(LIBS)

test.o: test.cc tests.h

tests.h: tests.m4
	m4 < $< > $@

#eigen.o: eigen.cc

anim: anim.o
	g++ -o $@ $(LDFLAGS) $^ $(GL_LIBS)

clean:
	rm -f *.o *.so tests.h

veryclean: clean
	rm -f test
