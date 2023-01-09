#pragma once
#include <string>
#include <vector>

#include "IState.h"
#include "Player.h"
#include "Spawner.h"

class Level final : public IState
{
public:
    Level(aie::Renderer2D*& _renderer, aie::Application& _application) : IState(_renderer, _application)
    {
        Start();
    }

    ~Level() override
    {
        for (const auto spawner : m_spawners)
            delete spawner;

        delete m_player;
    }
    
    void Start() override;
    void Update(float _deltaTime) override;
    void Draw() override;

    void LoadLevel(int _levelNumber);
    void InitSpawners();
    
private:
    std::vector<Spawner*> m_spawners;
    std::vector<std::string> m_sequences;
    
    Player* m_player;
};
