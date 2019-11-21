// Justin Erdmann
//ID: 1001288553
#ifndef ttt_HEADER_H
#define ttt_HEADER_H
#include	<gtkmm.h>

#include  <vector>

using namespace std;

class Player {
public:

  int won = 0;    // 0 loss, 1 is won, 2 is tie
  string name;
  int wins, loss;
  int turns;

  Player() {
    wins = 0;
    loss = 0;
  }
};

class Board {
public:
  char board_array[3][3];

  Board() {

  }

  void initialize_board();
  void take_turn(bool player_one, int row, int col);
  int calculate_win();
  bool check_if_space_open(int row, int col);
  int evaluate();
  bool isMovesLeft();
};

struct Move {
  int row, col;
};

class Ai {
public:

  void performMove(Board & board_array);
  int minimax(char board[3][3], int depth, bool isMax);
};

class ttt_window: public Gtk::Window // main wwindow
{
  public: ttt_window();
  virtual~ttt_window();
  protected:
    //signal	handlers
  void set_images();
  void rematch();
  void initialize_buttons_to_white();
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
  void change_buttons_win(Board &ttt_board);
  void save_stats(Player);
  void overwrite_stats(vector<string>);
  //widgets
  Gtk::Box textbox,
  textbox2;
  Gtk::Label label,
  label2,
  label3;
  Gtk::Box box;
  Gtk::Entry entry,
  entry2;
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
  Gtk::HBox hbox,
  hbox2,
  hbox3,
  close_hbox;
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
