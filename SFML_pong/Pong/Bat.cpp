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

sf::RectangleShape& Bat::GetInstance()
{
    return shape;
}

void Bat::Init()
{
    shape.setSize({ 100.f, 500.f });
    Utils::SetOrigin(shape, Origins::TC); // 이렇게 하면 포지션 = 공 포지션이면 맞붙게 됨
    shape.setFillColor(sf::Color::White);
    SetPos({ 1280.f * 0.5f, 720.f - 25.f }); // 하드코딩 고치기 나중에
    speed = 500.f;
    direction = { 0.f, 0.f };
}

void Bat::Update(float dt)
{
    // 키 입력 받고 움직이기
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
