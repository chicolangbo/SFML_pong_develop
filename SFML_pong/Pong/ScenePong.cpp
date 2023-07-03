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
    // 디버깅용
    //resources.push_back(std::make_tuple(ResourceTypes::Font, "fonts/DS-DIGI.ttf"));

    font.loadFromFile("fonts/DS-DIGI.ttf"); // 리소스매니저
}

void ScenePong::Init()
{
	Release();

    // 디버깅용
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
    if (!ballActive) // 스페이스키를 누르면 bool 값이 바뀌게
    {
        ball.SetPos(bat.GetPos()); // bat를 따라다니게 한다
    }
    ball.Update(dt);


    /////////////////////////// 충돌체크 ///////////////////////////
    // 
    // 벽 충돌
    CheckWallCollide();

    // bat 충돌
    if (CheckCRCollide(bat.GetInstance()) == Collide::Top)
    {
        std::cout << "충돌" << std::endl;
        if (!batOnce && ballActive)
        {
            ++score;
        }
        batOnce = true;
    }
    else
    {
        std::cout << "충돌해제" << std::endl;
        batOnce = false;
    }

    //if(CheckCRCollide(block객체))
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
    // 볼 바운드, 블록(or배트) 바운드
    sf::FloatRect ballBound = ball.GetBounds();
    sf::FloatRect recBound = rec.getGlobalBounds();
    
    // 볼 센터좌표, 블록(or배트) 꼭지점 좌표
    sf::Vector2f ballCenterPos = ball.GetPos() + sf::Vector2f(0.f, -10.f);
    sf::Vector2f recLTPos = { recBound.left, recBound.top };
    sf::Vector2f recLBPos = { recBound.left, recBound.top + recBound.height };
    sf::Vector2f recRTPos = { recBound.left + recBound.width, recBound.top };
    sf::Vector2f recRBPos = { recBound.left + recBound.width, recBound.top + recBound.height };

    // 볼과 블록(or배트) 수직선상 점(가장 가까운 점)
    sf::Vector2f closePos;
    closePos.x = (ballCenterPos.x <= recBound.left) ? recBound.left :
        (ballCenterPos.x >= recRTPos.x) ? recRTPos.x : ballCenterPos.x;
    closePos.y = (ballCenterPos.y <= recBound.top) ? recBound.top :
        (ballCenterPos.y >= recRBPos.y) ? recRBPos.y : ballCenterPos.y;

    // 가장 가까운 점과 볼좌표의 차
    float subX = closePos.x - ballCenterPos.x;
    float subY = closePos.y - ballCenterPos.y;

    // 충돌체크 함수
    if (Utils::SqrMagnitude({ subX,subY }) <= ball.GetRadius() * ball.GetRadius())
    {
        if (ballCenterPos.x >= recBound.left && ballCenterPos.x <= recRTPos.x) // 위 or 아래 충돌
        {
            if (ballCenterPos.y < recBound.top) // 상
            {
                ball.OnCollisionBottom();
                return Collide::Top;
            }
            else // 하 : else if(ballCenterPos.y > recRBPos.y)
            {
                ball.OnCollisionTop();
                return Collide::Other;
            }
        }
        else if (ballCenterPos.y >= recBound.top && ballCenterPos.y <= recRBPos.y) // 옆 충돌
        {
            if (ballCenterPos.x < recBound.left) // 좌
            {
                ball.OnCollisionRight();
                return Collide::Other;
            }
            else // 우 : else if(ballCenterPos.x > recRTPos.x)
            {
                ball.OnCollisionLeft();
                return Collide::Other;
            }
        }
        else // 모서리 충돌
        {
            if (ballCenterPos.x < recBound.left && ballCenterPos.y < recBound.top) // 좌상
            {
                ball.OnCollisionLT();
                return Collide::Other;
            }
            else if (ballCenterPos.x < recBound.left && ballCenterPos.y > recRBPos.y) // 좌하
            {
                ball.OnCollisionLB();
                return Collide::Other;
            }
            else if (ballCenterPos.x > recRTPos.x && ballCenterPos.y < recBound.top) // 우상
            {
                ball.OnCollisionRT();
                return Collide::Other;
            }
            else if (ballCenterPos.x > recRTPos.x && ballCenterPos.y > recBound.top) // 우하
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
    // 벽 충돌
    const sf::FloatRect& ballRect = ball.GetBounds();

    if (ballRect.top < 0.f)
    {
        // 상
        ball.OnCollisionTop();
    }
    else if (ballRect.top + ballRect.height > FRAMEWORK.GetWindowSize().y)
    {
        // 하
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
        // 좌
        ball.OnCollisionLeft();
    }
    else if (ballRect.left + ballRect.width > FRAMEWORK.GetWindowSize().x)
    {
        // 우
        ball.OnCollisionRight();
    }
}
