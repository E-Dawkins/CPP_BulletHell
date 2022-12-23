#include "Player.h"

void Player::Start()
{
    pos = Vector2(application->getWindowWidth() * 0.5f, application->getWindowHeight() * 0.5f);
    size = 5;

    m_font = new aie::Font("./font/consolas.ttf", 32);
}

void Player::Update(float _deltaTime)
{
    aie::Input* input = aie::Input::getInstance();
    
    Vector2 playerMovement;
    playerMovement.x = -m_speed * input->isKeyDown(aie::INPUT_KEY_LEFT) + m_speed * input->isKeyDown(aie::INPUT_KEY_RIGHT);
    playerMovement.y = -m_speed * input->isKeyDown(aie::INPUT_KEY_DOWN) + m_speed * input->isKeyDown(aie::INPUT_KEY_UP);
    pos += playerMovement;
    
    if (lives == 0)
        application->quit();
}

void Player::Draw()
{
    renderer2D->setRenderColour(0,0,1,1);
    renderer2D->drawCircle(pos.x, pos.y, size, -1);

    char fps[32];
    sprintf_s(fps, 32, "Lives: %i", lives);
    renderer2D->setRenderColour(1,1,1,1);
    renderer2D->drawText(m_font, fps, 0, 720 - 32);
}
