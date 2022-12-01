#include "ttt_header.h"
#include <SFML/Audio.hpp>
#include <gtkmm.h>
#include <iostream>
#include <thread>

using namespace std;

static sf::Music music;

void play_music()
{
  if (!music.openFromFile("music.ogg"))
      exit(0);
  music.setLoop(true);
  music.play();
  std::cout<<"thread launching (music playing!)"<<std::endl;
}

int main(int argc, char *argv[])
{
  std::thread t(play_music);
  t.join();
	Gtk::Main	app(argc,	argv);
	ttt_window	window;	// create windown object
	Gtk::Main::run(window); // run wwindow
	return	0;
}
