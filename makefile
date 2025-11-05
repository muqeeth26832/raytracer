# Define link target
linkTarget = mqRay

# Define libs that we need
LIBS = -lSDL2

# Define any flags
CFLAGS = -std=c++17

# Define the object files that we need to use.
objects = main.o \
		  CApp.o \
		  $(patsubst %.cpp,%.o,$(wildcard ./mqRayTrace/*.cpp))

# Define the rebuildables.
rebuildables = $(objects) $(linkTarget)

# Rule to actually perform the build
$(linkTarget): $(objects)
	g++ -g -o $(linkTarget) $(objects) $(LIBS) $(CFLAGS)

# Rule to create .o files
$.o: %.cpp
	g++ -o $@ -c $< $(CFLAGS)

.PHONEY:
clean:
	rm $(rebuildables)
