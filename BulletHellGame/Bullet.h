#pragma once
#include "Entity.h"
#include "Player.h"

class Bullet final : public Entity
{
public:
    Bullet(aie::Renderer2D*& _renderer, aie::Application& _application, Player*& _player) : Entity(_renderer, _application)
    {
        m_player = _player;
        
        Start();
    }
    
    void Start() override;
    void Update(float _deltaTime) override;
    void Draw() override;

    Vector2 velocity = Vector2();

private:
    Player* m_player;
    float m_speed = 1;
};
