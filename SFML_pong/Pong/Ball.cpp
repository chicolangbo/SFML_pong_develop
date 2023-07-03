#include "stdafx.h"
#include "Ball.h"
#include "Utils.h"

Ball::Ball()
{
}

void Ball::SetPos(const sf::Vector2f& p)
{
	position = p;
	shape.setPosition(position);
}

sf::Vector2f Ball::GetPos() const
{
	return position;
}

sf::FloatRect Ball::GetBounds() const
{
    return shape.getGlobalBounds();
}

float Ball::GetRadius() const
{
    return shape.getRadius();
}

void Ball::Init()
{
    shape.setRadius(10.f);
    Utils::SetOrigin(shape, Origins::BC); // 이렇게 하면 포지션 = 공 포지션이면 맞붙게 됨
    shape.setFillColor(sf::Color::White);
    SetPos({ 1280.f * 0.5f, 720.f - 25.f }); // 하드코딩 고치기 나중에
    speed = 0.f; // 처음에 안 움직여야 하니까
    direction = { 0.f, 0.f };
}

void Ball::Fire(sf::Vector2f dir, float s)
{
    direction = dir;
    speed = s;
}

void Ball::Update(float dt)
{
    SetPos(position + direction * speed * dt);

    /* 위와 같음
    position += direction * speed * dt;
    shape.setPosition(position);
    */
}

void Ball::Draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

void Ball::OnCollisionTop()
{
    direction.y = abs(direction.y);
}

void Ball::OnCollisionBottom()
{
    direction.y = -abs(direction.y);
}

void Ball::OnCollisionLeft()
{
    direction.x = abs(direction.x);
}

void Ball::OnCollisionRight()
{
    direction.x = -abs(direction.x);
}

void Ball::OnCollisionLT()
{
    direction = { -1.f, 1.f };
}

void Ball::OnCollisionRT()
{
    direction = { 1.f, 1.f };
}

void Ball::OnCollisionLB()
{
    direction = { -1.f, -1.f };
}

void Ball::OnCollisionRB()
{
    direction = { 1.f, -1.f };
}
