#include "stdafx.h"
#include "Bat.h"
#include "InputMgr.h"
#include "Utils.h"
#include <iostream>

void Bat::SetPos(const sf::Vector2f& p)
{
    position = p;
}

sf::Vector2f Bat::GetPos() const
{
    return position;
}

sf::FloatRect Bat::GetBounds() const
{
    return shape.getGlobalBounds();
}

void Bat::Init()
{
    shape.setSize({ 100.f, 5.f });
    Utils::SetOrigin(shape, Origins::TC); // �̷��� �ϸ� ������ = �� �������̸� �ºٰ� ��
    shape.setFillColor(sf::Color::White);
    SetPos({ 1280.f * 0.5f, 720.f - 25.f }); // �ϵ��ڵ� ��ġ�� ���߿�
    speed = 1000.f;
    direction = { 0.f, 0.f };
}

void Bat::Update(float dt)
{
    // Ű �Է� �ް� �����̱�
    direction.x = 0.f;
    if (INPUT_MGR.GetKey(sf::Keyboard::A))
    {
        
        direction.x += -1.f;
    }

    if (INPUT_MGR.GetKey(sf::Keyboard::D))
    {
        direction.x += 1.f;
    }

    position += direction * speed * dt;
    shape.setPosition(position);
}

void Bat::Draw(sf::RenderWindow& window)
{
    window.draw(shape);
}