all: test_picture

test_picture: test_picture.cpp picture.o
	g++ -o test_picture test_picture.cpp picture.o

ppm.o: picture.h picture.cpp
	g++ -c -o picture.o picture.cpp

clean:
	rm *.o
