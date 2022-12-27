#include "Spawner.h"
#include <glm/detail/func_trigonometric.inl>

void Spawner::Start()
{
    pos = Vector2(application->getWindowWidth() * 0.5f, application->getWindowHeight() * 0.75f);
    size = 15;
}

void Spawner::Update(float _deltaTime)
{
    // Update bullets
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

    // Run pattern sequence
    RunSequence(_deltaTime);
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
    
    renderer2D->setRenderColour(0.3f,0.3f,0.3f,0.7f);
    renderer2D->drawCircle(pos.x, pos.y, size, 0);
}

void Spawner::RunSequence(float _deltaTime)
{
    m_commInterval += _deltaTime;
    
    if (m_lerping)
        LerpPos(_deltaTime);

    else if (m_waiting)
        Wait(_deltaTime, m_maxWaitTime);

    // Run current command
    else if (m_curComm < (int)m_sequence.size() && m_commInterval >= m_maxCommInterval)
    {
        const int index = m_curComm;
        const char commType = m_sequence[index].front();
        m_sequence[index].erase(0, 1);
        
        m_commInterval = 0;
        m_curComm++;

        // Interval
        if (commType == 'i') 
        {
            m_commInterval = m_maxCommInterval = (float)atof(m_sequence[index].c_str());
        }

        // Move, Position
        if (commType == 'm' || commType == 'p') 
        {
            MovePos(_deltaTime, index, commType == 'm');
        }

        // Wait
        if (commType == 'w') 
        {
            Wait(_deltaTime, (float)atof(m_sequence[index].c_str()));
        }

        // Circle
        if (commType == 'c') 
        {
            CircleSpawn(atoi(m_sequence[index].c_str()));
        }
    }
}

/**
 * \brief Moves the spawner to the position signified in the pattern sequence.
 */
void Spawner::MovePos(float _deltaTime, int _index, bool _lerp)
{
    const int colonIndex = m_sequence[_index].find_first_of(':');
    const std::string xStr = m_sequence[_index].substr(0, colonIndex);
    const std::string yStr = m_sequence[_index].substr(colonIndex + 1, m_sequence[_index].length() - colonIndex);

    const Vector2 tempPos = {(float)atof(xStr.c_str()), (float)atof(yStr.c_str())};
    const Vector2 newPos = {tempPos.x * application->getWindowWidth(), tempPos.y * application->getWindowHeight()};

    if (_lerp)
    {
        m_endPos = newPos;
        LerpPos(_deltaTime);
        m_commInterval = m_maxCommInterval;
    }
    else pos = newPos;
}

/**
 * \brief Lerps the spawner's position to the m_endPos.
 */
void Spawner::LerpPos(float _deltaTime)
{
    // Start lerp variables
    if (m_lerping == false) 
    {
        m_t = 0;
        m_startPos = pos;
        m_lerping = true;
    }

    // Actual lerp code
    pos = Vector2::Lerp(m_startPos, m_endPos, m_t);

    m_t += _deltaTime;
        
    if (pos == m_endPos) // end of lerp
        m_lerping = false;
}

/**
 * \brief Waits for _maxWaitTime seconds before proceeding.
 */
void Spawner::Wait(float _deltaTime, float _maxWaitTime)
{
    m_maxWaitTime = _maxWaitTime;
    
    if (m_waiting == false)
    {
        m_waitTime = 0;
        m_waiting = true;
    }
    
    m_waitTime += _deltaTime;

    if (m_waitTime >= m_maxWaitTime)
        m_waiting = false;
}

/**
 * \brief Spawns _bulletAmount of bullets evenly distributed in a circle around the spawner.
 */
bool Spawner::CircleSpawn(int _bulletAmount)
{
    for (int i = 0; i < _bulletAmount; i++) // spawns bullets evenly in a circle around spawner
    {
        m_bullets.push_back(new Bullet(renderer2D, *application, m_player));
        m_bullets.back()->pos = pos;

        const float rads = glm::radians((360.0f / _bulletAmount) * i);
        m_bullets.back()->velocity = Vector2(cos(rads), sin(rads));
    }

    return true;
}