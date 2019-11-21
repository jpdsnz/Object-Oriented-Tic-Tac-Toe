// Justin Erdmann
//ID: 1001288553
#include "ttt_header.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <gtkmm.h>
#include <string.h>
#include <exception>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

Player player1;
Player player2;
Ai computer;
Board ttt_board;
bool player_1_turn = true;
bool game_end = false;
bool playerNamesSet = false;
string win;
int turns = 0;
int games = 0;

string lowercase(string word) { //function to convert string to all lowercase
  for (int i = 0; i < word.size(); i++) {
    word.at(i) = tolower(word.at(i));
  }
  return word;
}

ttt_window::ttt_window(): box(Gtk::ORIENTATION_VERTICAL), //create window
  hbox(Gtk::ORIENTATION_VERTICAL, 1), hbox2(Gtk::ORIENTATION_VERTICAL, 1),
  hbox3(Gtk::ORIENTATION_VERTICAL, 1), close_hbox(Gtk::ORIENTATION_HORIZONTAL, 1),
  button_close("Close"), button_set("Set Names"), button_rematch("Rematch") {
    set_images();
    initialize_buttons_to_white();
    ttt_board.initialize_board();
    set_border_width(10);
    set_size_request(600, 600);
    set_title("Tic-Tac-Toe Game");
    add(box);
    box.set_homogeneous(FALSE);
    label.set_text("Enter Name of Player 1: ");
    grid.attach(label, 0, 0, 1, 2);
    entry.set_max_length(50);
    entry.set_text("Enter Name");
    entry.select_region(0, entry.get_text_length());
    grid.attach(entry, 0, 2, 1, 2);
    grid.attach(textbox, 0, 2, 1, 2);
    label2.set_text("Enter Name of Player 2: ");
    grid.attach(label2, 1, 0, 1, 2);
    entry2.set_max_length(50);
    entry2.set_text("Enter Name");
    entry2.select_region(0, entry2.get_text_length());
    grid.attach(entry2, 1, 2, 1, 2);
    grid.attach(textbox2, 1, 2, 1, 2);
    button_set.signal_clicked().connect(sigc::mem_fun( * this, // close button
      &
      ttt_window::set_names));
    grid.attach(button_set, 0, 4, 4, 1);
    box.pack_start(grid, 0, 0, 0);
    label3.set_text("Game Board: ");
    label3.set_width_chars(10);
    box.pack_start(label3, 0, 0, 0);
    button_11.signal_clicked().connect(sigc::mem_fun( * this, // close button
      &
      ttt_window::change_button11));
    hbox.pack_start(button_11, 1, 1, 5);
    button_12.signal_clicked().connect(sigc::mem_fun( * this, // close button
      &
      ttt_window::change_button12));
    hbox.pack_start(button_12, 1, 1, 5);
    button_13.signal_clicked().connect(sigc::mem_fun( * this, // close button
      &
      ttt_window::change_button13));
    hbox.pack_start(button_13, 1, 1, 5);
    button_21.signal_clicked().connect(sigc::mem_fun( * this, // close button
      &
      ttt_window::change_button21));
    hbox2.pack_start(button_21, 1, 1, 5);
    button_22.signal_clicked().connect(sigc::mem_fun( * this, // close button
      &
      ttt_window::change_button22));
    hbox2.pack_start(button_22, 1, 1, 5);
    button_23.signal_clicked().connect(sigc::mem_fun( * this, // close button
      &
      ttt_window::change_button23));
    hbox2.pack_start(button_23, 1, 1, 5);
    button_31.signal_clicked().connect(sigc::mem_fun( * this, // close button
      &
      ttt_window::change_button31));
    hbox3.pack_start(button_31, 1, 1, 5);
    button_32.signal_clicked().connect(sigc::mem_fun( * this, // close button
      &
      ttt_window::change_button32));
    hbox3.pack_start(button_32, 1, 1, 5);
    button_33.signal_clicked().connect(sigc::mem_fun( * this, // close button
      &
      ttt_window::change_button33));
    hbox3.pack_start(button_33, 1, 1, 5);

    box.pack_start(hbox, 1, 1, 5);
    box.pack_start(hbox2, 1, 1, 5);
    box.pack_start(hbox3, 1, 1, 5);
    button_rematch.signal_clicked().connect(sigc::mem_fun( * this, // close button
      &
      ttt_window::rematch));
    close_hbox.pack_start(button_rematch, 1, 1, 0);
    button_close.signal_clicked().connect(sigc::mem_fun( * this, // close button
      &
      ttt_window::close_button));
    close_hbox.pack_start(button_close, 1, 1, 1);
    box.pack_start(close_hbox, 1, 1, 5);
    button_close.set_can_default();
    button_close.grab_default();
    show_all_children();
    Gtk::MessageDialog dialog( * this, "How To Play", false, Gtk::MESSAGE_INFO);
    string input = "To Play a Friend:\tEnter your Names and press \"Set Names\""
    ". Then Begin Playing.\n\nTo Play The Computer: Enter your name as Player 1"
    " then enter \"Computer\" as Player 2. Press Set Names. Then Begin "
    "Playing.";
    dialog.set_secondary_text(input);
    dialog.run();
  }

ttt_window::~ttt_window() {}

