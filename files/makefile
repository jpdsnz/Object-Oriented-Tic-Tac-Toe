executable: ttt_main.o ttt_gui.o
	@echo "Compiling..."
	@g++ -std=c++11 -o ttt_gui ttt_main.o ttt_gui.o -lsfml-graphics -lsfml-window -lsfml-audio -pthread `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
	@echo "Compiling Successful! type ./ttt_gui to run"
ttt_main.o: ttt_main.cpp
	@g++ -std=c++11 -c ttt_main.cpp -g -pthread `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
ttt_gui.o: ttt_gui.cpp
	@g++ -std=c++11 -c ttt_gui.cpp -g -pthread `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
