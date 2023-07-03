#pragma once
#include "Scene.h"
#include "Ball.h"
#include "Bat.h"

class ScenePong :
    public Scene
{
protected:
    Ball ball;
    Bat bat;
    sf::Text hud;
    bool ballActive;
    int score;
    int life;
    sf::Font font;
    bool batOnce;

public:
    ScenePong();
    virtual ~ScenePong() override = default;

    virtual void Init() override;
    virtual void Release() override;

    virtual void Enter() override;
    virtual void Exit() override;

    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;
};

