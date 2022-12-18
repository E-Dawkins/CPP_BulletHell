#pragma once
#include "Bullet.h"
#include "Entity.h"
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

private:
    void LerpPos(float _deltaTime);
    void SpawnBullets();

    Player* m_player;
    
    float m_moveTimer = 0;
    float m_maxMoveTimer = 5;

    float m_spawnTimer = 0;
    float m_maxSpawnTimer = 1;
    int m_maxBulletAmount = 10;
    int m_minBulletAmount = 3;

    std::vector<Vector2> m_spawnerPositions;
    std::vector<Bullet*> m_bullets;

    Vector2 m_startPos = Vector2();
    Vector2 m_endPos = Vector2();
    bool m_lerping = false;
    float m_t = 0;
};
