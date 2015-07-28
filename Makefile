LIBRARIES = Object.hpp Field.hpp Position.hpp Sprite.hpp Image.hpp Storage.hpp Grass.hpp Headquarters.hpp Knight.hpp Princess.hpp Dragon.hpp Player.hpp Anorak.hpp Moob.hpp
OBJECTS = repka.cpp Object.cpp Field.cpp Position.cpp Sprite.cpp Image.cpp Storage.cpp Grass.cpp Headquarters.cpp Knight.cpp Princess.cpp Dragon.cpp Player.cpp Anorak.cpp Moob.cpp


all : $(OBJECTS) $(LIBRARIES)
	g++ $(OBJECTS) -o repka -framework OpenGL -framework GLUT
tux : $(OBJECTS) $(LIBRARIES)
	g++ $(OBJECTS) -o repka -l GL -l GLU -l glut

open :
	vim -p repka.cpp Player.hpp Field.hpp Headquarters.hpp Princess.hpp Knight.hpp Princess.hpp Grass.hpp
mini :
	./repka 5 5
maxi :
	./repka 60 40
run :
	./repka
