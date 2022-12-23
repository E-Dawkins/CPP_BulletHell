#include "Bullet.h"

#include <iostream>

void Bullet::Start()
{
    size = 3;
}

void Bullet::Update(float _deltaTime)
{
    pos += velocity * m_speed;

    if (pos.x <= 0 || pos.x >= application->getWindowWidth() || pos.y <= 0 || pos.y >= application->getWindowHeight())
    {
        isActive = false;
    }

    // Bullet collided with player
    if (Vector2::Distance(pos, m_player->pos) < size + m_player->size)
    {
        m_player->lives--;
        isActive = false;
    }
}

void Bullet::Draw()
{
    renderer2D->setRenderColour(1,0,0,1);
    renderer2D->drawCircle(pos.x, pos.y, size, 0);
}