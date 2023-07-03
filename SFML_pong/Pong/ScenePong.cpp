#include "stdafx.h"
#include "ScenePong.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "SpriteGo.h"
#include "Framework.h"
#include "TextGo.h"
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

    // 충돌체크
    const sf::FloatRect& ballRect = ball.GetBounds();
    const sf::FloatRect& batRect = bat.GetBounds();
    sf::FloatRect tempRect;
    if (ballRect.top < 0.f)
    {
        // 상
        ball.OnCollisionTop();
    }
    else if (ballRect.top + ballRect.height > 720.f)
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
    else if (ballRect.left + ballRect.width > 1280.f)
    {
        // 우
        ball.OnCollisionRight();
    }

    if (!batOnce)
    {
        if (ballRect.intersects(batRect, tempRect))
        {
            if (Utils::Distance(ball.GetPos(), { bat.GetPos().x + batRect.width / 2.f, batRect.top }) == ball.shape.getRadius()
                && (tempRect.height == tempRect.width))
            {
                std::cout << "모서리 충돌" << std::endl;
            }

            std::cout << "충돌" << std::endl;
            ball.OnCollisionBottom();
            ++score;
            batOnce = true;
        }
    }
    else
    {
        if (!ballRect.intersects(batRect))
        {
            std::cout << "충돌해제" << std::endl;
            batOnce = false;
        }
    }

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