void ttt_window::change_button() {
  for (int y = 0; y < 3; y++) {
    for (int x = 0; x < 3; x++) {
      if (ttt_board.board_array[x][y] == 'O') {
        if (x == 0 && y == 0) {
          button_11.set_image(o_image);
        } else if (x == 0 && y == 1) {
          button_12.set_image(o_image2);
        } else if (x == 0 && y == 2) {
          button_13.set_image(o_image3);
        } else if (x == 1 && y == 0) {
          button_21.set_image(o_image4);
        } else if (x == 1 && y == 1) {
          button_22.set_image(o_image5);
        } else if (x == 1 && y == 2) {
          button_23.set_image(o_image6);
        } else if (x == 2 && y == 0) {
          button_31.set_image(o_image7);
        } else if (x == 2 && y == 1) {
          button_32.set_image(o_image8);
        } else if (x == 2 && y == 2) {
          button_33.set_image(o_image9);
        }
      }
    }
  }
}

void Board::initialize_board() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      this->board_array[i][j] = '_';
    }
  }
}

void Board::take_turn(bool player_one, int row, int col) {
  if (player_one) {
    this->board_array[row][col] = 'X';
  } else {
    this->board_array[row][col] = 'O';
  }
}

int Board::evaluate() {
  for (int row = 0; row < 3; row++) {
    if (board_array[row][0] == board_array[row][1] &&
      board_array[row][1] == board_array[row][2]) {
      if (board_array[row][0] == 'O')
        return +10;
      else if (board_array[row][0] == 'X')
        return -10;
    }
  }
  for (int col = 0; col < 3; col++) {
    if (board_array[0][col] == board_array[1][col] &&
      board_array[1][col] == board_array[2][col]) {
      if (board_array[0][col] == 'O')
        return +10;

      else if (board_array[0][col] == 'X')
        return -10;
    }
  }

  // Checking for Diagonals for X or O victory.
  if (board_array[0][0] == board_array[1][1] && board_array[1][1] == board_array[2][2]) {
    if (board_array[0][0] == 'O')
      return +10;
    else if (board_array[0][0] == 'X')
      return -10;
  }

  if (board_array[0][2] == board_array[1][1] && board_array[1][1] == board_array[2][0]) {
    if (board_array[0][2] == 'O')
      return +10;
    else if (board_array[0][2] == 'X')
      return -10;
  }

  // Else if none of them have won then return 0
  return 0;
}

bool Board::isMovesLeft() {
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (board_array[i][j] == '_')
        return true;
  return false;
}

int Ai::minimax(char board[3][3], int depth, bool isMax) {
  int score = ttt_board.evaluate();

  // If Maximizer has won the game return his/her
  // evaluated score
  if (score == 10)
    return score;

  // If Minimizer has won the game return his/her
  // evaluated score
  if (score == -10)
    return score;

  // If there are no more moves and no winner then
  // it is a tie
  if (ttt_board.isMovesLeft() == false)
    return 0;

  // If this maximizer's move
  if (isMax) {
    int best = -1000;

    // Traverse all cells
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        // Check if cell is empty
        if (board[i][j] == '_') {
          // Make the move
          board[i][j] = 'O';

          // Call minimax recursively and choose
          // the maximum value
          best = max(best,
            minimax(board, depth + 1, !isMax));

          // Undo the move
          board[i][j] = '_';
        }
      }
    }
    return best;
  }

  // If this minimizer's move
  else {
    int best = 1000;

    // Traverse all cells
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        // Check if cell is empty
        if (board[i][j] == '_') {
          // Make the move
          board[i][j] = 'X';

          // Call minimax recursively and choose
          // the minimum value
          best = min(best,
            minimax(board, depth + 1, !isMax));

          // Undo the move
          board[i][j] = '_';
        }
      }
    }
    return best;
  }
}

// This will return the best possible move for the player
Move findBestMove(char board[3][3]) {
  int bestVal = -1000;
  Move bestMove;
  bestMove.row = -1;
  bestMove.col = -1;

  // Traverse all cells, evaluate minimax function for
  // all empty cells. And return the cell with optimal
  // value.
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      // Check if cell is empty
      if (board[i][j] == '_') {
        // Make the move
        board[i][j] = 'O';

        // compute evaluation function for this
        // move.
        int moveVal = computer.minimax(board, 0, false);

        // Undo the move
        board[i][j] = '_';

        // If the value of the current move is
        // more than the best value, then update
        // best/
        if (moveVal > bestVal) {
          bestMove.row = i;
          bestMove.col = j;
          bestVal = moveVal;
        }
      }
    }
  }

  return bestMove;
}

bool Board::check_if_space_open(int row, int col) {
  return (this->board_array[row][col] == '_') ? TRUE : FALSE;
}

