#include "Spawner.h"
#include <glm/detail/func_trigonometric.inl>

void Spawner::Start()
{
    pos = Vector2(application->getWindowWidth() * 0.5f, application->getWindowHeight() * 0.75f);
    size = 15;

    m_spawnerPositions.emplace_back(application->getWindowWidth() * 0.25f, application->getWindowHeight() * 0.25f);
    m_spawnerPositions.emplace_back(application->getWindowWidth() * 0.75f, application->getWindowHeight() * 0.75f);
    m_spawnerPositions.emplace_back(application->getWindowWidth() * 0.25f, application->getWindowHeight() * 0.75f);
    m_spawnerPositions.emplace_back(application->getWindowWidth() * 0.75f, application->getWindowHeight() * 0.25f);
}

void Spawner::Update(float _deltaTime)
{
    if (m_lerping)
        LerpPos(_deltaTime);

    else
    {
        m_moveTimer += _deltaTime;
        m_spawnTimer += _deltaTime;

        if (m_spawnTimer >= m_maxSpawnTimer)
        {
            SpawnBullets();
            m_spawnTimer = 0;
        }

        // Reset timer, lerp to new pos
        if (m_moveTimer >= m_maxMoveTimer)
        {
            m_moveTimer = 0;
            m_lerping = true;
        }
    }
    
    for (const auto bullet : m_bullets)
        bullet->Update(_deltaTime);

    for (int i = (int)m_bullets.size() - 1; i >= 0; i--)
    {
        if (!m_bullets[i]->isActive)
        {
            delete m_bullets[i];
            m_bullets.erase(m_bullets.begin() + i);
        }
    }
}

void Spawner::Draw()
{
    for (const auto bullet : m_bullets)
        bullet->Draw();

    if (m_lerping)
    {
        renderer2D->setRenderColour(1,1,0,0.5);
        renderer2D->drawCircle(m_endPos.x, m_endPos.y, size * 0.7f, 0);
    }
    
    renderer2D->setRenderColour(1,1,1,1);
    renderer2D->drawCircle(pos.x, pos.y, size, 0);
}

void Spawner::LerpPos(float _deltaTime)
{
    if (m_t == 0) // Start lerping variables
    {
        m_startPos = pos;
        m_endPos = m_spawnerPositions[rand() % m_spawnerPositions.size()];
    
        m_lerping = true;
    }

    // Actual lerp code
    pos = Vector2::Lerp(m_startPos, m_endPos, m_t);

    m_t += _deltaTime;
        
    if (pos == m_endPos)
    {
        m_lerping = false;
        m_t = 0;
    }
}

void Spawner::SpawnBullets()
{
    const int bulletAmount = (rand() % (m_maxBulletAmount - 1 - m_minBulletAmount)) + m_minBulletAmount;

    for (int i = 0; i < bulletAmount; i++)
    {
        m_bullets.push_back(new Bullet(renderer2D, *application, m_player));
        m_bullets.back()->pos = pos;

        const float rads = glm::radians((360.0f / bulletAmount) * i);
        m_bullets.back()->velocity = Vector2(cos(rads), sin(rads));
    }
}
