#include "game.h"

game::game()
{

	//set gamestate to normal
	gameState = 0;

	//set usernames?

	//randomly set the first turn
	srand((unsigned)time(NULL));
	int i = rand() % 2 + 1;

	if (i == 1)
		playerturn = '1';
	else
		playerturn = '2';


	//gets the usernames of the players
	setUsernames();


	current_col = 0;
	current_row = 0;

}

game::~game()
{
	//D E S T R U C T O R
	//(lots of destruction)

	//can also display the winner here if you want
	//declareWinner();
}



void game::setUsernames()
{
	cout << "Enter name for Player 1: ";
	// cin >> username1;
	getline(cin, username1); // reads spaces
	cout << "Enter name for Player 2: ";
	//cin >> username2;
	getline(cin, username2);
}

void game::declareWinner()
{
	sf::Font font;
	font.loadFromFile("coolvetica_rg.ttf");

	sf::Text text("", font);
	switch (gameState)
	{
	case 0:
		cout << "Error, there is no winner\n";
		break;
	case 1:
		cout << "Player 1 wins!\n";
		text.setString(username1 +  "\n" + "Wins!");
		text.setOutlineColor(Color::Blue);
		text.setOutlineThickness(4.f);
		break;
	case 2:
		cout << "Player 2 wins!\n";
		text.setString(username2 + "\n " + "Wins!");
		text.setOutlineColor(Color::Blue);
		text.setOutlineThickness(4.f);
		break;
	case 3:
		cout << "It is a tie...\n";
		text.setString("Tie Game");
		text.setOutlineColor(Color::Blue);
		text.setOutlineThickness(4.f);
		break;

	}
	sf::RenderWindow window(sf::VideoMode(1024, 1024), "Winner");

	window.setFramerateLimit(12);

	text.setCharacterSize(150);
	text.setFillColor(sf::Color::Yellow);
	text.setPosition(175, 350);

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				//close window​
				window.close();
			}
		}

		Texture texture;
		if (!texture.loadFromFile("Trophy.png"))
		{
			cout << "Could not load Trophy.png" << endl;
		}

		Texture texture2;
		if (!texture2.loadFromFile("Confetti3.png"))
		{
			cout << "Could not load confetti3.png" << endl;
		}

		Sprite trophy;
		trophy.setTexture(texture);
		trophy.setPosition(250, 250);

		Sprite confetti;
		confetti.setTexture(texture2);
		confetti.setPosition(0, 0);

		window.display();
		window.draw(trophy);
		window.draw(text);
		window.draw(confetti);
		window.display();
		delay(3000);
		window.close();
	}
}

bool game::checkWinner(char player)
{
	//checks each directoin if there are a number in a row
	//returns true if there is a winnner, false if not

	//variable "player" can be changed to a color if we wish to catagorize that way
	if (testHorizontal(player) == true)
	{
		if (player == '1')
		{
			gameState = 1;
			//cout << "Congrats on the win player 1" << endl; // debug
		}
		else
		{
			gameState = 2;
			//cout << "Congrats on the win player 2" << endl; // debug
		}
		return true;

	}


	if (testVertical(player) == true)
	{
		if (player == '1')
		{
			gameState = 1;
			cout << "Congrats on the win player 1" << endl; // debug
		}
		else
		{
			gameState = 2;
			cout << "Congrats on the win player 2" << endl; // debug
		}
		return true;
	}


	if (testDiagonal(player) == true)
	{
		if (player == '1')
		{
			gameState = 1;
			cout << "Congrats on the win player 1" << endl; // debug
		}
		else
		{
			gameState = 2;
			cout << "Congrats on the win player 2" << endl; // debug
		}
		return true;
	}

	if (testTie() == true)
	{
		gameState = 3;
		return true;
	}

	return false;
}

int game::moveHorizontal()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		//change this delay function to set how fast the response rate for the movment is
		//delay(200);
		cout << "move right\n"; //for debugging
		return 1;

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		//change this delay function to set how fast the response rate for the movment is
		//delay(200);
		cout << "move left\n"; //for dubugging
		return -1;

	}

	return 0;
}

void game::delay(int milli_seconds)
{
	// Storing start time 
	clock_t start_time = clock();

	// looping till required time is not achieved 
	while (clock() < start_time + milli_seconds)
		;
}



