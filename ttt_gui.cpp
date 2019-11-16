// Justin Erdmann
//ID: 1001288553
#include "ttt_header.h"
#include	<iostream>
#include  <gtkmm.h>
#include  <string.h>
#include  <exception>

using namespace std;

Player player1;
Player player2;
Board ttt_board;
bool player_1_turn = true;
bool game_end = false;
string win;
int turns = 0;
int games = 0;

string lowercase(string word){  //function to convert string to all lowercase
  for(int i =0; i<word.size(); i++){
    word.at(i) = tolower(word.at(i));
  }
  return word;
}

ttt_window::ttt_window() :	box(Gtk::ORIENTATION_VERTICAL),  //create window
  	hbox(Gtk::ORIENTATION_VERTICAL,1), hbox2(Gtk::ORIENTATION_VERTICAL,1),
    hbox3(Gtk::ORIENTATION_VERTICAL,1), close_hbox(Gtk::ORIENTATION_HORIZONTAL,1),
    button_close("Close"), button_set("Set Names"), button_rematch("Rematch")
{
  set_images();
  initialize_buttons_to_white();
  ttt_board.initialize_board();
  set_border_width(10);
  set_size_request(600,	600);
  set_title("Tic-Tac-Toe Game");
  add(box);
  box.set_homogeneous(FALSE);
  label.set_text("Enter Name of Player 1: ");
  grid.attach(label,0,0,1,2);
  entry.set_max_length(50);
  entry.set_text("Enter Name");
  entry.select_region(0,	entry.get_text_length());
  grid.attach(entry,0,2,1,2);
  grid.attach(textbox,0,2,1,2);
  label2.set_text("Enter Name of Player 2: ");
  grid.attach(label2,1,0,1,2);
  entry2.set_max_length(50);
  entry2.set_text("Enter Name");
  entry2.select_region(0,	entry2.get_text_length());
  grid.attach(entry2,1,2,1,2);
  grid.attach(textbox2,1,2,1,2);
  button_set.signal_clicked().connect(	sigc::mem_fun(*this, // close button
                          &ttt_window::set_names));
  grid.attach(button_set,0,4,4,1);
  box.pack_start(grid,0,0,0);
  label3.set_text("Game Board: ");
  label3.set_width_chars(10);
  box.pack_start(label3,0,0,0);
  button_11.signal_clicked().connect(	sigc::mem_fun(*this, // close button
                          &ttt_window::change_button11));
  hbox.pack_start(button_11,1,1,5);
  button_12.signal_clicked().connect(	sigc::mem_fun(*this, // close button
                          &ttt_window::change_button12));
  hbox.pack_start(button_12,1,1,5);
  button_13.signal_clicked().connect(	sigc::mem_fun(*this, // close button
                          &ttt_window::change_button13));
  hbox.pack_start(button_13,1,1,5);
  button_21.signal_clicked().connect(	sigc::mem_fun(*this, // close button
                          &ttt_window::change_button21));
  hbox2.pack_start(button_21,1,1,5);
  button_22.signal_clicked().connect(	sigc::mem_fun(*this, // close button
                          &ttt_window::change_button22));
  hbox2.pack_start(button_22,1,1,5);
  button_23.signal_clicked().connect(	sigc::mem_fun(*this, // close button
                          &ttt_window::change_button23));
  hbox2.pack_start(button_23,1,1,5);
  button_31.signal_clicked().connect(	sigc::mem_fun(*this, // close button
                          &ttt_window::change_button31));
  hbox3.pack_start(button_31,1,1,5);
  button_32.signal_clicked().connect(	sigc::mem_fun(*this, // close button
                          &ttt_window::change_button32));
  hbox3.pack_start(button_32,1,1,5);
  button_33.signal_clicked().connect(	sigc::mem_fun(*this, // close button
                          &ttt_window::change_button33));
  hbox3.pack_start(button_33,1,1,5);

  box.pack_start(hbox,1,1,5);
  box.pack_start(hbox2,1,1,5);
  box.pack_start(hbox3,1,1,5);
  button_rematch.signal_clicked().connect(	sigc::mem_fun(*this, // close button
                          &ttt_window::rematch));
  close_hbox.pack_start(button_rematch, 1,1,0);
  button_close.signal_clicked().connect(	sigc::mem_fun(*this, // close button
                          &ttt_window::close_button));
  close_hbox.pack_start(button_close,1,1,1);
  box.pack_start(close_hbox, 1,1,5);
  button_close.set_can_default();
  button_close.grab_default();
  show_all_children();

}


