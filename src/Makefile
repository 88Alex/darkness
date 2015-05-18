OBJECTS=darkness.o interpreter.o error.o voicelist.o objects/mainobject.o objects/manipulator.o objects/entropy.o objects/stalker.o objects/sign.o
%.o: %.cpp
	g++ -c -g --std=c++11 $< -o $@
# specify explicit dependencies
darkness.o: interpreter.o
interpreter.o: error.o objects/mainobject.o voicelist.o
objects/mainobject.o: objects/entropy.o objects/stalker.o objects/manipulator.o objects/sign.o
objects/stalker.o: objects/manipulator.o
objects/sign.o: objects/manipulator.o voicelist.o
objects/entropy.o: objects/manipulator.o
darkness: $(OBJECTS)
	g++ $(OBJECTS) -lboost_regex -o darkness
clean: cleanobjfiles
cleanobjfiles:
	rm *.o objects/*.o
all: darkness clean
default: darkness clean