int Board::calculate_win() {
  if (this->board_array[0][0] == 'X' && this->board_array[0][1] == 'X' && this->board_array[0][2] == 'X') {
    game_end = TRUE;
    return 1;
  }
  if (this->board_array[1][0] == 'X' && this->board_array[1][1] == 'X' && this->board_array[1][2] == 'X') {
    game_end = TRUE;
    return 1;
  }
  if (this->board_array[2][0] == 'X' && this->board_array[2][1] == 'X' && this->board_array[2][2] == 'X') {
    game_end = TRUE;
    return 1;
  }
  if (this->board_array[0][0] == 'X' && this->board_array[1][0] == 'X' && this->board_array[2][0] == 'X') {
    game_end = TRUE;
    return 1;
  }
  if (this->board_array[0][1] == 'X' && this->board_array[1][1] == 'X' && this->board_array[2][1] == 'X') {
    game_end = TRUE;
    return 1;
  }
  if (this->board_array[0][2] == 'X' && this->board_array[1][2] == 'X' && this->board_array[2][2] == 'X') {
    game_end = TRUE;
    return 1;
  }
  if (this->board_array[0][0] == 'X' && this->board_array[1][1] == 'X' && this->board_array[2][2] == 'X') {
    game_end = TRUE;
    return 1;
  }
  if (this->board_array[2][0] == 'X' && this->board_array[1][1] == 'X' && this->board_array[0][2] == 'X') {
    game_end = TRUE;
    return 1;
  }
  //second player
  if (this->board_array[0][0] == 'O' && this->board_array[0][1] == 'O' && this->board_array[0][2] == 'O') {
    game_end = TRUE;
    return 2;
  }
  if (this->board_array[1][0] == 'O' && this->board_array[1][1] == 'O' && this->board_array[1][2] == 'O') {
    game_end = TRUE;
    return 2;
  }
  if (this->board_array[2][0] == 'O' && this->board_array[2][1] == 'O' && this->board_array[2][2] == 'O') {
    game_end = TRUE;
    return 2;
  }
  if (this->board_array[0][0] == 'O' && this->board_array[1][0] == 'O' && this->board_array[2][0] == 'O') {
    game_end = TRUE;
    return 2;
  }
  if (this->board_array[0][1] == 'O' && this->board_array[1][1] == 'O' && this->board_array[2][1] == 'O') {
    game_end = TRUE;
    return 2;
  }
  if (this->board_array[0][2] == 'O' && this->board_array[1][2] == 'O' && this->board_array[2][2] == 'O') {
    game_end = TRUE;
    return 2;
  }
  if (this->board_array[0][0] == 'O' && this->board_array[1][1] == 'O' && this->board_array[2][2] == 'O') {
    game_end = TRUE;
    return 2;
  }
  if (this->board_array[2][0] == 'O' && this->board_array[1][1] == 'O' && this->board_array[0][2] == 'O') {
    game_end = TRUE;
    return 2;
  }

  return 0;

}

void ttt_window::set_names() {
  player1.name = entry.get_text();
  player2.name = entry2.get_text();
  if (lowercase(player2.name) == "computer") {
    Gtk::MessageDialog dialog( * this, "Computer", false, Gtk::MESSAGE_INFO);
    string input = "You Chose to play the Computer\n\nPrepare To Lose!";
    dialog.set_secondary_text(input);
    dialog.run();
  } else {
    Gtk::MessageDialog dialog( * this, "Player Names", false, Gtk::MESSAGE_INFO);
    string input = "X's -> Player 1: " + player1.name + "\nO's -> Player 2: " +
      player2.name + "\n\nBEGIN!";
    dialog.set_secondary_text(input);
    dialog.run();
  }
  player_label();
  playerNamesSet = true;
}

void ttt_window::set_images() {
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
  x_image_win2.set("x_picture_win.png");
  x_image_win3.set("x_picture_win.png");
  o_image_win.set("o_picture_win.jpg");
  o_image_win2.set("o_picture_win.jpg");
  o_image_win3.set("o_picture_win.jpg");
}

