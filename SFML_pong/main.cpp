//#include <SFML/Graphics.hpp>
//#include "InputMgr.h"
//#include "Bat.h"
//#include "Ball.h"
//#include "Utils.h"
//#include <iostream>
//#include <sstream>

// 수정후
#include "stdafx.h"
#include "Framework.h"

int main()
{
    //sf::RenderWindow window(sf::VideoMode(1280, 720), "Pong!");

    //Bat bat;
    //bat.Init();
    //Ball ball;
    //ball.Init();

    //sf::Font font;
    //font.loadFromFile("fonts/DS-DIGI.ttf"); // 리소스매니저

    //sf::Text hud;
    //hud.setFont(font);
    //hud.setCharacterSize(50);
    //hud.setFillColor(sf::Color::White);
    //hud.setPosition(20, 20);

    //bool ballActive = false;
    //int score = 0;
    //int life = 3;

    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);

    //sf::Clock clock;
    //while (window.isOpen())
    //{
    //    sf::Time deltaTime = clock.restart();
    //    float dt = deltaTime.asSeconds();
    //    INPUT_MGR.Clear(); // 입력버퍼 비워주기

    //    sf::Event event;
    //    while (window.pollEvent(event))
    //    {
    //        if (event.type == sf::Event::Closed)
    //            window.close();

    //        INPUT_MGR.Update(event);
    //    }

    //    if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space) && !ballActive)
    //    {
    //        ballActive = true;
    //        ball.Fire(Utils::Normalize({1.f,-1.f}), 1000.f);
    //    }
    //    else if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space) && ballActive)
    //    {
    //        ballActive = false;
    //        ball.Init();
    //    }

    //    bat.Update(dt);
    //    if (!ballActive) // 스페이스키를 누르면 bool 값이 바뀌게
    //    {
    //        ball.SetPos(bat.GetPos()); // bat를 따라다니게 한다
    //    }
    //    ball.Update(dt);

    //    // 충돌체크
    //    const sf::FloatRect& ballRect = ball.GetBounds();
    //    const sf::FloatRect& batRect = bat.GetBounds();
    //    if (ballRect.top < 0.f)
    //    {
    //        // 상
    //        ball.OnCollisionTop();
    //    }
    //    else if (ballRect.top + ballRect.height > 720.f)
    //    {
    //        // 하
    //        ball.OnCollisionBottom();
    //        --life;

    //        ballActive = false;
    //        ball.Init();
    //        if (life == 0)
    //        {
    //            bat.Init();
    //            score = 0;
    //            life = 3;
    //        }
    //    }
    //    else if (ballRect.left < 0.f)
    //    {
    //        // 좌
    //        ball.OnCollisionLeft();
    //    }
    //    else if (ballRect.left + ballRect.width > 1280.f)
    //    {
    //        // 우
    //        ball.OnCollisionRight();
    //    }

    //    if (ballRect.intersects(batRect))
    //    {
    //        ball.OnCollisionBottom();
    //        ++score;
    //    }

    //    std::stringstream ss;
    //    ss << "Score: " << score << "\tLife: " << life;
    //    hud.setString(ss.str());

    //    window.clear();
    //    bat.Draw(window);
    //    ball.Draw(window);
    //    window.draw(hud);
    //    window.display();
    //}

    // 수정 후
    FRAMEWORK.Run();

    return 0;
}