#include "Player.h"

void Player::Start()
{
    pos = Vector2(application->getWindowWidth() * 0.5f, application->getWindowHeight() * 0.5f);
    size = 7;
    m_speed = 200;
    m_turretLength = size * 2.5f;

    m_font = new aie::Font("./font/consolas.ttf", 32);

    for (int i = 0; i < 50; i++)
    {
        bullets.push_back(new Bullet(renderer2D, *application, 0));
        bullets.back()->isActive = false;
        bullets.back()->SetColour(0, 1, 0, 1);
    }
}

void Player::Update(const float _deltaTime)
{
    // Update bullets
    for (const auto bullet : bullets)
    {
        if (bullet->isActive)
            bullet->Update(_deltaTime);
    }
    
    aie::Input* input = aie::Input::getInstance();

    // Player movement
    Vector2 playerMovement;
    playerMovement.x = -m_speed * (input->isKeyDown(aie::INPUT_KEY_A) || input->isKeyDown(aie::INPUT_KEY_LEFT)) +
                        m_speed * (input->isKeyDown(aie::INPUT_KEY_D) || input->isKeyDown(aie::INPUT_KEY_RIGHT));
    playerMovement.y = -m_speed * (input->isKeyDown(aie::INPUT_KEY_S) || input->isKeyDown(aie::INPUT_KEY_DOWN)) +
                        m_speed * (input->isKeyDown(aie::INPUT_KEY_W) || input->isKeyDown(aie::INPUT_KEY_UP));
    pos += playerMovement * _deltaTime;

    // Player shooting
    m_dirToMouse = (Vector2((float)input->getMouseX(), (float)input->getMouseY()) - pos).Normalize();
    m_turretEnd = pos + m_dirToMouse * m_turretLength;
    
    if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))
    {
        SpawnBullet(m_turretEnd, m_dirToMouse * 3);
    }

    // Player death
    if (lives == 0)
        application->quit();
}

void Player::Draw()
{
    // Draw player
    renderer2D->setRenderColour(0,0,1,1);
    renderer2D->drawCircle(pos.x, pos.y, size, -1);

    // Draw turret
    renderer2D->drawLine(pos.x, pos.y, m_turretEnd.x, m_turretEnd.y, 5);

    // Draw bullets
    for (const auto bullet : bullets)
    {
        if (bullet->isActive)
            bullet->Draw();
    }
    
    // Draw lives
    char fps[32];
    sprintf_s(fps, 32, "Lives: %i", lives);
    renderer2D->setRenderColour(1,1,1,1);
    renderer2D->drawText(m_font, fps, 0, 720 - 32);
}

void Player::SpawnBullet(const Vector2 _pos, const Vector2 _velocity)
{
    bullets.front()->pos = _pos;
    bullets.front()->velocity = _velocity;
    bullets.front()->isActive = true;
    
    bullets.front()->Start();
    
    std::rotate(bullets.begin(), bullets.begin() + 1, bullets.end());
}