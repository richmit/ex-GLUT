##
# @file      makefile
# @author    Mitch Richling <https://www.mitchr.me/>
# @Copyright Copyright 1997 by Mitch Richling.  All rights reserved.
# @brief     @EOL
# @Keywords  
# @Std       GNUmake BSDmake SYSVmake GenericMake
#
#            Notes here
#            


# Fix for local needs
CXX      = g++
CXXFLAGS = -Wall -O3
CC       = gcc
CFLAGS   = -Wall -O3
#GLLNK    = -lglut -lGL -lGLU -lm
GLLNK    = -lfreeglut -lopengl32 -lglu32 -lm

# For OSX
#GLLNK = -framework AGL -framework GLUT -framework OpenGL -framework Carbon -framework ApplicationServices -lobjc

# Uncomment to build all when make file changes
#SPECDEP=makefile

# Put targets here
TARGETS =  helloWorld boxR lorenzR  lightedSphere mandelbrotGL mandelbrotImageGL mandelbrotIncImageGL tformColor interact surf tex

all : $(TARGETS)
	@echo Make Complete

clean :
	rm -rf a.out *~ *.bak $(TARGETS)
	@echo Make Complete

helloWorld : helloWorld.c $(SPECDEP)
	$(CC) $(CFLAGS) -o helloWorld helloWorld.c $(GLLNK)

lightedSphere : lightedSphere.c $(SPECDEP)
	$(CC) $(CFLAGS) -o lightedSphere lightedSphere.c $(GLLNK)

mandelbrotGL : mandelbrotGL.c $(SPECDEP)
	$(CC) $(CFLAGS) -o mandelbrotGL mandelbrotGL.c $(GLLNK) 

mandelbrotImageGL : mandelbrotImageGL.c $(SPECDEP)
	$(CC) $(CFLAGS) -o mandelbrotImageGL mandelbrotImageGL.c $(GLLNK)

mandelbrotIncImageGL : mandelbrotIncImageGL.c $(SPECDEP)
	$(CC) $(CFLAGS) -o mandelbrotIncImageGL mandelbrotIncImageGL.c $(GLLNK)

tformColor : tformColor.c $(SPECDEP)
	$(CC) $(CFLAGS) -o tformColor tformColor.c $(GLLNK)

interact : interact.c $(SPECDEP)
	$(CC) $(CFLAGS) -o interact interact.c $(GLLNK)

lorenzR : rotAndScaleInteractive.c lorenzC.h $(SPECDEP)
	$(CXX) $(CXXFLAGS) -DMODL=2 -o lorenzR rotAndScaleInteractive.c $(GLLNK)

boxR : rotAndScaleInteractive.c boxNaxis.h $(SPECDEP)
	$(CXX) $(CXXFLAGS) -DMODL=1 -o boxR rotAndScaleInteractive.c $(GLLNK)

surf : rotAndScaleInteractive.c surf.h $(SPECDEP)
	$(CXX) $(CXXFLAGS) -DMODL=3 -o surf rotAndScaleInteractive.c $(GLLNK)

tex : tex.c $(SPECDEP)
	$(CXX) $(CXXFLAGS) -DMODL=3 -o tex tex.c $(GLLNK)
