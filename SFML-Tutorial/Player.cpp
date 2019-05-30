#include "Player.h"
#include <iostream>



Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
	animation(texture, imageCount, switchTime), canJump{true}
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	this->canJump = true;
	this->acceleration = sqrtf(2 * 981 * jumpHeight)/100;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(40, 80));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(300, 200);
	body.setTexture(texture);
}


Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	velocity.x = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= speed;
	} 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
	{
		canJump = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		body.setPosition(sf::Vector2f(300, 200));
	}

	if (!canJump)
	{
		acceleration -= 2*981*deltaTime/700;
		velocity.y -= acceleration;
	}
	else
	{
		velocity.y += 2 * 981 * deltaTime;
	}

	if (velocity.x == 0)
	{
		row = 0;
	}
	else
	{
		row = 1;

		if (velocity.x > 0)
		{
			faceRight = true;
		}
		else
		{
			faceRight = false;
		}
	}

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	velocity.y /= 2;
	body.move(velocity);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0)
	{
		velocity.x = 0;
	}
	else if (direction.x > 0)
	{
		velocity.x = 0;
	}
	if (direction.y < 0)
	{
		velocity.y = 0;
		canJump = true;
		acceleration = sqrtf(2 * 981 * jumpHeight) / 10;
	}
	else if (direction.y > 0)
	{
		velocity.y = 0;
	}
}
