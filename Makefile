CC = g++
CFLAGS = -g
	
RM = /bin/rm -f 
all: main 
main: Main.o 
	$(CC) $(CFLAGS) -o RayTracer Main.cpp Shape.cpp LocalGeo.cpp Normal.cpp Point.cpp Ray.cpp Vector.cpp $(LDFLAGS) 

Shape.o: Shape.cpp 
	$(CC) $(CFLAGS) -c Shape.cpp 

LocalGeo.o: LocalGeo.cpp
	$(CC) $(CFLAGS) -c LocalGeo.cpp 

Normal.o: Normal.cpp 
	$(CC) $(CFLAGS) -c Normal.cpp 
 
Point.o: Point.cpp 
	$(CC) $(CFLAGS) -c Point.cpp 
 
Ray.o: Ray.cpp 
	$(CC) $(CFLAGS) -c Ray.cpp 

Vector.o: Vector
	$(CC) $(CFLAGS) -c Vector.cpp 


clean: 
	$(RM) *.o RayTracer
