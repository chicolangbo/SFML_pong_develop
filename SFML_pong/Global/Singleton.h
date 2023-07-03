#pragma once

template <typename T>
class Singleton
{
public:
    static T& Instance()
    {
        static T instance;
        return instance;
    }

    // �Ű������� �ѱ涧 ����°� ����
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

protected:
    Singleton() = default;
    virtual ~Singleton() = default;
};