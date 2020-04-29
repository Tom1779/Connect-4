#include "game.h"
int main()
{
	string choice;
	//this will contain the menu where you can select the game
	RenderWindow window(sf::VideoMode(634, 600), "Rules");

	Font font;
	font.loadFromFile("coolvetica_rg.ttf");

	Text title("", font);
	title.setString("         Connect 4         ");
	title.setStyle(Text::Underlined);
	title.setCharacterSize(75);
	title.setFillColor(Color::White);

	Texture texture;
	if (!texture.loadFromFile("kids.png"))
	{
		cout << "Could not load kids.png" << endl;
	}
	texture.setSmooth(true);

	Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(0, 150);

	RectangleShape background(Vector2f(630, 500));
	background.setFillColor(Color::White);
	background.setPosition(0, 100);

	Text text("", font);
	text.setString("                         RULES\nBe the first player to get four pieces\nin a row. Four in a row can be \nhorizontal, vertical, or diagonal.\nPress left or right to move.\nPress spacebar to place chip.\n\n\n\n          Press spacebar to begin!\n");
	text.setCharacterSize(40);
	text.setPosition(5, 100);
	text.setOutlineColor(Color::Blue);
	text.setOutlineThickness(4.f);

	while (window.isOpen()) {

		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				//close window​
				window.close();
			}
		}
		window.draw(background);
		window.draw(sprite);
		window.draw(title);
		window.draw(text);
		window.display();
	}

	game* test = new connectGame();

	while(true) // keeps running the game until says he wants to stop
	{
		do
		{
			cout << "Do You Wish To Play Another Game (yes/no): ";
			getline(cin, choice);
			for_each(choice.begin(), choice.end(), [](char& c)
				{
					c = ::toupper(c);
				});
		} while (choice != "YES" && choice != "NO");
		if (choice == "NO")
		{
			break;
		}
		test = new connectGame();
	}
	return 0;
}