ttt_window::~ttt_window()
{
}

void Board::initialize_board(){
	 for(int i = 0; i < 3; i++){
	   for(int j = 0; j < 3; j++){
			this->board_array[i][j] = '_';
		}
	}
}

void Board::take_turn(bool player_one, int row, int col){
  if(player_one){
    this->board_array[row][col] = 'X';
  }
  else{
    this->board_array[row][col] = 'O';
  }
}

bool Board::check_if_space_open(int row, int col){
  return (this->board_array[row][col] == '_') ? TRUE :  FALSE;
}

int Board::calculate_win(){
    if (this->board_array[0][0] == 'X' && this->board_array[0][1] == 'X' && this->board_array[0][2] == 'X'){
      game_end = TRUE;
		  return 1;
    }
	  if (this->board_array[1][0] == 'X' && this->board_array[1][1] == 'X' && this->board_array[1][2] == 'X'){
      game_end = TRUE;
		  return 1;
    }
	  if (this->board_array[2][0] == 'X' && this->board_array[2][1] == 'X' && this->board_array[2][2] == 'X'){
      game_end = TRUE;
		  return 1;
    }
	  if (this->board_array[0][0] == 'X' && this->board_array[1][0] == 'X' && this->board_array[2][0] == 'X'){
      game_end = TRUE;
		  return 1;
    }
	  if (this->board_array[0][1] == 'X' && this->board_array[1][1] == 'X' && this->board_array[2][1] == 'X'){
      game_end = TRUE;
		  return 1;
    }
	  if (this->board_array[0][2] == 'X' && this->board_array[1][2] == 'X' && this->board_array[2][2] == 'X'){
      game_end = TRUE;
		  return 1;
    }
	  if (this->board_array[0][0] == 'X' && this->board_array[1][1] == 'X' && this->board_array[2][2] == 'X'){
      game_end = TRUE;
		  return 1;
    }
	  if (this->board_array[2][0] == 'X' && this->board_array[1][1] == 'X' && this->board_array[0][2] == 'X'){
      game_end = TRUE;
		  return 1;
    }
	     //second player
	  if (this->board_array[0][0] == 'O' && this->board_array[0][1] == 'O' && this->board_array[0][2] == 'O'){
      game_end = TRUE;
		 return 2;
   }
	  if (this->board_array[1][0] == 'O' && this->board_array[1][1] == 'O' && this->board_array[1][2] == 'O'){
      game_end = TRUE;
  		return 2;
    }
	  if (this->board_array[2][0] == 'O' && this->board_array[2][1] == 'O' && this->board_array[2][2] == 'O'){
      game_end = TRUE;
		  return 2;
    }
	  if (this->board_array[0][0] == 'O' && this->board_array[1][0] == 'O' && this->board_array[2][0] == 'O'){
      game_end = TRUE;
		  return 2;
    }
	  if (this->board_array[0][1] == 'O' && this->board_array[1][1] == 'O' && this->board_array[2][1] == 'O'){
      game_end = TRUE;
		  return 2;
    }
	  if (this->board_array[0][2] == 'O' && this->board_array[1][2] == 'O' && this->board_array[2][2] == 'O'){
      game_end = TRUE;
		  return 2;
    }
	  if (this->board_array[0][0] == 'O' && this->board_array[1][1] == 'O' && this->board_array[2][2] == 'O'){
      game_end = TRUE;
		  return 2;
    }
	  if (this->board_array[2][0] == 'O' && this->board_array[1][1] == 'O' && this->board_array[0][2] == 'O'){
      game_end = TRUE;
		  return 2;
    }

	  return 0;

  }


void ttt_window::set_names(){
  player1.name = entry.get_text();
  player2.name = entry2.get_text();
  Gtk::MessageDialog	dialog(*this,	"Player Names",false,Gtk::MESSAGE_INFO);
  string input = "X's -> Player 1: " + player1.name + "\nO's -> Player 2: " +
  player2.name + "\n\nBEGIN!";
  dialog.set_secondary_text(input);
  dialog.run();
}

