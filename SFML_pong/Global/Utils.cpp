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
    // ���̰� radius�� ����
    //float x = RandomRange(0.f, radius);
    //float y = RandomRange(0.f, radius);

    //while (Magnitude({ x,y }) != radius)
    //{
    //    x = RandomRange(0.f, radius);
    //    y = RandomRange(0.f, radius);
    //}

    // ������ �ڵ�
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

    // ������ �ڵ�

    return RandomOnCircle(1.f) * RandomRange(0.f,radius); // radius �ְ�, 0.1, 1.f ���� �Ŷ� ����
    // return RandomOnCircle(radius)* RandomValue(); ����
}

float Utils::RandomValue()
{
    return RandomRange(0.0f, 1.0f); // �� ���� �³�?
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

// Text �� Sprite�� ���ڸ� �Ѱܹ޾� �ǹ��� �缳��
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

float Utils::Magnitude(const sf::Vector2f& vec) // ���� ����?
{
    return sqrt(vec.x * vec.x + vec.y * vec.y); // sqrt = ��Ʈ�� ����. ���� ���� ���̸� ���ϴ� ��
}

sf::Vector2f Utils::Normalize(const sf::Vector2f& vec) // Ư�� ���� ���� ������ ���ν�Ű�� �� = ����ȭ / ������ �˰� ���� ��
{
    float mag = Magnitude(vec);
    if (mag == 0.f)
    {
        return vec;
    }
    return vec / mag; // ���� ���̷� ������ ������ ���̰� 1�� ������
}

float Utils::Distance(const sf::Vector2f& a, const sf::Vector2f& b)
{
    // (a - b) �����ϰ� ��Ʈ ����� ���� �ʳ�

    return  Magnitude(a - b);
}
