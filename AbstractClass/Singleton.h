#pragma once

template <typename Derived>
class Singleton
{
protected:
    static Derived* Instance;
    Singleton();

public:
    ~Singleton();

    // 이동 & 복사 생성자 제거
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

    static Derived& GetInstance();
};


template <typename Derived>
Singleton<Derived>::~Singleton()
{
    delete Instance;
}

template <typename Derived>
Derived& Singleton<Derived>::GetInstance()
{
    if (Instance == nullptr)
    {
        Instance = new Derived();
    }
    return *Instance;
}

template <typename Derived>
Derived* Singleton<Derived>::Instance = nullptr;
