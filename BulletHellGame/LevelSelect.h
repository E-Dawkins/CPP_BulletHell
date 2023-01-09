#pragma once
#include <vector>

#include "Button.h"
#include "IState.h"

class LevelSelect final : public IState
{
public:
    LevelSelect(aie::Renderer2D*& _renderer, aie::Application& _application) : IState(_renderer, _application)
    {
        Start();
    }

    ~LevelSelect() override
    {
        for (const auto button : m_buttons)
            delete button;
    }
    
    void Start() override;
    void Draw() override;
    void LoadLevel() const;
    void Update(float _deltaTime) override;

protected:
    std::vector<Button*> m_buttons;

    // Button functions
    
};
