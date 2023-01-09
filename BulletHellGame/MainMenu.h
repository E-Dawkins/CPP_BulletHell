#pragma once
#include <vector>

#include "Button.h"
#include "IState.h"

class MainMenu final : public IState
{
public:
    MainMenu(aie::Renderer2D*& _renderer, aie::Application& _application) : IState(_renderer, _application)
    {
        Start();
    }

    ~MainMenu() override
    {
        for (const auto button : m_buttons)
            delete button;
    }
    
    void Start() override;
    void Draw() override;
    void Update(float _deltaTime) override;

protected:
    std::vector<Button*> m_buttons;

    // Button Functions
    void PlayFunction() const;
    void LevelSelect() const;
    void QuitFunction() const;
};
