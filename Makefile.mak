// Makefile

hw1a : vector3.o simpletracer.o
	g++ -std=c++11 -o hw1a vector3.o simpletracer.o

simpletracer.o: types.h vector3.h simpletracer.cpp
	g++ -std=c++11 -c simpletracer.cpp

vector3.o: vector3.cpp vector3.h
	g++ -std=c++11 -c vector3.cpp

clean:
	rm hw1a main.o RayCasting.o Vector3.o