void ttt_window::initialize_buttons_to_white() {
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

void ttt_window::player_label() {
  string players;
  if (player_1_turn) {
    players = player1.name + ", it's your turn.";
  } else {
    players = player2.name + ", its your turn.";
  }
  label3.set_text(players);
}

void ttt_window::game_over() {
  if (game_end) {
    label3.set_text("GAME OVER: Rematch or Close");
    save_stats(player1);
    save_stats(player2);
  }
}

void ttt_window::save_stats(Player p)
{
  ifstream file("stats.txt");
  bool isPlayerNew = true;
  string line;
  vector<string> all_stats;
  if(file.is_open())
  {
    while(getline(file, line))
    {
      string name, swins, sloss, sties;
      stringstream s(line);
      s >> name >> swins >> sloss >> sties;
      if(lowercase(name).compare(lowercase(p.name)) == 0)
      {
        isPlayerNew = false;
        string newline;
        int playerTies = games - p.wins - p.loss;
        newline.append(p.name); newline.append(" ");
        if(p.won == 1)
        {
          newline.append(to_string(stoi(swins)+1)); newline.append(" ");
          newline.append(to_string(stoi(sloss))); newline.append(" ");
          newline.append(to_string(stoi(sties))); newline.append(" ");
        }
        else if(p.won == 0)
        {
          newline.append(to_string(stoi(swins))); newline.append(" ");
          newline.append(to_string(stoi(sloss)+1)); newline.append(" ");
          newline.append(to_string(stoi(sties))); newline.append(" ");
        }
        else
        {
          newline.append(to_string(stoi(swins))); newline.append(" ");
          newline.append(to_string(stoi(sloss))); newline.append(" ");
          newline.append(to_string(stoi(sties)+1)); newline.append(" ");
        }
        all_stats.push_back(newline);
      }
      else all_stats.push_back(line);
    }

    if(isPlayerNew)
    {
      string newline;
      int playerTies = games - p.wins - p.loss;
      newline.append(p.name); newline.append(" ");
      if(p.won == 1)
      {
        newline.append("1"); newline.append(" ");
        newline.append("0"); newline.append(" ");
        newline.append("0"); newline.append(" ");
      }
      else if(p.won == 0)
      {
        newline.append("0"); newline.append(" ");
        newline.append("1"); newline.append(" ");
        newline.append("0"); newline.append(" ");
      }
      else
      {
        newline.append("0"); newline.append(" ");
        newline.append("0"); newline.append(" ");
        newline.append("1"); newline.append(" ");
      }
      all_stats.push_back(newline);
    }
  }
      /*
      string name, swins, sloss, sties;
      stringstream s(line);
      s >> name >> swins >> sloss >> sties;
      if(lowercase(name).compare(lowercase(p.name)))
      {
        isPlayerNew = false;
        string newline;
        int playerTies = games - p.wins - p.loss;
        newline.append(p.name); newline.append(" ");
        newline.append(to_string(stoi(swins)+p.wins)); newline.append(" ");
        newline.append(to_string(stoi(sloss)+p.loss)); newline.append(" ");
        newline.append(to_string(stoi(sties)+playerTies)); newline.append(" ");
        all_stats.push_back(newline);
      }
      else all_stats.push_back(line);
    }

    if(isPlayerNew)
    {
      string newline;
      int playerTies = games - p.wins - p.loss;
      newline.append(p.name); newline.append(" ");
      newline.append(to_string(p.wins)); newline.append(" ");
      newline.append(to_string(p.loss)); newline.append(" ");
      newline.append(to_string(playerTies)); newline.append(" ");
      all_stats.push_back(newline);
    }
  }
*/
  file.close();

  overwrite_stats(all_stats);
}

void ttt_window::overwrite_stats(vector<string> snames)
{
  for(int i = 0; i < snames.size(); i++)
  {
    cout << snames.at(i);
  }

  ofstream output_file("stats.txt");
  ostream_iterator<string> output_iterator(output_file, "\n");
  copy(snames.begin(), snames.end(), output_iterator);
}

void ttt_window::rematch() {
  if (game_end) {
    ttt_board.initialize_board();
    ttt_window::initialize_buttons_to_white();
    player_1_turn = TRUE;
    game_end = FALSE;
    turns = 0;
    player_label();
  }
}

void ttt_window::change_buttons_win(Board &ttt_board){
    if (ttt_board.board_array[0][0] == 'X' && ttt_board.board_array[0][1] == 'X' && ttt_board.board_array[0][2] == 'X') {
      button_11.set_image(x_image_win);
      button_12.set_image(x_image_win2);
      button_13.set_image(x_image_win3);
    }
    if (ttt_board.board_array[1][0] == 'X' && ttt_board.board_array[1][1] == 'X' && ttt_board.board_array[1][2] == 'X') {
      button_21.set_image(x_image_win);
      button_22.set_image(x_image_win2);
      button_23.set_image(x_image_win3);
    }
    if (ttt_board.board_array[2][0] == 'X' && ttt_board.board_array[2][1] == 'X' && ttt_board.board_array[2][2] == 'X') {
      button_31.set_image(x_image_win);
      button_32.set_image(x_image_win2);
      button_33.set_image(x_image_win3);
    }
    if (ttt_board.board_array[0][0] == 'X' && ttt_board.board_array[1][0] == 'X' && ttt_board.board_array[2][0] == 'X') {
      button_11.set_image(x_image_win);
      button_21.set_image(x_image_win2);
      button_31.set_image(x_image_win3);
    }
    if (ttt_board.board_array[0][1] == 'X' && ttt_board.board_array[1][1] == 'X' && ttt_board.board_array[2][1] == 'X') {
      button_12.set_image(x_image_win);
      button_22.set_image(x_image_win2);
      button_32.set_image(x_image_win3);
    }
    if (ttt_board.board_array[0][2] == 'X' && ttt_board.board_array[1][2] == 'X' && ttt_board.board_array[2][2] == 'X') {
      button_13.set_image(x_image_win);
      button_23.set_image(x_image_win2);
      button_33.set_image(x_image_win3);
    }
    if (ttt_board.board_array[0][0] == 'X' && ttt_board.board_array[1][1] == 'X' && ttt_board.board_array[2][2] == 'X') {
      button_11.set_image(x_image_win);
      button_22.set_image(x_image_win2);
      button_33.set_image(x_image_win3);
    }
    if (ttt_board.board_array[2][0] == 'X' && ttt_board.board_array[1][1] == 'X' && ttt_board.board_array[0][2] == 'X') {
      button_31.set_image(x_image_win);
      button_22.set_image(x_image_win2);
      button_13.set_image(x_image_win3);
    }
    //second player
    if (ttt_board.board_array[0][0] == 'O' && ttt_board.board_array[0][1] == 'O' && ttt_board.board_array[0][2] == 'O') {
      button_11.set_image(o_image_win);
      button_12.set_image(o_image_win2);
      button_13.set_image(o_image_win3);
    }
    if (ttt_board.board_array[1][0] == 'O' && ttt_board.board_array[1][1] == 'O' && ttt_board.board_array[1][2] == 'O') {
      button_21.set_image(o_image_win);
      button_22.set_image(o_image_win2);
      button_23.set_image(o_image_win3);
    }
    if (ttt_board.board_array[2][0] == 'O' && ttt_board.board_array[2][1] == 'O' && ttt_board.board_array[2][2] == 'O') {
      button_31.set_image(o_image_win);
      button_32.set_image(o_image_win2);
      button_33.set_image(o_image_win3);
    }
    if (ttt_board.board_array[0][0] == 'O' && ttt_board.board_array[1][0] == 'O' && ttt_board.board_array[2][0] == 'O') {
      button_11.set_image(o_image_win);
      button_21.set_image(o_image_win2);
      button_31.set_image(o_image_win3);
    }
    if (ttt_board.board_array[0][1] == 'O' && ttt_board.board_array[1][1] == 'O' && ttt_board.board_array[2][1] == 'O') {
      button_12.set_image(o_image_win);
      button_22.set_image(o_image_win2);
      button_32.set_image(o_image_win3);
    }
    if (ttt_board.board_array[0][2] == 'O' && ttt_board.board_array[1][2] == 'O' && ttt_board.board_array[2][2] == 'O') {
      button_13.set_image(o_image_win);
      button_23.set_image(o_image_win2);
      button_33.set_image(o_image_win3);
    }
    if (ttt_board.board_array[0][0] == 'O' && ttt_board.board_array[1][1] == 'O' && ttt_board.board_array[2][2] == 'O') {
      button_11.set_image(o_image_win);
      button_22.set_image(o_image_win2);
      button_33.set_image(o_image_win3);
    }
    if (ttt_board.board_array[2][0] == 'O' && ttt_board.board_array[1][1] == 'O' && ttt_board.board_array[0][2] == 'O') {
      button_31.set_image(o_image_win);
      button_22.set_image(o_image_win2);
      button_13.set_image(o_image_win3);
    }

}

void ttt_window::change_button11() {
  if (ttt_board.check_if_space_open(0, 0) && !game_end && playerNamesSet) {
    if (player_1_turn == TRUE) {
      ttt_board.take_turn(player_1_turn, 0, 0);
      player1.turns++;
      button_11.set_image(x_image);
      player_1_turn = FALSE;
      turns++;
    } else if (lowercase(player2.name) != "computer") {
      ttt_board.take_turn(player_1_turn, 0, 0);
      player2.turns++;
      button_11.set_image(o_image);
      player_1_turn = TRUE;
      turns++;
    }
    if (lowercase(player2.name) == "computer" && turns < 9) {
      Move bestMove = findBestMove(ttt_board.board_array);
      ttt_board.board_array[bestMove.row][bestMove.col] = 'O';
      change_button();
      player_1_turn = TRUE;
      turns++;
    }
    if (ttt_board.calculate_win()) {
      games++;
      Gtk::MessageDialog dialog( * this, "WINNER", false, Gtk::MESSAGE_INFO);
      if (ttt_board.calculate_win() == 1) {
        player1.wins++;
        player1.won = 1;
        player2.loss++;
        player2.won = 0;
        win = player1.name + " YOU WON!\n\n" + "Score:  " + player1.name +
          ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
          to_string(player2.wins);
      } else {
        player1.loss++;
        player1.won = 0;
        player2.wins++;
        player2.won = 1;
        win = player2.name + " YOU WON!\n\n" + "Score:  " + player1.name +
          ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
          to_string(player2.wins);
      }
      change_buttons_win(ttt_board);
      dialog.set_secondary_text(win);
      dialog.run();
    }
    if (turns == 9 && ttt_board.calculate_win() == 0) {
      Gtk::MessageDialog dialog( * this, "DRAW", false, Gtk::MESSAGE_INFO);
      win = "NO WINNER!\n\nScore:  " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      player1.won = 2;
      player2.won = 2;
      game_end = TRUE;
      games++;
      dialog.set_secondary_text(win);
      dialog.run();
    }

    player_label();
  }

  game_over();
}

void ttt_window::change_button12() {
  if (ttt_board.check_if_space_open(0, 1) && !game_end && playerNamesSet) {
    if (player_1_turn == TRUE) {
      ttt_board.take_turn(player_1_turn, 0, 1);
      player1.turns++;
      button_12.set_image(x_image2);
      player_1_turn = FALSE;
      turns++;
    } else if (lowercase(player2.name) != "computer") {
      ttt_board.take_turn(player_1_turn, 0, 1);
      player2.turns++;
      button_12.set_image(o_image2);
      player_1_turn = TRUE;
      turns++;
    }
    if (lowercase(player2.name) == "computer" && turns != 9) {
      Move bestMove = findBestMove(ttt_board.board_array);
      ttt_board.board_array[bestMove.row][bestMove.col] = 'O';
      change_button();
      player_1_turn = TRUE;
      turns++;
    }
    if (ttt_board.calculate_win()) {
      games++;
      Gtk::MessageDialog dialog( * this, "WINNER", false, Gtk::MESSAGE_INFO);
      if (ttt_board.calculate_win() == 1) {
        player1.wins++;
        player1.won = 1;
        player2.loss++;
        player2.won = 0;
        win = player1.name + " YOU WON!\n\n" + "Score:  " + player1.name +
          ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
          to_string(player2.wins);
      } else {
        player1.loss++;
        player1.won = 0;
        player2.wins++;
        player2.won = 1;
        win = player2.name + " YOU WON!\n\n" + "Score:  " + player1.name +
          ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
          to_string(player2.wins);
      }
      change_buttons_win(ttt_board);
      dialog.set_secondary_text(win);
      dialog.run();
    }
    if (turns == 9 && ttt_board.calculate_win() == 0) {
      Gtk::MessageDialog dialog( * this, "DRAW", false, Gtk::MESSAGE_INFO);
      win = "NO WINNER!\n\nScore:  " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      player1.won = 2;
      player2.won = 2;
      game_end = TRUE;
      games++;
      dialog.set_secondary_text(win);
      dialog.run();
    }

    player_label();
  }

  game_over();
}

void ttt_window::change_button13() {
  if (ttt_board.check_if_space_open(0, 2) && !game_end && playerNamesSet) {
    if (player_1_turn == TRUE) {
      ttt_board.take_turn(player_1_turn, 0, 2);
      player1.turns++;
      button_13.set_image(x_image3);
      player_1_turn = FALSE;
      turns++;
    } else if (lowercase(player2.name) != "computer") {
      ttt_board.take_turn(player_1_turn, 0, 2);
      player2.turns++;
      button_13.set_image(o_image3);
      player_1_turn = TRUE;
      turns++;
    }
    if (lowercase(player2.name) == "computer" && turns < 9) {
      Move bestMove = findBestMove(ttt_board.board_array);
      ttt_board.board_array[bestMove.row][bestMove.col] = 'O';
      change_button();
      player_1_turn = TRUE;
      turns++;
    }
    if (ttt_board.calculate_win()) {
      games++;
      Gtk::MessageDialog dialog( * this, "WINNER", false, Gtk::MESSAGE_INFO);
      if (ttt_board.calculate_win() == 1) {
        player1.wins++;
        player1.won = 1;
        player2.loss++;
        player2.won = 0;
        win = player1.name + " YOU WON!\n\n" + "Score:  " + player1.name +
          ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
          to_string(player2.wins);
      } else {
        player1.loss++;
        player1.won = 0;
        player2.wins++;
        player2.won = 1;
        win = player2.name + " YOU WON!\n\n" + "Score:  " + player1.name +
          ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
          to_string(player2.wins);
      }
      change_buttons_win(ttt_board);
      dialog.set_secondary_text(win);
      dialog.run();
    }
    if (turns == 9 && ttt_board.calculate_win() == 0) {
      Gtk::MessageDialog dialog( * this, "DRAW", false, Gtk::MESSAGE_INFO);
      win = "NO WINNER!\n\nScore:  " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      player1.won = 2;
      player2.won = 2;
      game_end = TRUE;
      games++;
      dialog.set_secondary_text(win);
      dialog.run();
    }

    player_label();
  }

  game_over();
}

void ttt_window::change_button21() {
  if (ttt_board.check_if_space_open(1, 0) && !game_end && playerNamesSet) {
    if (player_1_turn == TRUE) {
      ttt_board.take_turn(player_1_turn, 1, 0);
      player1.turns++;
      button_21.set_image(x_image4);
      player_1_turn = FALSE;
      turns++;
    } else if (lowercase(player2.name) != "computer") {
      ttt_board.take_turn(player_1_turn, 1, 0);
      player2.turns++;
      button_21.set_image(o_image4);
      player_1_turn = TRUE;
      turns++;
    }
    if (lowercase(player2.name) == "computer" && turns < 9) {
      Move bestMove = findBestMove(ttt_board.board_array);
      ttt_board.board_array[bestMove.row][bestMove.col] = 'O';
      change_button();
      player_1_turn = TRUE;
      turns++;
    }
    if (ttt_board.calculate_win()) {
      games++;
      Gtk::MessageDialog dialog( * this, "WINNER", false, Gtk::MESSAGE_INFO);
      if (ttt_board.calculate_win() == 1) {
        player1.wins++;
        player1.won = 1;
        player2.loss++;
        player2.won = 0;
        win = player1.name + " YOU WON!\n\n" + "Score:  " + player1.name +
          ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
          to_string(player2.wins);
      } else {
        player1.loss++;
        player1.won = 0;
        player2.wins++;
        player2.won = 1;
        win = player2.name + " YOU WON!\n\n" + "Score:  " + player1.name +
          ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
          to_string(player2.wins);
      }
      change_buttons_win(ttt_board);
      dialog.set_secondary_text(win);
      dialog.run();
    }
    if (turns == 9 && ttt_board.calculate_win() == 0) {
      Gtk::MessageDialog dialog( * this, "DRAW", false, Gtk::MESSAGE_INFO);
      win = "NO WINNER!\n\nScore:  " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      player1.won = 2;
      player2.won = 2;
      game_end = TRUE;
      games++;
      dialog.set_secondary_text(win);
      dialog.run();
    }

    player_label();
  }

  game_over();
}

void ttt_window::change_button22() {
  if (ttt_board.check_if_space_open(1, 1) && !game_end && playerNamesSet) {
    if (player_1_turn == TRUE) {
      ttt_board.take_turn(player_1_turn, 1, 1);
      player1.turns++;
      button_22.set_image(x_image5);
      player_1_turn = FALSE;
      turns++;
    } else if (lowercase(player2.name) != "computer") {
      ttt_board.take_turn(player_1_turn, 1, 1);
      player2.turns++;
      button_22.set_image(o_image5);
      player_1_turn = TRUE;
      turns++;
    }
    if (lowercase(player2.name) == "computer" && turns < 9) {
      Move bestMove = findBestMove(ttt_board.board_array);
      ttt_board.board_array[bestMove.row][bestMove.col] = 'O';
      change_button();
      player_1_turn = TRUE;
      turns++;
    }
    if (ttt_board.calculate_win()) {
      games++;
      Gtk::MessageDialog dialog( * this, "WINNER", false, Gtk::MESSAGE_INFO);
      if (ttt_board.calculate_win() == 1) {
        player1.wins++;
        player1.won = 1;
        player2.loss++;
        player2.won = 0;
        win = player1.name + " YOU WON!\n\n" + "Score:  " + player1.name +
          ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
          to_string(player2.wins);
      } else {
        player1.loss++;
        player1.won = 0;
        player2.wins++;
        player2.won = 1;
        win = player2.name + " YOU WON!\n\n" + "Score:  " + player1.name +
          ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
          to_string(player2.wins);
      }
      change_buttons_win(ttt_board);
      dialog.set_secondary_text(win);
      dialog.run();
    }
    if (turns == 9 && ttt_board.calculate_win() == 0) {
      Gtk::MessageDialog dialog( * this, "DRAW", false, Gtk::MESSAGE_INFO);
      win = "NO WINNER!\n\nScore:  " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      player1.won = 2;
      player2.won = 2;
      game_end = TRUE;
      games++;
      dialog.set_secondary_text(win);
      dialog.run();
    }

    player_label();
  }

  game_over();
}
void ttt_window::change_button23() {
  if (ttt_board.check_if_space_open(1, 2) && !game_end && playerNamesSet) {
    if (player_1_turn == TRUE) {
      ttt_board.take_turn(player_1_turn, 1, 2);
      player1.turns++;
      button_23.set_image(x_image6);
      player_1_turn = FALSE;
      turns++;
    } else if (lowercase(player2.name) != "computer") {
      ttt_board.take_turn(player_1_turn, 1, 2);
      player2.turns++;
      button_23.set_image(o_image6);
      player_1_turn = TRUE;
      turns++;
    }
    if (lowercase(player2.name) == "computer" && turns < 9) {
      Move bestMove = findBestMove(ttt_board.board_array);
      ttt_board.board_array[bestMove.row][bestMove.col] = 'O';
      change_button();
      player_1_turn = TRUE;
      turns++;
    }
    if (ttt_board.calculate_win()) {
      games++;
      Gtk::MessageDialog dialog( * this, "WINNER", false, Gtk::MESSAGE_INFO);
      if (ttt_board.calculate_win() == 1) {
        player1.wins++;
        player1.won = 1;
        player2.loss++;
        player2.won = 0;
        win = player1.name + " YOU WON!\n\n" + "Score:  " + player1.name +
          ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
          to_string(player2.wins);
      } else {
        player1.loss++;
        player1.won = 0;
        player2.wins++;
        player2.won = 1;
        win = player2.name + " YOU WON!\n\n" + "Score:  " + player1.name +
          ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
          to_string(player2.wins);
      }
      change_buttons_win(ttt_board);
      dialog.set_secondary_text(win);
      dialog.run();
    }
    if (turns == 9 && ttt_board.calculate_win() == 0) {
      Gtk::MessageDialog dialog( * this, "DRAW", false, Gtk::MESSAGE_INFO);
      win = "NO WINNER!\n\nScore:  " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      player1.won = 2;
      player2.won = 2;
      game_end = TRUE;
      games++;
      dialog.set_secondary_text(win);
      dialog.run();
    }

    player_label();
  }

  game_over();
}

void ttt_window::change_button31() {
  if (ttt_board.check_if_space_open(2, 0) && !game_end && playerNamesSet) {
    if (player_1_turn == TRUE) {
      ttt_board.take_turn(player_1_turn, 2, 0);
      player1.turns++;
      button_31.set_image(x_image7);
      player_1_turn = FALSE;
      turns++;
    } else if (lowercase(player2.name) != "computer") {
      ttt_board.take_turn(player_1_turn, 2, 0);
      player2.turns++;
      button_31.set_image(o_image7);
      player_1_turn = TRUE;
      turns++;
    }
    if (lowercase(player2.name) == "computer" && turns < 9) {
      Move bestMove = findBestMove(ttt_board.board_array);
      ttt_board.board_array[bestMove.row][bestMove.col] = 'O';
      change_button();
      player_1_turn = TRUE;
      turns++;
    }

    if (ttt_board.calculate_win()) {
      games++;
      Gtk::MessageDialog dialog( * this, "WINNER", false, Gtk::MESSAGE_INFO);
      if (ttt_board.calculate_win() == 1) {
        player1.wins++;
        player1.won = 1;
        player2.loss++;
        player2.won = 0;
        win = player1.name + " YOU WON!\n\n" + "Score:  " + player1.name +
          ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
          to_string(player2.wins);
      } else {
        player1.loss++;
        player1.won = 0;
        player2.wins++;
        player2.won = 1;
        win = player2.name + " YOU WON!\n\n" + "Score:  " + player1.name +
          ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
          to_string(player2.wins);
      }
      change_buttons_win(ttt_board);
      dialog.set_secondary_text(win);
      dialog.run();
    }
    if (turns == 9 && ttt_board.calculate_win() == 0) {
      Gtk::MessageDialog dialog( * this, "DRAW", false, Gtk::MESSAGE_INFO);
      win = "NO WINNER!\n\nScore:  " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      player1.won = 2;
      player2.won = 2;
      game_end = TRUE;
      games++;
      dialog.set_secondary_text(win);
      dialog.run();
    }

    player_label();
  }

  game_over();
}

void ttt_window::change_button32() {
  if (ttt_board.check_if_space_open(2, 1) && !game_end && playerNamesSet) {
    if (player_1_turn == TRUE) {
      ttt_board.take_turn(player_1_turn, 2, 1);
      player1.turns++;
      button_32.set_image(x_image8);
      player_1_turn = FALSE;
      turns++;
    } else if (lowercase(player2.name) != "computer") {
      ttt_board.take_turn(player_1_turn, 2, 1);
      player2.turns++;
      button_32.set_image(o_image8);
      player_1_turn = TRUE;
      turns++;
    }
    if (lowercase(player2.name) == "computer" && turns < 9) {
      Move bestMove = findBestMove(ttt_board.board_array);
      ttt_board.board_array[bestMove.row][bestMove.col] = 'O';
      change_button();
      player_1_turn = TRUE;
      turns++;
    }

    if (ttt_board.calculate_win()) {
      games++;
      Gtk::MessageDialog dialog( * this, "WINNER", false, Gtk::MESSAGE_INFO);
      if (ttt_board.calculate_win() == 1) {
        player1.wins++;
        player1.won = 1;
        player2.loss++;
        player2.won = 0;
        win = player1.name + " YOU WON!\n\n" + "Score:  " + player1.name +
          ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
          to_string(player2.wins);
      } else {
        player1.loss++;
        player1.won = 0;
        player2.wins++;
        player2.won = 1;
        win = player2.name + " YOU WON!\n\n" + "Score:  " + player1.name +
          ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
          to_string(player2.wins);
      }
      change_buttons_win(ttt_board);
      dialog.set_secondary_text(win);
      dialog.run();
    }
    if (turns == 9 && ttt_board.calculate_win() == 0) {
      Gtk::MessageDialog dialog( * this, "DRAW", false, Gtk::MESSAGE_INFO);
      win = "NO WINNER!\n\nScore:  " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      player1.won = 2;
      player2.won = 2;
      game_end = TRUE;
      games++;
      dialog.set_secondary_text(win);
      dialog.run();
    }

    player_label();
  }

  game_over();
}

void ttt_window::change_button33() {
  if (ttt_board.check_if_space_open(2, 2) && !game_end && playerNamesSet) {
    if (player_1_turn == TRUE) {
      ttt_board.take_turn(player_1_turn, 2, 2);
      player1.turns++;
      button_33.set_image(x_image9);
      player_1_turn = FALSE;
      turns++;
    } else if (lowercase(player2.name) != "computer") {
      ttt_board.take_turn(player_1_turn, 2, 2);
      player2.turns++;
      button_33.set_image(o_image9);
      player_1_turn = TRUE;
      turns++;
    }
    if (lowercase(player2.name) == "computer" && turns < 9) {
      Move bestMove = findBestMove(ttt_board.board_array);
      ttt_board.board_array[bestMove.row][bestMove.col] = 'O';
      change_button();
      player_1_turn = TRUE;
      turns++;
    }
    if (ttt_board.calculate_win()) {
      games++;
      Gtk::MessageDialog dialog( * this, "WINNER", false, Gtk::MESSAGE_INFO);
      if (ttt_board.calculate_win() == 1) {
        player1.wins++;
        player1.won = 1;
        player2.loss++;
        player2.won = 0;
        win = player1.name + " YOU WON!\n\n" + "Score:  " + player1.name +
          ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
          to_string(player2.wins);
      } else {
        player1.loss++;
        player1.won = 0;
        player2.wins++;
        player2.won = 1;
        win = player2.name + " YOU WON!\n\n" + "Score:  " + player1.name +
          ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
          to_string(player2.wins);
      }
      change_buttons_win(ttt_board);
      dialog.set_secondary_text(win);
      dialog.run();
    }
    if (turns == 9 && ttt_board.calculate_win() == 0) {
      Gtk::MessageDialog dialog( * this, "DRAW", false, Gtk::MESSAGE_INFO);
      win = "NO WINNER!\n\nScore:  " + player1.name +
        ": " + to_string(player1.wins) + "\n\t\t" + player2.name + ": " +
        to_string(player2.wins);
      player1.won = 2;
      player2.won = 2;
      game_end = TRUE;
      games++;
      dialog.set_secondary_text(win);
      dialog.run();
    }

    player_label();
  }

  game_over();
}

void ttt_window::close_button() {
  hide();
  string stats;
  int pstats, p2stats;
  pstats = (((double) player1.wins / (double) games) * 100);
  p2stats = (((double) player2.wins / (double) games) * 100);
  Gtk::MessageDialog dialog( * this, "GAME STATS", false, Gtk::MESSAGE_INFO);
  stats = "SCORE:\t" + player1.name + ": " + to_string(player1.wins) + "\n\t\t\t" +
    player2.name + ": " + to_string(player2.wins) + "\n\n" + "WIN PCT:\t" +
    player1.name + ": " + to_string(pstats) + "%\n\t\t\t" + player2.name +
    ": " + to_string(p2stats) + "%";
  dialog.set_secondary_text(stats);
  dialog.run();
}
