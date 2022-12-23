#pragma once
#include <string>
#include <vector>

#include "Player.h"
#include "Spawner.h"

class Level final : public Entity
{
public:
    Level(aie::Renderer2D*& _renderer, aie::Application& _application) : Entity(_renderer, _application)
    {
        Start();
    }
    
    void Start() override;
    void Update(float _deltaTime) override;
    void Draw() override;

private:
    void LoadLevel(int _levelNumber);
    void InitSpawners();
    
    std::vector<Spawner*> m_spawners;
    std::vector<std::string> m_sequences;
    
    Player* m_player;
};