void ttt_window:: set_images(){
  white_image.set("white_screen.png");
  white_image2.set("white_screen.png");
  white_image3.set("white_screen.png");
  white_image4.set("white_screen.png");
  white_image5.set("white_screen.png");
  white_image6.set("white_screen.png");
  white_image7.set("white_screen.png");
  white_image8.set("white_screen.png");
  white_image9.set("white_screen.png");
  x_image.set("x_picture.png");
  x_image2.set("x_picture.png");
  x_image3.set("x_picture.png");
  x_image4.set("x_picture.png");
  x_image5.set("x_picture.png");
  x_image6.set("x_picture.png");
  x_image7.set("x_picture.png");
  x_image8.set("x_picture.png");
  x_image9.set("x_picture.png");
  o_image.set("o_picture.jpg");
  o_image2.set("o_picture.jpg");
  o_image3.set("o_picture.jpg");
  o_image4.set("o_picture.jpg");
  o_image5.set("o_picture.jpg");
  o_image6.set("o_picture.jpg");
  o_image7.set("o_picture.jpg");
  o_image8.set("o_picture.jpg");
  o_image9.set("o_picture.jpg");
  x_image_win.set("x_picture_win.png");
  o_image_win.set("o_picture_win.jpg");
}

void ttt_window::initialize_buttons_to_white(){
  button_11.set_image(white_image);
  button_12.set_image(white_image2);
  button_13.set_image(white_image3);
  button_21.set_image(white_image4);
  button_22.set_image(white_image5);
  button_23.set_image(white_image6);
  button_31.set_image(white_image7);
  button_32.set_image(white_image8);
  button_33.set_image(white_image9);
}

void ttt_window::rematch(){
  if(game_end){
    ttt_board.initialize_board();
    ttt_window::initialize_buttons_to_white();
    player_1_turn = TRUE;
    game_end = FALSE;
    turns = 0;
  }
}

