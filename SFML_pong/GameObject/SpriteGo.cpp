#include "stdafx.h"
#include "SpriteGo.h"
//#include "Utils.h"

SpriteGo::SpriteGo(const std::string n, sf::Vector2f spriteDir)
	: GameObject(n), spriteDir(spriteDir)
{
}

SpriteGo::~SpriteGo()
{
}

void SpriteGo::SetPosition(const sf::Vector2f p)
{
	position = p;
	sprite.setPosition(p);

}

void SpriteGo::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	sprite.setPosition(position);
}

void SpriteGo::SetOrigin(Origins origin)
{
	GameObject::SetOrigin(origin);
	if (this->origin != Origins::CUSTOM)
	{
		Utils::SetOrigin(sprite, origin);
	}
}

void SpriteGo::SetOrigin(float x, float y)
{
	GameObject::SetOrigin(x,y);
	sprite.setOrigin(x, y);
}

void SpriteGo::SetFlipX(bool flip)
{
	sf::Vector2f scale = sprite.getScale();
	scale.x = flip ? -abs(scale.x) : abs(scale.x);
	if (spriteDir.x < 0.f)
	{
		scale.x *= -1.f;
	}
	sprite.setScale(scale);
}

void SpriteGo::Init()
{
}

void SpriteGo::Release()
{
}

void SpriteGo::Reset()
{

}

void SpriteGo::Update(float dt)
{

}

void SpriteGo::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
