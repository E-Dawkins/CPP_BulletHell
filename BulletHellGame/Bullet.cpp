#include "Bullet.h"

#include <iostream>

void Bullet::Start()
{
    size = 4;
    m_speed = 100;
    m_waitTimer = 0.0f;
}

void Bullet::Update(float _deltaTime)
{
    if (m_waitTimer < m_maxWaitTimer)
    {
        m_waitTimer += _deltaTime;
        return;
    }
    
    pos += velocity * m_speed * _deltaTime;

    // Bullet off-screen
    if (pos.x <= 0 || pos.x >= application->getWindowWidth() || pos.y <= 0 || pos.y >= application->getWindowHeight())
    {
        isActive = false;
    }
}

void Bullet::Draw()
{
    // if (m_waitTimer < m_maxWaitTimer)
    // {
    //     renderer2D->setRenderColour(1,0,1,0.5f);
    //     
    //     const Vector2 lineEnd = pos + velocity * 15.0f;
    //     renderer2D->drawLine(pos.x, pos.y, lineEnd.x, lineEnd.y, 5);
    // }

    renderer2D->setRenderColour(m_color.r, m_color.g, m_color.b, m_color.a);
    renderer2D->drawCircle(pos.x, pos.y, size, 0);
}

/**
 * \brief Returns whether the bullet has collided with _entity
 */
bool Bullet::CheckCollision(const IEntity* _entity)
{
    if (!isActive)
        return false;
    
    // Bullet collided with other entity
    if (Vector2::Distance(pos, _entity->pos) < size + _entity->size)
    {
        isActive = false;
        return true;
    }

    return false;
}

void Bullet::SetColour(const float _r, const float _g, const float _b, const float _a)
{
    m_color.r = _r;
    m_color.g = _g;
    m_color.b = _b;
    m_color.a = _a;
}