connectGame::connectGame()
{
	display_board(); //debugging

	while (gameState == 0)
	{




		//play makes his turn
		turn(playerturn);

		display_board(); //debugging

		//check if they just won
		checkWinner(playerturn);

		//switch the player turn
		if (playerturn == '1')
			playerturn = '2';
		else
			playerturn = '1';



	}
	declareWinner();

}

//connectGame::~connectGame()
//{
//
//}

//code for a single turn of one player
void connectGame::turn(char player)
{
	//Create Font (display score)
	Font font;
	font.loadFromFile("coolvetica_rg.ttf");

	//Creates Texture
	Texture texture;
	texture.setSmooth(true);

	//create window
	RenderWindow window(VideoMode(1000, 1000), "Connect 4 C++");

	//set max fps
	window.setFramerateLimit(15);

	//psotion. can move form 0 to 6
	int position = 3;


	//create array of circle objects
	CircleShape circles[6][7];

	//set all the objects size, color, and position
	for (int row = 0; row < 6; row++)
	{
		for (int col = 0; col < 7; col++)
		{
			circles[row][col].setRadius(50.f);

			if (board[row][col] == NULL)
				circles[row][col].setFillColor(Color::White);
			else if (board[row][col] == '1')
				circles[row][col].setFillColor(Color::Red);
			else
				circles[row][col].setFillColor(Color::Yellow);

			circles[row][col].setPosition(115 + col * 110, 260 + row * 110);
		}
	}
	//Creates the board
	RectangleShape board(Vector2f(795, 675));
	board.setFillColor(Color(0, 0, 255));
	board.setPosition(100, 250);

	RectangleShape border(Vector2f(815, 695));
	border.setFillColor(Color::Blue);
	border.setPosition(90, 240);

	//Create arrow
	CircleShape arrow(25, 3);
	arrow.setFillColor(Color::White);
	arrow.setPosition(175, 175);
	arrow.rotate(60.f);

	Texture texture3;
	if (!texture3.loadFromFile("board.png"))
	{
		cout << "Could not load board.png" << endl;
	}
	texture.setSmooth(true);

	Sprite cover;
	cover.setTexture(texture3);
	cover.setPosition(100, 250);

	//Creates the title
	Text text("", font);
	text.setString("           Connect 4             ");
	text.setStyle(Text::Underlined);
	text.setCharacterSize(100);
	text.setFillColor(Color::White);

	//Creates text to show turn
	Text turn("", font);
	turn.setString("Player's Turn:  ");
	turn.setCharacterSize(50);
	turn.setPosition(0, 105);
	turn.setFillColor(Color::White);

	//Creates text to show username
//Creates text to show username
	Text person("", font);
	if (player == '1') {
		person.setString(username1);
		person.setFillColor(Color::Red);
		arrow.setFillColor(Color::Red);
		arrow.setOutlineColor(Color::White);
		arrow.setOutlineThickness(4.f);
	}
	else {
		person.setString(username2);
		person.setFillColor(Color::Yellow);
		arrow.setFillColor(Color::Yellow);
		arrow.setOutlineColor(Color::White);
		arrow.setOutlineThickness(4.f);
	}
	person.setCharacterSize(50);
	person.setPosition(280, 105);

	Text winner("", font);
	winner.setFillColor(Color::Black);
	winner.setCharacterSize(100);
	winner.setPosition(500, 500);

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				//close window
				window.draw(winner);
				window.display();
				delay(2000);
				window.close();

				//set the gamestate to a tie
				gameState = 3;
			}

		}


		//lets player move left and right
		position = position + moveHorizontal();

		//set the arrow to follow the position
		arrow.setPosition(178 + 110 * position, 180);

		//makes sure they stay in the boundries
		if (position < 0)
			position++;
		if (position > 6)
			position--;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			delay(10);
			//test if they chip can be placed here, and if it can, then place it
			if (placeChip(position, player))
			{
				//close the window so it is the next players turn
				window.close();
			}

			//else no chip is placed, and loop contiunes

			//can add graphics here to indicate failed placement 
		}


		//clear window and put it bakc onto the screen
		window.clear();
		window.draw(text);
		window.draw(turn);
		window.draw(person);
		window.draw(arrow);
		window.draw(border);
		window.draw(board);
		window.draw(cover);


		for (int row = 0; row < 6; row++)
		{
			for (int col = 0; col < 7; col++)
			{
				window.draw(circles[row][col]);
			}
		}
		window.display();
	}
}

