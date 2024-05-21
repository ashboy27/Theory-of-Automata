
CXX = g++


CXXFLAGS = -std=c++11 -Wall -I/usr/local/include


LDFLAGS = -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system


SOURCES = Button.cpp TextEditor.cpp Dictionary.cpp main.cpp


OBJECTS = $(SOURCES:.cpp=.o)


EXECUTABLE = main


all: $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

# Phony targets
.PHONY: all clean
