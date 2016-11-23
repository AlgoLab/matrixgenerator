# compile the generator
#
cc = g++
objs = src/matrix_generator.o src/matrixgenerator.o \
	src/graycodes.o src/connected.o

matrix_generator : $(objs)  
	$(cc) $^ -o $@

%.o : %.cpp
	$(cc) -c $< -o $@

clean :
	rm -f *~ *\# src/*~ src/*\# $(objs) matrix_generator
