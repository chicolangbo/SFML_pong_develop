#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
protected:
	sf::Vector2f position;

	float speed;
	sf::Vector2f direction;

public:
	sf::CircleShape shape;

	Ball();
	~Ball() = default;
	
	void SetPos(const sf::Vector2f& p);
	sf::Vector2f GetPos() const;

	sf::FloatRect GetBounds() const;

	void Init();
	void Fire(sf::Vector2f dir, float s);

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	void OnCollisionTop();
	void OnCollisionBottom();
	void OnCollisionLeft();
	void OnCollisionRight();
};

