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

	virtual void Init() override;	// ������ new ����
	virtual void Release() override;	// �Ҹ��� delete ����
	virtual void Reset() override;	// �� ����

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

};

