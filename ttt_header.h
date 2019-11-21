#ifndef _TTT_HEADER_H
#define _TTT_HEADER_H

#include <gtkmm.h>
#include <vector>

using namespace std;

class Player
{
	public:
		/**
		* Set the player name
		**/
		string name;
		
		/**
		* Check if user has won, loss, or tied
		* 
		* 0 = reset
		* 1 = won
		* 2 = loss
		* 3 = tie
		**/
		int hasWon;
		
		/**
		* Keeps track of total wins and losses from session
		**/
		int wins, loss;
		
		/**
		* Keeps track of total turns from the game - resets after every game
		**/
		int turns;
		
		/**
		* Player's symbol
		**/
		char symbol;
		
		Player()
		{
			hasWon = 0;
			wins = 0;
			loss = 0;
		}
};

class Board
{
	public:
		/**
		* Saves the moves in this array
		* row x column
		**/
		char boardArray[3][3];
		
		/**
		* Create an empty board, so that we can start the game
		**/
		void intializeBoard();
		
		/**
		* Store the move in the array
		*
		* @param p - is it player one's turn? true = player 1, false = player 2
		* @param row
		* @param column
		**/
		void takeTurn(bool, int, int);
		
		/**
		* Check if anyone has won yet?
		*
		* @return
		*	1 - player 1 won
		*	2 - player 2 won
		**/
		int calculateWin();
		
		/**
		* Check if the spot in the array is open
		*
		* @param row
		* @param column
		* @return
		*	true - spot is open
		*	false - spot is not open
		**/
		bool checkSpace(int, int);
		
		int evaluate();
		bool isMovesLeft();
		
		Board() {}
};

struct Move
{
	int row, col;
};

class Ai
{
	public:
		void performMove(Board);
		int minimax(char[3][3], int, bool);
};

class TTTWindow:public::Gtk::Window
{
	public:
		TTTWindow();
		virtual ~TTTWindow();
	
	protected:
		void set_images();
		void rematch();
		void intializeButtonsToWhite();
		void change_button11();
		void change_button12();
		void change_button13();
		void change_button21();
		void change_button22();
		void change_button23();
		void change_button31();
		void change_button32();
		void change_button33();
		void set_names();
		void close_button();
		void player_label();
		void game_over();
		void aimove();
		void change_button();
		void change_buttons_win(Board &board);
		void save_stats(Player);
		void overwrite_stats(vector<string>);
		
		Gtk::Box textbox, textbox2;
		Gtk::Label label, label2, label3;
		Gtk::Box box;
		Gtk::Entry entry, entry2;
		Gtk::Button button_close,
			button_11,
			button_12,
			button_13,
			button_21,
			button_22,
			button_23,
			button_31,
			button_32,
			button_33,
			button_set,
			button_rematch;
		Gtk::HBox hbox, hbox2, hbox3, close_hbox;
		Gtk::VBox vbox;
		Gtk::Grid grid;
		Gtk::Image white_image,
			white_image2,
			white_image3,
			white_image4,
			white_image5,
			white_image6,
			white_image7,
			white_image8,
			white_image9,
			x_image,
			x_image2,
			x_image3,
			x_image4,
			x_image5,
			x_image6,
			x_image7,
			x_image8,
			x_image9,
			o_image,
			o_image2,
			o_image3,
			o_image4,
			o_image5,
			o_image6,
			o_image7,
			o_image8,
			o_image9,
			x_image_win,
			x_image_win2,
			x_image_win3,
			o_image_win,
			o_image_win2,
			o_image_win3;
};

#endif
