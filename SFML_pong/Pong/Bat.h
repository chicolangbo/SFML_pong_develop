#pragma once
#include <SFML/Graphics.hpp>

class Bat
{
protected:
	float speed = 1000.f; // ¼Ó·Â
	sf::Vector2f direction; // º¤ÅÍ

	sf::Vector2f position; // Æ÷Áö¼Ç(º¤ÅÍ¶û ±¸ºÐÇÏ±â)
	sf::RectangleShape shape;

public:
	Bat() = default;
	~Bat() = default;

	void SetPos(const sf::Vector2f& p);
	sf::Vector2f GetPos() const;

	sf::FloatRect GetBounds() const;
	sf::RectangleShape& GetInstance();

	void Init();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);
};

