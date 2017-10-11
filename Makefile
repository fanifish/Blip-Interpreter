CC = g++ 
FLAGS = -g -c -std=c++11

SOURCEDIR =src
BUILDDIR =bin
LIB =inc
EXECUTABLE =blip
SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS = $(addprefix bin/,$(notdir $(SOURCES:.cpp=.o)))


all: dir $(BUILDDIR)/$(EXECUTABLE)

dir:
	mkdir -p $(BUILDDIR)

$(BUILDDIR)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@

$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp
	$(CC) $(FLAGS) $< -o $@ -I $(LIB)

clean:
	rm -f $(BUILDDIR)/*o $(BUILDDIR)/$(EXECUTABLE)