bool connectGame::testHorizontal(char player)
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (i <= 3) // checking horizontal combination to the right
			{
				if ((board[j][i] == player) && (board[j][i + 1] == player) && (board[j][i + 2] == player) && (board[j][i + 3] == player))
				{
					return true;
				}
			}
			if (i >= 3) // checking horizontal combination to the left
			{
				if ((board[j][i] == player) && (board[j][i - 1] == player) && (board[j][i - 2] == player) && (board[j][i - 3] == player))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool connectGame::testVertical(char player)
{
	if (current_row >= 3) // checking vertical combination downwards
	{
		if ((board[current_row - 1][current_col] == player) && (board[current_row - 2][current_col] == player) && (board[current_row - 3][current_col] == player))
		{
			return true;
		}
	}
	if (current_row <= 2) // checking vertical combination upwards
	{
		if ((board[current_row + 1][current_col] == player) && (board[current_row + 2][current_col] == player) && (board[current_row + 3][current_col] == player))
		{
			return true;
		}
	}
	return false;
}

bool connectGame::testDiagonal(char player)
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (j <= 2 && i >= 3) // checking diagonal combination down left
			{
				if ((board[j][i] == player) && (board[j + 1][i - 1] == player) && (board[j + 2][i - 2] == player) && (board[j + 3][i - 3] == player))
				{
					return true;
				}

			}
			if (j <= 2 && i <= 3) // checking diagonal combination down right
			{
				if ((board[j][i] == player) && (board[j + 1][i + 1] == player) && (board[j + 2][i + 2] == player) && (board[j + 3][i + 3] == player))
				{
					return true;
				}
			}
			if (j >= 3 && i <= 3) // checking diagonal combination up right
			{
				if ((board[j][i] == player) && (board[j - 1][i + 1] == player) && (board[j - 2][i + 2] == player) && (board[j - 3][i + 3] == player))
				{
					return true;
				}
			}
			if (j >= 3 && i >= 3) // checking diagonal combination up left
			{
				if ((board[j][i] == player) && (board[j - 1][i - 1] == player) && (board[j - 2][i - 2] == player) && (board[j - 3][i - 3] == player))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool connectGame::testTie()
{
	int count = 0;
	for (int i = 0; i < 7; i++)
	{
		if (board[0][i] != '\0')
		{
			count++;
		}
	}
	if (count == 7)
	{
		return true;
	}
	return false;
}



//code to place a chip, aka set a spot on the board to a 1 or 2
//will return false if the placement was unsucessful
bool connectGame::placeChip(int column, char player)
{

	//traverse to the top of the column
	int i = 0;

	if (board[i][column] != '\0') // if i = 0 after the loop it means the column is full therefore disc cannot be places here, leaving function and returning false
	{
		cout << "Column is already filled, please choose a different place\n";
		return false;
	}

	while (board[i][column] == '\0') // updating current row "i" to the amount of rows that are empty in that column
	{
		if (i == 5) // if we are on the last row do not want to update i, so leaving loop before hitting i++
		{
			break;
		}
		if (board[i + 1][column] != '\0') // checking if the next row is empty or not, if it its not leaving the loop
		{
			break;
		}
		i++;
	}

	board[i][column] = player; // passed all checks placing the matching player sign in the lowest available row in given column
	current_row = i; // updating private member current row
	current_col = column; // updating private member current col
	return true; // returning true
}

void connectGame::display_board()
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			cout << board[i][j] << " - ";
		}
		cout << endl;
	}
}


/*

tictacGame::tictacGame()
{
}

bool tictacGame::testHorizontal(char num)
{
	return false;
}

bool tictacGame::testVertical(char num)
{
	return false;
}

bool tictacGame::testDiagonal(char num)
{
	return false;
}



gomokuGame::gomokuGame()
{
}

bool gomokuGame::testHorizontal()
{
	return false;
}

bool gomokuGame::testVertical()
{
	return false;
}

bool gomokuGame::testDiagonal()
{
	return false;
}


*/