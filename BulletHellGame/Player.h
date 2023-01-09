#pragma once
#include "Bullet.h"
#include "IEntity.h"
#include "Font.h"

class Player final : public IEntity
{
public:
    Player(aie::Renderer2D*& _renderer, aie::Application& _application) : IEntity(_renderer, _application)
    {
        Start();
    }

    ~Player() override
    {
        for (const auto bullet : bullets)
            delete bullet;
        
        delete m_font;
    }
    
    void Start() override;
    void Update(float _deltaTime) override;
    void Draw() override;
    
    void SpawnBullet(Vector2 _pos, Vector2 _velocity);

    int lives = 3;
    std::vector<Bullet*> bullets;

private:
    float m_speed = 3;
    
    Vector2 m_dirToMouse;
    float m_turretLength = 1;
    Vector2 m_turretEnd;
    
    aie::Font* m_font;
};
