#pragma once
#include <SFML/Graphics.hpp>

class Bat
{
protected:
	float speed = 1000.f; // �ӷ�
	sf::Vector2f direction; // ����

	sf::Vector2f position; // ������(���Ͷ� �����ϱ�)
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