void ttt_window::change_button11(){
  if(ttt_board.check_if_space_open(0,0) && game_end == FALSE){
    ttt_board.take_turn(player_1_turn, 0, 0);
    if(player_1_turn == TRUE){
      player1.turns++;
      button_11.set_image(x_image);
      player_1_turn = FALSE;
    }
    else{
      player2.turns++;
      button_11.set_image(o_image);
      player_1_turn = TRUE;
    }
    turns++;
    if(ttt_board.calculate_win()){
      Gtk::MessageDialog	dialog(*this,	"WINNER",false,Gtk::MESSAGE_INFO);
      if(ttt_board.calculate_win() == 1){
        games++;
        player1.wins++;
        win = player1.name + " YOU WON!\n\n" + "Score: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      }
      else{
        games++;
        player2.wins++;
        win = player2.name + " YOU WON!\n\n" + "Score: " + player1.name +
          ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      }
      dialog.set_secondary_text(win);
      dialog.run();
    }
    else if(turns == 9){
      Gtk::MessageDialog	dialog(*this,	"DRAW",false,Gtk::MESSAGE_INFO);
      win = "NO WINNER!\n\nScore: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
      to_string(player2.wins);
      game_end = TRUE;
      dialog.set_secondary_text(win);
      dialog.run();
    }
  }
}

void ttt_window::change_button12(){
  if(ttt_board.check_if_space_open(0,1) && game_end == FALSE){
    ttt_board.take_turn(player_1_turn, 0, 1);
    if(player_1_turn == TRUE){
      player1.turns++;
      button_12.set_image(x_image2);
      player_1_turn = FALSE;
    }
    else{
      player2.turns++;
      button_12.set_image(o_image2);
      player_1_turn = TRUE;
    }
    turns++;
    if(ttt_board.calculate_win()){
      games++;
      Gtk::MessageDialog	dialog(*this,	"WINNER",false,Gtk::MESSAGE_INFO);
      if(ttt_board.calculate_win() == 1){
        player1.wins++;
        win = player1.name + " YOU WON!\n\n" + "Score: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      }
      else{
        player2.wins++;
        win = player2.name + " YOU WON!\n\n" + "Score: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      }
      dialog.set_secondary_text(win);
      dialog.run();
    }else if(turns == 9){
      Gtk::MessageDialog	dialog(*this,	"DRAW",false,Gtk::MESSAGE_INFO);
      win = "NO WINNER!\n\nScore: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
      to_string(player2.wins);
      game_end = TRUE;
      dialog.set_secondary_text(win);
      dialog.run();
    }
  }
}

void ttt_window::change_button13(){
  if(ttt_board.check_if_space_open(0,2) && game_end == FALSE){
    ttt_board.take_turn(player_1_turn, 0, 2);
    if(player_1_turn == TRUE){
      player1.turns++;
      button_13.set_image(x_image3);
      player_1_turn = FALSE;
    }
    else{
      player2.turns++;
      button_13.set_image(o_image3);
      player_1_turn = TRUE;
    }
    turns++;
    if(ttt_board.calculate_win()){
      games++;
      Gtk::MessageDialog	dialog(*this,	"WINNER",false,Gtk::MESSAGE_INFO);
      if(ttt_board.calculate_win() == 1){
        player1.wins++;
        win = player1.name + " YOU WON!\n\n" + "Score: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      }
      else{
        player2.wins++;
        win = player2.name + " YOU WON!\n\n" + "Score: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      }
      dialog.set_secondary_text(win);
      dialog.run();
    }else if(turns == 9){
      Gtk::MessageDialog	dialog(*this,	"DRAW",false,Gtk::MESSAGE_INFO);
      win = "NO WINNER!\n\nScore: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
      to_string(player2.wins);
      game_end = TRUE;
      dialog.set_secondary_text(win);
      dialog.run();
    }
  }
}

void ttt_window::change_button21(){
  if(ttt_board.check_if_space_open(1,0) && game_end == FALSE){
    ttt_board.take_turn(player_1_turn, 1, 0);
    if(player_1_turn == TRUE){
      player1.turns++;
      button_21.set_image(x_image4);
      player_1_turn = FALSE;
    }
    else{
      player2.turns++;
      button_21.set_image(o_image4);
      player_1_turn = TRUE;
    }
    turns++;
    if(ttt_board.calculate_win()){
      games++;
      Gtk::MessageDialog	dialog(*this,	"WINNER",false,Gtk::MESSAGE_INFO);
      if(ttt_board.calculate_win() == 1){
        player1.wins++;
        win = player1.name + " YOU WON!\n\n" + "Score: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      }
      else{
        player2.wins++;
        win = player2.name + " YOU WON!\n\n" + "Score: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      }
      dialog.set_secondary_text(win);
      dialog.run();
    }else if(turns == 9){
      Gtk::MessageDialog	dialog(*this,	"DRAW",false,Gtk::MESSAGE_INFO);
      win = "NO WINNER!\n\nScore: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
      to_string(player2.wins);
      game_end = TRUE;
      dialog.set_secondary_text(win);
      dialog.run();
    }
  }
}

void ttt_window::change_button22(){
  if(ttt_board.check_if_space_open(1,1) && game_end == FALSE){
    ttt_board.take_turn(player_1_turn, 1, 1);
    if(player_1_turn == TRUE){
      player1.turns++;
      button_22.set_image(x_image5);
      player_1_turn = FALSE;
    }
    else{
      player2.turns++;
      button_22.set_image(o_image5);
      player_1_turn = TRUE;
    }
    turns++;
    if(ttt_board.calculate_win()){
      games++;
      Gtk::MessageDialog	dialog(*this,	"WINNER",false,Gtk::MESSAGE_INFO);
      if(ttt_board.calculate_win() == 1){
        player1.wins++;
        win = player1.name + " YOU WON!\n\n" + "Score: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      }
      else{
        player2.wins++;
        win = player2.name + " YOU WON!\n\n" + "Score: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      }
      dialog.set_secondary_text(win);
      dialog.run();
    }else if(turns == 9){
      Gtk::MessageDialog	dialog(*this,	"DRAW",false,Gtk::MESSAGE_INFO);
      win = "NO WINNER!\n\nScore: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
      to_string(player2.wins);
      game_end = TRUE;
      dialog.set_secondary_text(win);
      dialog.run();
    }
  }
}

void ttt_window::change_button23(){
  if(ttt_board.check_if_space_open(1,2) && game_end == FALSE){
    ttt_board.take_turn(player_1_turn, 1, 2);
    if(player_1_turn == TRUE){
      player1.turns++;
      button_23.set_image(x_image6);
      player_1_turn = FALSE;
    }
    else{
      player2.turns++;
      button_23.set_image(o_image6);
      player_1_turn = TRUE;
    }
    turns++;
    if(ttt_board.calculate_win()){
      games++;
      Gtk::MessageDialog	dialog(*this,	"WINNER",false,Gtk::MESSAGE_INFO);
      if(ttt_board.calculate_win() == 1){
        player1.wins++;
        win = player1.name + " YOU WON!\n\n" + "Score: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      }
      else{
        player2.wins++;
        win = player2.name + " YOU WON!\n\n" + "Score: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      }
      dialog.set_secondary_text(win);
      dialog.run();
    }else if(turns == 9){
      Gtk::MessageDialog	dialog(*this,	"DRAW",false,Gtk::MESSAGE_INFO);
      win = "NO WINNER!\n\nScore: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
      to_string(player2.wins);
      game_end = TRUE;
      dialog.set_secondary_text(win);
      dialog.run();
    }
  }
}

void ttt_window::change_button31(){
  if(ttt_board.check_if_space_open(2,0) && game_end == FALSE){
    ttt_board.take_turn(player_1_turn, 2, 0);
    if(player_1_turn == TRUE){
      player1.turns++;
      button_31.set_image(x_image7);
      player_1_turn = FALSE;
    }
    else{
      player2.turns++;
      button_31.set_image(o_image7);
      player_1_turn = TRUE;
    }
    turns++;
    if(ttt_board.calculate_win()){
      games++;
      Gtk::MessageDialog	dialog(*this,	"WINNER",false,Gtk::MESSAGE_INFO);
      if(ttt_board.calculate_win() == 1){
        player1.wins++;
        win = player1.name + " YOU WON!\n\n" + "Score: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      }
      else{
        player2.wins++;
        win = player2.name + " YOU WON!\n\n" + "Score: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      }
      dialog.set_secondary_text(win);
      dialog.run();
    }else if(turns == 9){
      Gtk::MessageDialog	dialog(*this,	"DRAW",false,Gtk::MESSAGE_INFO);
      win = "NO WINNER!\n\nScore: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
      to_string(player2.wins);
      game_end = TRUE;
      dialog.set_secondary_text(win);
      dialog.run();
    }
  }
}

void ttt_window::change_button32(){
  if(ttt_board.check_if_space_open(2,1) && game_end == FALSE){
    ttt_board.take_turn(player_1_turn, 2, 1);
    if(player_1_turn == TRUE){
      player1.turns++;
      button_32.set_image(x_image8);
      player_1_turn = FALSE;
    }
    else{
      player2.turns++;
      button_32.set_image(o_image8);
      player_1_turn = TRUE;
    }
    turns++;
    if(ttt_board.calculate_win()){
      games++;
      Gtk::MessageDialog	dialog(*this,	"WINNER",false,Gtk::MESSAGE_INFO);
      if(ttt_board.calculate_win() == 1){
        player1.wins++;
        win = player1.name + " YOU WON!\n\n" + "Score: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      }
      else{
        player2.wins++;
        win = player2.name + " YOU WON!\n\n" + "Score: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      }
      dialog.set_secondary_text(win);
      dialog.run();
    }else if(turns == 9){
      Gtk::MessageDialog	dialog(*this,	"DRAW",false,Gtk::MESSAGE_INFO);
      win = "NO WINNER!\n\nScore: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
      to_string(player2.wins);
      game_end = TRUE;
      dialog.set_secondary_text(win);
      dialog.run();
    }
  }
}

void ttt_window::change_button33(){
  if(ttt_board.check_if_space_open(2,2) && game_end == FALSE){
    ttt_board.take_turn(player_1_turn, 2, 2);
    if(player_1_turn == TRUE){
      player1.turns++;
      button_33.set_image(x_image9);
      player_1_turn = FALSE;
    }
    else{
      player2.turns++;
      button_33.set_image(o_image9);
      player_1_turn = TRUE;
    }
    turns++;
    if(ttt_board.calculate_win()){
      games++;
      Gtk::MessageDialog	dialog(*this,	"WINNER",false,Gtk::MESSAGE_INFO);
      if(ttt_board.calculate_win() == 1){
        player1.wins++;
        win = player1.name + " YOU WON!\n\n" + "Score: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      }
      else{
        player2.wins++;
        win = player2.name + " YOU WON!\n\n" + "Score: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      }
      dialog.set_secondary_text(win);
      dialog.run();
    }else if(turns == 9){
      Gtk::MessageDialog	dialog(*this,	"DRAW",false,Gtk::MESSAGE_INFO);
      win = "NO WINNER!\n\nScore: " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
      to_string(player2.wins);
      game_end = TRUE;
      dialog.set_secondary_text(win);
      dialog.run();
    }
  }
}

void	ttt_window::close_button()
{
  hide();
  string stats;
  int pstats, p2stats;
  pstats = (((double)player1.wins / (double)games)*100);
  p2stats = (((double)player2.wins / (double)games)*100);
  Gtk::MessageDialog	dialog(*this,	"GAME STATS",false,Gtk::MESSAGE_INFO);
  stats = "SCORE:\t" + player1.name + ": " + to_string(player1.wins) + "\n\t\t\t"
  + player2.name + ": " + to_string(player2.wins) + "\n\n" + "WIN PCT:\t" +
  player1.name + ": " + to_string(pstats) + "%\n\t\t\t" + player2.name +
  ": " + to_string(p2stats) + "%";
  dialog.set_secondary_text(stats);
  dialog.run();
}
