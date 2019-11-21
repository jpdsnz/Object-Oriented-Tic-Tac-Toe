#include "ttt_header.h"

int main(int argc, char *argv[])
{
	Gtk::Main app(argc, argv);
	TTTWindow window;
	Gtk::Main::run(window);
	return 0;
}
