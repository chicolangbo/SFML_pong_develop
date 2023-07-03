#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "Utils.h"
class GameObject
{
protected:
	sf::Vector2f position;
	std::string name;
	bool isActive = true;			// Ȱ��ȭ: Update, Draw()
	Origins origin;

public:

	int sortLayer = 0;
	int sortOrder = 0;

	GameObject(const std::string n = "");
	virtual ~GameObject();

	bool GetActive() const;
	void SetActive(bool active);

	std::string GetName();
	virtual void SetName(const std::string& n);
	sf::Vector2f GetPosition();

	virtual void SetPosition(float x, float y);
	virtual void SetPosition(const sf::Vector2f p);

	virtual void SetOrigin(Origins origin);
	virtual void SetOrigin(float x, float y);

	virtual void Init() = 0;	// ������ new ����
	virtual void Release() {};	// �Ҹ��� delete ����

	virtual void Reset() = 0;	// �� ����

	virtual void Update(float dt) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;
};

