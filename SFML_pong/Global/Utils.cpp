#include "stdafx.h"
#include "Utils.h"

std::random_device Utils::rd;
std::mt19937 Utils::gen(Utils::rd());


int Utils::RandomRange(int min, int maxExclude)
{
    std::uniform_int_distribution<> dist(min, maxExclude -1);
    return dist(gen);
    //return gen() % (maxExclude - min) + min;
}

float Utils::RandomRange(float min, float max)
{
    std::uniform_real_distribution<> dist(min, max);
    return (float)dist(gen);
}

sf::Vector2f Utils::RandomOnCircle(float radius)
{
    // 길이가 radius와 동일
    //float x = RandomRange(0.f, radius);
    //float y = RandomRange(0.f, radius);

    //while (Magnitude({ x,y }) != radius)
    //{
    //    x = RandomRange(0.f, radius);
    //    y = RandomRange(0.f, radius);
    //}

    // 선생님 코드
    sf::Vector2f vec(RandomRange(-1.0f, 1.0f), RandomRange(-1.0f, 1.0f));
    vec = Normalize(vec) * radius;

    return vec;
}

sf::Vector2f Utils::RandomInCircle(float radius)
{
    //float x = RandomRange(0.f, radius);
    //float y = RandomRange(0.f, radius);

    //while (RandomOnCircle(radius).x >= x && RandomOnCircle(radius).y >= y)
    //{
    //    x = RandomRange(0.f, radius);
    //    y = RandomRange(0.f, radius);
    //}
    // return {x,y};

    // 선생님 코드

    return RandomOnCircle(1.f) * RandomRange(0.f,radius); // radius 넣고, 0.1, 1.f 넣은 거랑 동일
    // return RandomOnCircle(radius)* RandomValue(); 동일
}

float Utils::RandomValue()
{
    return RandomRange(0.0f, 1.0f); // 이 말이 맞나?
}

void Utils::SetOrigin(sf::Sprite& sprite, Origins origin)
{
    SetOrigin(sprite, origin, sprite.getLocalBounds());
}

void Utils::SetOrigin(sf::Text& text, Origins origin)
{
    SetOrigin(text, origin, text.getLocalBounds());
}

void Utils::SetOrigin(sf::Shape& shape, Origins origin)
{
    SetOrigin(shape, origin, shape.getLocalBounds());
}

// Text 나 Sprite의 인자를 넘겨받아 피벗을 재설정
void Utils::SetOrigin(sf::Transformable& obj, Origins origin, const sf::FloatRect& rect)
{
    sf::Vector2f originPos(rect.width, rect.height);
    originPos.x *= ((int)origin % 3) * 0.5f;
    originPos.y *= ((int)origin / 3) * 0.5f;
    obj.setOrigin(originPos);
}

float Utils::SqrMagnitude(const sf::Vector2f& vec)
{

    return vec.x * vec.x + vec.y * vec.y;
}

float Utils::Magnitude(const sf::Vector2f& vec) // 빗변 길이?
{
    return sqrt(vec.x * vec.x + vec.y * vec.y); // sqrt = 루트의 역할. 지금 빗변 길이를 구하는 거
}

sf::Vector2f Utils::Normalize(const sf::Vector2f& vec) // 특정 값을 일정 범위에 맵핑시키는 것 = 정규화 / 방향을 알고 싶을 때
{
    float mag = Magnitude(vec);
    if (mag == 0.f)
    {
        return vec;
    }
    return vec / mag; // 빗변 길이로 나누면 벡터의 길이가 1로 고정됨
}

float Utils::Distance(const sf::Vector2f& a, const sf::Vector2f& b)
{
    // (a - b) 제곱하고 루트 씌우면 되지 않나

    return  Magnitude(a - b);
}
