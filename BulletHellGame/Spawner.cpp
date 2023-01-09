#include "Spawner.h"
#include <glm/detail/func_trigonometric.inl>

void Spawner::Start()
{
    pos = Vector2(application->getWindowWidth() * 0.5f, application->getWindowHeight() * 0.75f);
    size = 15;

    for (int i = 0; i < 100; i++)
    {
        bullets.push_back(new Bullet(renderer2D, *application));
        bullets.back()->isActive = false;
        bullets.back()->SetColour(1,0,0,1);
    }
}

void Spawner::Update(const float _deltaTime)
{
    // Update bullets
    for (const auto bullet : bullets)
    {
        if (bullet->isActive)
            bullet->Update(_deltaTime);
    }

    // Run pattern sequence
    RunSequence(_deltaTime);

    // Check health state
    if (health <= 0)
        isActive = false;
}

void Spawner::Draw()
{
    // Draw bullets
    for (const auto bullet : bullets)
    {
        if (bullet->isActive)
            bullet->Draw();
    }

    if (m_lerping) // draws lerp end-point
    {
        renderer2D->setRenderColour(1,1,0,0.5);
        renderer2D->drawCircle(m_endPos.x, m_endPos.y, size * 0.7f, 0);
    }
    
    renderer2D->setRenderColour(0.3f,0.3f,0.3f,0.7f);
    renderer2D->drawCircle(pos.x, pos.y, size, 0);
}

/**
 * \brief Runs the spawner's command sequence
 */
void Spawner::RunSequence(const float _deltaTime)
{
    char* endPtr; // used for string-to-type functions
    
    m_commInterval += _deltaTime;
    
    if (m_lerping)
        LerpPos(_deltaTime, m_endPos);

    else if (m_waiting)
        Wait(_deltaTime);

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
            Interval(strtof(m_sequence[index].c_str(), &endPtr));
        }

        // Move, Position
        if (commType == 'm' || commType == 'p') 
        {
            MovePos(_deltaTime, index, commType == 'm');
        }

        // Wait
        if (commType == 'w') 
        {
            Wait(_deltaTime, strtof(m_sequence[index].c_str(), &endPtr));
        }

        // Circle
        if (commType == 'c') 
        {
            CircleSpawn(strtol(m_sequence[index].c_str(), &endPtr, 10));
        }

        // Dice
        if (commType == 'd')
        {
            DiceSpawn(index);
        }
    }
}

#pragma region Helper Functions

/**
 * \brief Gets a list of floats from the sequence split by ':', i.e. 3:4:5 => {3,4,5}
 */
std::vector<float> Spawner::GetVars(const int _index)
{
    std::vector<float> subStrings;
    std::string curSubStr;

    for (std::string::iterator iter = m_sequence[_index].begin(); iter != m_sequence[_index].end(); ++iter)
    {
        if (*iter != ':')
            curSubStr += *iter;

        if (*iter == ':' || iter == m_sequence[_index].end() - 1)
        {
            if (!curSubStr.empty())
            {
                char* endPtr;
                subStrings.push_back(strtof(curSubStr.c_str(), &endPtr));
            }
                
            curSubStr = "";
        }
    }

    return subStrings;
}

/**
 * \brief Sets a bullet from the pool to active, and sets its position/velocity
 */
void Spawner::SpawnBullet(const Vector2 _pos, const Vector2 _velocity)
{
    bullets.front()->pos = _pos;
    bullets.front()->velocity = _velocity;
    bullets.front()->isActive = true;
    
    bullets.front()->Start();
    
    std::rotate(bullets.begin(), bullets.begin() + 1, bullets.end());
}

#pragma endregion

#pragma region Command Functions

/**
 * \brief Sets the bullet interval to the _newInterval
 */
void Spawner::Interval(const float _newInterval)
{
    m_commInterval = m_maxCommInterval = _newInterval;
}

/**
 * \brief Moves the spawner to the position signified in the pattern sequence
 */
void Spawner::MovePos(const float _deltaTime, const int _index, const bool _lerp)
{
    const std::vector<float> vars = GetVars(_index);
    const Vector2 newPos = {vars[0] * application->getWindowWidth(), vars[1] * application->getWindowHeight()};

    if (_lerp) LerpPos(_deltaTime, newPos);
    else pos = newPos;
}

/**
 * \brief Interpolates the spawner's position to the _newEndPos
 */
void Spawner::LerpPos(const float _deltaTime, const Vector2 _newEndPos)
{
    if (m_lerping == false) // start lerp variables
    {
        m_t = 0;
        m_startPos = pos;
        m_endPos = _newEndPos;
        m_commInterval = m_maxCommInterval;
        m_lerping = true;
    }
    
    pos = Vector2::Lerp(m_startPos, m_endPos, m_t);
    m_t += _deltaTime;
        
    if (pos == m_endPos) // end of lerp
        m_lerping = false;
}

/**
 * \brief Waits for _maxWaitTime seconds before proceeding
 */
void Spawner::Wait(const float _deltaTime, const float _maxWaitTime)
{
    if (m_waiting == false) // start waiting variables
    {
        m_waitTime = 0;
        m_maxWaitTime = _maxWaitTime;
        m_waiting = true;
    }
    
    m_waitTime += _deltaTime;

    if (m_waitTime >= m_maxWaitTime) // end of wait time
        m_waiting = false;
}

/**
 * \brief Spawns _bulletAmount of bullets evenly distributed in a circle around the spawner
 */
void Spawner::CircleSpawn(const int _bulletAmount)
{
    for (int i = 0; i < _bulletAmount; i++) // spawns bullets evenly in a circle around spawner
    {
        const float rads = glm::radians((360.0f / _bulletAmount) * i);
        Vector2 velocity = Vector2(cos(rads), sin(rads)).Normalize();
        SpawnBullet(pos + velocity * 20.0f, velocity);
    }
}

/**
 * \brief Spawns a dice face of bullets at a corner of the spawner, i.e. top-left
 */
void Spawner::DiceSpawn(const int _index)
{
    const std::vector<float> diceVars = GetVars(_index);
    
    const float rads = glm::radians(45.0f * diceVars[1]); // spawn pos at increments of 45 degrees
    const Vector2 diceCenter = pos + (Vector2(cos(rads), sin(rads)) * 35.0f);

    const int diceVal = (int)diceVars[0] % 7 + ((int)diceVars[0] % 7 == 0 ? 1 : 0);

    std::vector<Vector2> diceFacePositions;
    constexpr float diceSpacing = 10.0f;

    if (diceVal % 2 != 0) // odd nums, i.e. 1,3,5
    {
        diceFacePositions.push_back(diceCenter);
    }

    if (diceVal > 1) // all but 1, i.e. 2,3,4,5,6
    {
        diceFacePositions.push_back(diceCenter - Vector2(diceSpacing, diceSpacing));
        diceFacePositions.push_back(diceCenter + Vector2(diceSpacing, diceSpacing));
    }

    if (diceVal > 3) // above 3, i.e. 4,5,6
    {
        diceFacePositions.push_back(diceCenter - Vector2(diceSpacing, -diceSpacing));
        diceFacePositions.push_back(diceCenter + Vector2(diceSpacing, -diceSpacing));
    }

    if (diceVal == 6) // only 6
    {
        diceFacePositions.push_back(diceCenter - Vector2(diceSpacing, 0));
        diceFacePositions.push_back(diceCenter + Vector2(diceSpacing, 0));
    }

    for(const auto position : diceFacePositions) // spawn dice-face of bullets
    {
        SpawnBullet(position, (diceCenter - pos).Normalize());
    }
}

#pragma endregion