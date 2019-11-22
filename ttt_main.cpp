#include "ttt_header.h"
#include <SFML/Audio.hpp>
#include <gtkmm.h>
#include <iostream>
#include <thread>

using namespace std;

static sf::Music music;

///Play Loop until exit////////
void play_music()
{
  //sf::Music music;
  if (!music.openFromFile("music.ogg"))
      exit(0);
     //return -1; // error
  music.setLoop(true);
  music.play();
  std::cout<<"thread launching (music playing!)"<<std::endl;
}

int main(int argc, char *argv[])
{
	///Thread Start////
  std::thread t(play_music);
  t.join();
	//////////////////
	Gtk::Main app(argc, argv);
	TTTWindow window;
	Gtk::Main::run(window);
	return 0;
}
