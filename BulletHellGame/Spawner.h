#pragma once
#include <string>

#include "Bullet.h"
#include "Player.h"

class Spawner final : public IEntity
{
public:
    Spawner(aie::Renderer2D*& _renderer, aie::Application& _application) : IEntity(_renderer, _application)
    {
        Start();
    }

    ~Spawner() override
    {
        for (const auto bullet : bullets)
            delete bullet;
    }
    
    void Start() override;
    void Update(float _deltaTime) override;
    void Draw() override;

    void SetSequence(const std::vector<std::string>& _sequence)
    {
        m_sequence = _sequence;
    }

    float health = 2;
    
    std::vector<Bullet*> bullets;

private:
    // Helper Functions
    std::vector<float> GetVars(int _index);
    void SpawnBullet(Vector2 _pos, Vector2 _velocity);
    
    void RunSequence(float _deltaTime);

    // Command types
    void Interval(float _newInterval);
    void MovePos(float _deltaTime, int _index, bool _lerp);
    void LerpPos(float _deltaTime, Vector2 _newEndPos);
    void Wait(float _deltaTime, float _maxWaitTime = 1.0f);
    void CircleSpawn(int _bulletAmount);
    void DiceSpawn(int _index);

    // Command variables
    std::vector<std::string> m_sequence;
    int m_curComm = 0;
    float m_commInterval = 1.0f;
    float m_maxCommInterval = 1.0f;

    // Wait variables
    bool m_waiting = false;
    float m_maxWaitTime = 1.0f;
    float m_waitTime = 0.0f;

    // Lerp variables
    Vector2 m_startPos = Vector2();
    Vector2 m_endPos = Vector2();
    bool m_lerping = false;
    float m_t = 0;
};
