LIBRARIES = Object.h Field.h Position.h Sprite.h Image.h Storage.h Grass.h Headquarters.h Knight.h Princess.h Dragon.h Player.h Anorak.h Moob.h
OBJECTS = repka.cpp Object.cpp Field.cpp Position.cpp Sprite.cpp Image.cpp Storage.cpp Grass.cpp Headquarters.cpp Knight.cpp Princess.cpp Dragon.cpp Player.cpp Anorak.cpp Moob.cpp


all : $(OBJECTS) $(LIBRARIES)
	g++ $(OBJECTS) -o repka -framework OpenGL -framework GLUT
tux : $(OBJECTS) $(LIBRARIES)
	g++ $(OBJECTS) -o repka -l GL -l GLU -l glut

open :
	vim -p repka.cpp Player.h Field.h Headquarters.h Princess.h Knight.h Princess.h Grass.h
mini :
	./repka 5 5
maxi :
	./repka 60 40
run :
	./repka
