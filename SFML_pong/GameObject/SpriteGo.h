#pragma once
#include "GameObject.h"
class SpriteGo : public GameObject
{
protected:
	sf::Vector2f spriteDir; // <- : -1 / -> : 1
public:
	sf::Sprite sprite;

	SpriteGo(const std::string n,
		sf::Vector2f spriteDir);
	virtual ~SpriteGo() override;

	virtual void SetPosition(const sf::Vector2f p);
	virtual void SetPosition(float x, float y);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);

	virtual void SetFlipX(bool flip);

	virtual void Init() override;	// 생성자 new 역할
	virtual void Release() override;	// 소멸자 delete 역할
	virtual void Reset() override;	// 값 세팅

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

};

