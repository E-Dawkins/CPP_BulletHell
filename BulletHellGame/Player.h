#pragma once
#include "Entity.h"
#include "Font.h"

class Player final : public Entity
{
public:
    Player(aie::Renderer2D*& _renderer, aie::Application& _application) : Entity(_renderer, _application)
    {
        Start();
    }
    
    void Start() override;
    void Update(float _deltaTime) override;
    void Draw() override;

    int lives = 3;

private:
    float m_speed = 3;
    aie::Font* m_font;
    
};
