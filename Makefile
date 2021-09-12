# Makefile for Writing Make Files Example
 
# *****************************************************
# Variables to control Makefile operation
 
CC = clang++ -std=c++0x -stdlib=libc++
CFLAGS = -Wall -g
 
# ****************************************************
# Targets needed to bring the executable up to date
 
render: main.o 
	$(CC) $(CFLAGS) -o render main.o 
 
# The main.o target can be written more simply
main.o: main.cpp vec3.h utils.h ray.h color.h hittable_list.h hittable.h
	$(CC) $(CFLAGS) -c main.cpp

# ray.o: ray.h 
# 	$(CC) $(CFLAGS) -c ray.h
# vec3.o: vec3.h
# 	$(CC) $(CFLAGS) -c vec3.h
# color.o: color.h vec3.h
# 	$(CC) $(CFLAGS) -c color.h