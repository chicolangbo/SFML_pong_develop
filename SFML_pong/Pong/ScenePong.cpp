#include "stdafx.h"
#include "ScenePong.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "SpriteGo.h"
#include "Framework.h"
#include "TextGo.h"
#include "Utils.h"
#include <sstream>

ScenePong::ScenePong()
	: Scene(SceneId::Game),
	ballActive(false), score(0), life(3), batOnce(false)
{
    // ������
    //resources.push_back(std::make_tuple(ResourceTypes::Font, "fonts/DS-DIGI.ttf"));

    font.loadFromFile("fonts/DS-DIGI.ttf"); // ���ҽ��Ŵ���
}

void ScenePong::Init()
{
	Release();

    // ������
    //AddGo(new TextGo("Title", "fonts/DS-DIGI.ttf"));

	ball.Init();
	bat.Init();

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void ScenePong::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void ScenePong::Enter()
{
	Scene::Enter();
    ball.Init();
    bat.Init();
    hud.setFont(font);
    hud.setCharacterSize(50);
    hud.setFillColor(sf::Color::White);
    hud.setPosition(20, 20);

}

void ScenePong::Exit()
{
	Scene::Exit();
}

void ScenePong::Update(float dt)
{
	Scene::Update(dt);

    if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space) && !ballActive)
    {
        ballActive = true;
        ball.Fire(Utils::Normalize({1.f,-1.f}), 1000.f);
    }
    else if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space) && ballActive)
    {
        ballActive = false;
        ball.Init();
    }

    bat.Update(dt);
    if (!ballActive) // �����̽�Ű�� ������ bool ���� �ٲ��
    {
        ball.SetPos(bat.GetPos()); // bat�� ����ٴϰ� �Ѵ�
    }
    ball.Update(dt);


    /////////////////////////// �浹üũ ///////////////////////////
    // 
    // �� �浹
    CheckWallCollide();

    // bat �浹
    if (CheckCRCollide(bat.GetInstance()) == Collide::Top)
    {
        std::cout << "�浹" << std::endl;
        if (!batOnce && ballActive)
        {
            ++score;
        }
        batOnce = true;
    }
    else
    {
        std::cout << "�浹����" << std::endl;
        batOnce = false;
    }

    //if(CheckCRCollide(block��ü))
    //{
    //  ++score;

    std::stringstream ss;
    ss << "Score: " << score << "\tLife: " << life;
    hud.setString(ss.str());

}

void ScenePong::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
    window.clear();
    bat.Draw(window);
    ball.Draw(window);
    window.draw(hud);
}

Collide ScenePong::CheckCRCollide(sf::RectangleShape& rec)
{
    // �� �ٿ��, ���(or��Ʈ) �ٿ��
    sf::FloatRect ballBound = ball.GetBounds();
    sf::FloatRect recBound = rec.getGlobalBounds();
    
    // �� ������ǥ, ���(or��Ʈ) ������ ��ǥ
    sf::Vector2f ballCenterPos = ball.GetPos() + sf::Vector2f(0.f, -10.f);
    sf::Vector2f recLTPos = { recBound.left, recBound.top };
    sf::Vector2f recLBPos = { recBound.left, recBound.top + recBound.height };
    sf::Vector2f recRTPos = { recBound.left + recBound.width, recBound.top };
    sf::Vector2f recRBPos = { recBound.left + recBound.width, recBound.top + recBound.height };

    // ���� ���(or��Ʈ) �������� ��(���� ����� ��)
    sf::Vector2f closePos;
    closePos.x = (ballCenterPos.x <= recBound.left) ? recBound.left :
        (ballCenterPos.x >= recRTPos.x) ? recRTPos.x : ballCenterPos.x;
    closePos.y = (ballCenterPos.y <= recBound.top) ? recBound.top :
        (ballCenterPos.y >= recRBPos.y) ? recRBPos.y : ballCenterPos.y;

    // ���� ����� ���� ����ǥ�� ��
    float subX = closePos.x - ballCenterPos.x;
    float subY = closePos.y - ballCenterPos.y;

    // �浹üũ �Լ�
    if (Utils::SqrMagnitude({ subX,subY }) <= ball.GetRadius() * ball.GetRadius())
    {
        if (ballCenterPos.x >= recBound.left && ballCenterPos.x <= recRTPos.x) // �� or �Ʒ� �浹
        {
            if (ballCenterPos.y < recBound.top) // ��
            {
                ball.OnCollisionBottom();
                return Collide::Top;
            }
            else // �� : else if(ballCenterPos.y > recRBPos.y)
            {
                ball.OnCollisionTop();
                return Collide::Other;
            }
        }
        else if (ballCenterPos.y >= recBound.top && ballCenterPos.y <= recRBPos.y) // �� �浹
        {
            if (ballCenterPos.x < recBound.left) // ��
            {
                ball.OnCollisionRight();
                return Collide::Other;
            }
            else // �� : else if(ballCenterPos.x > recRTPos.x)
            {
                ball.OnCollisionLeft();
                return Collide::Other;
            }
        }
        else // �𼭸� �浹
        {
            if (ballCenterPos.x < recBound.left && ballCenterPos.y < recBound.top) // �»�
            {
                ball.OnCollisionLT();
                return Collide::Other;
            }
            else if (ballCenterPos.x < recBound.left && ballCenterPos.y > recRBPos.y) // ����
            {
                ball.OnCollisionLB();
                return Collide::Other;
            }
            else if (ballCenterPos.x > recRTPos.x && ballCenterPos.y < recBound.top) // ���
            {
                ball.OnCollisionRT();
                return Collide::Other;
            }
            else if (ballCenterPos.x > recRTPos.x && ballCenterPos.y > recBound.top) // ����
            {
                ball.OnCollisionRB();
                return Collide::Other;
            }
        }
    }
    else
    {
        return Collide::None;
    }
}

void ScenePong::CheckWallCollide()
{
    // �� �浹
    const sf::FloatRect& ballRect = ball.GetBounds();

    if (ballRect.top < 0.f)
    {
        // ��
        ball.OnCollisionTop();
    }
    else if (ballRect.top + ballRect.height > FRAMEWORK.GetWindowSize().y)
    {
        // ��
        ball.OnCollisionBottom();
        --life;

        ballActive = false;
        ball.Init();
        if (life == 0)
        {
            bat.Init();
            score = 0;
            life = 3;
        }
    }
    else if (ballRect.left < 0.f)
    {
        // ��
        ball.OnCollisionLeft();
    }
    else if (ballRect.left + ballRect.width > FRAMEWORK.GetWindowSize().x)
    {
        // ��
        ball.OnCollisionRight();
    }
}
