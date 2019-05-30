#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Platform.h"
#include <ctime>

static const float VIEW_HEIGHT = 512;

void ResizeView(sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

void setTextPosition(sf::Text& text, sf::Vector2f position)
{
	position.x -= 150;
	position.y -= 100;
	text.setPosition(position);
}

int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(512, 512), "SFML", sf::Style::Default);
	sf::View view(sf::Vector2f(0, 0), sf::Vector2f(512, 512));
	sf::Texture playerTexture;
	playerTexture.loadFromFile("tux_from_linux.png");

	sf::Font font;
	font.loadFromFile("arial.ttf");
	sf::Text text("Press R to restart", font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::Red);

	sf::Text win("You won", font);
	win.setCharacterSize(30);
	win.setStyle(sf::Text::Bold);
	win.setFillColor(sf::Color::Green);

	Player player(&playerTexture, sf::Vector2u(3, 9), 0.1f, 0.2f, 0.01f);

	std::vector<Platform> platforms;

	platforms.push_back(Platform(nullptr, sf::Vector2f(300, 10), sf::Vector2f(200, 300)));

	for (int i = 0; i < 20; i++)
	{
		float x = platforms[i].GetPosition().x;
		float y = platforms[i].GetPosition().y;
		float rndX = rand() % 100 + x + 200;
		float rndY = -rand() % 30 + y - 30;

		sf::Vector2f position(rndX, rndY);
		platforms.push_back(Platform(nullptr, sf::Vector2f(200, 10), position));
	}
	setTextPosition(win, platforms[20].GetPosition());

	float deltaTime = 0;
	sf::Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		
		if (deltaTime > 0.02)
		{
			deltaTime = 0.02f;
		}

		sf::Event e;
		while (window.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				ResizeView(window, view);
				break;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}
		}

		player.Update(deltaTime);
		setTextPosition(text, player.GetPosition());

		sf::Vector2f direction;

		for (Platform& platform : platforms)
		{
			if (platform.GetCollider().CheckCollision(player.GetCollider(), direction, 1))
			{
				player.OnCollision(direction);
			}
		}

		view.setCenter(player.GetPosition());

		window.clear(sf::Color(150, 150, 150));
		window.setView(view);
		player.Draw(window);
		for (Platform& platform : platforms)
		{
			platform.Draw(window);
		}
		if (player.GetPosition().y > 1500)
		{
			window.draw(text);
		}
		window.draw(win);
		window.display();
	}

	return 0;
}