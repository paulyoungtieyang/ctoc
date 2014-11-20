all: test_picture

test_picture: test_picture.c ppm.o
	g++ -o test_picture test_picture.c ppm.o

ppm.o: ppm.h ppm.c
	g++ -c -o ppm.o ppm.c

clean:
	rm *.o
