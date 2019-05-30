#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"

class Platform
{
private:
	sf::RectangleShape body;

public:
	Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~Platform();

	void Draw(sf::RenderWindow& window);
	Collider GetCollider() { return Collider(body); }
	sf::Vector2f GetPosition() { return body.getPosition(); }
};

