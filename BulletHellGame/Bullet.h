#pragma once
#include "Color.h"
#include "IEntity.h"

class Bullet final : public IEntity
{
public:
    Bullet(aie::Renderer2D*& _renderer, aie::Application& _application, const float _delay = 1.0f) : IEntity(_renderer, _application)
    {
        m_maxWaitTimer = _delay;
        Start();
    }
    
    void Start() override;
    void Update(float _deltaTime) override;
    void Draw() override;

    bool CheckCollision(const IEntity* _entity);
    void SetColour(float _r, float _g, float _b, float _a);

    Vector2 velocity = Vector2();

private:
    float m_speed = 1;

    // wait variables
    float m_maxWaitTimer = 1.0f;
    float m_waitTimer = 0.0f;

    Color m_color = {1,1,1,1};
};
