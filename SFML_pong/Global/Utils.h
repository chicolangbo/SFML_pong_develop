#pragma once
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include "Defines.h"


class Utils
{
private:
	static std::random_device rd;
	static std::mt19937 gen;

public:
	static int RandomRange(int min, int maxExclude);
	static float RandomRange(float min, float max);
	static sf::Vector2f RandomOnCircle(float radius); // radius : 반경
	static sf::Vector2f RandomInCircle(float radius);
	static float RandomValue(); // 0.0f~1.0f

	static void SetOrigin(sf::Sprite& sprite, Origins origin);
	static void SetOrigin(sf::Text& text, Origins origin);
	static void SetOrigin(sf::Shape& shape, Origins origin);
	static void SetOrigin(sf::Transformable& obj, Origins origin, const sf::FloatRect& rect);

	// 벡터
	static float SqrMagnitude(const sf::Vector2f& vec);
	static float Magnitude(const sf::Vector2f& vec);
	//정규화
	static sf::Vector2f Normalize(const sf::Vector2f& vec);
	static float Distance(const sf::Vector2f& a, const sf::Vector2f& b); // 두개 포지션 사이의 거리
};