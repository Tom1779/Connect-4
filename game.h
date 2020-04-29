#include <iostream>
#include <time.h>
#include <SFML\Graphics.hpp>

#include "NetworkConnection.h"

using namespace std;
using namespace sf;

class game
{
protected:

	//gamestate, 0 is normal, 1 is p1 win, 2 is p2 win, 3 is tie
	int gameState;

	//keeps track of who's turn it currently is
	char playerturn;

	//name of p1
	string username1;

	//name of p2
	string username2;


	int current_col;
	int current_row;;



public:
	//constructor
	game();
	~game();
	//destructor
	//virtual ~game();

	//sets usernames
	void setUsernames();

	//says who won the game
	void declareWinner();

	//checks if someone won
	bool checkWinner(char);

	//testing for in a row, returns 1 if found, 0 if not
	bool virtual testHorizontal(char) = 0;
	bool virtual testVertical(char) = 0;
	bool virtual testDiagonal(char) = 0;
	bool virtual testTie() = 0;

	//controls
	int moveHorizontal();

	//delay function
	void delay(int milli_seconds);

};


class connectGame :public game
{
private:
	char board[6][7] = {};


public:
	connectGame();

	void turn(char player);


	bool testHorizontal(char player);
	bool testVertical(char player);
	bool testDiagonal(char player);
	bool testTie();



	bool placeChip(int column, char player);

	//for debugging
	void display_board();




};

/*
class tictacGame :public game
{
private:
	char board[3][3] = {};

public:
	tictacGame();



	bool testHorizontal(char num);
	bool testVertical(char num);
	bool testDiagonal(char num);

};


class gomokuGame : public game
{
private:
	char board[15][15] = {};

public:
	gomokuGame();


	bool testHorizontal();
	bool testVertical();
	bool testDiagonal();

};

*/
