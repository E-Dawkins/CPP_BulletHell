#pragma once
#include <string>
#include <vector>

#include "Bullet.h"
#include "Player.h"

class Spawner final : public Entity
{
public:
    Spawner(aie::Renderer2D*& _renderer, aie::Application& _application, Player*& _player) : Entity(_renderer, _application)
    {
        m_player = _player;
        
        Start();
    }
    
    void Start() override;
    void Update(float _deltaTime) override;
    void Draw() override;

    void SetSequence(const std::vector<std::string>& _sequence)
    {
        m_sequence = _sequence;
    }

private:
    void RunSequence(float _deltaTime);
    
    // Command types
    void LerpPos(float _deltaTime);
    void Wait(float _deltaTime);
    bool CircleSpawn(int _bulletAmount);

    // Command variables
    std::vector<std::string> m_sequence;
    int m_curComm = 0;
    float m_maxCommInterval = 1.0f;
    float m_commInterval = 1.0f;

    // Wait variables
    bool m_waiting = false;
    float m_maxWaitTime = 1.0f;
    float m_waitTime = 0.0f;

    // Lerp variables
    Vector2 m_startPos = Vector2();
    Vector2 m_endPos = Vector2();
    bool m_lerping = false;
    float m_t = 0;

    Player* m_player;
    std::vector<Bullet*> m_bullets;
};
