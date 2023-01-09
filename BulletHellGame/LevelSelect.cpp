#include "LevelSelect.h"
#include "Application2D.h"

void LevelSelect::Start()
{
    const Vector2 windowCenter = Vector2(application->getWindowWidth(), application->getWindowHeight()) * 0.5f;
    
    m_buttons.push_back(new Button({windowCenter.x, windowCenter.y * 1.5f}, {20, 10}, "1", [this] {LoadLevel();}));
    m_buttons.push_back(new Button(windowCenter, {20, 10}, "2", [this] {LoadLevel();}));
    m_buttons.push_back(new Button({windowCenter.x, windowCenter.y * 0.5f}, {20, 10}, "3", [this] {LoadLevel();}));
}

void LevelSelect::Update(float _deltaTime)
{
    for (const auto button : m_buttons)
        button->OnPressed();
}

void LevelSelect::Draw()
{
    for (const auto button : m_buttons)
        button->Draw(renderer2D);
}

#pragma region Button Functions

void LevelSelect::LoadLevel() const
{
    dynamic_cast<Application2D*>(application)->SetState("level");

    for (int i = 0; i < (int)m_buttons.size(); i++)
    {
        if (m_buttons[i]->IsHovering())
        {
            IState* curState = dynamic_cast<Application2D*>(application)->GetState();
            dynamic_cast<Level*>(curState)->LoadLevel(i + 1);
            dynamic_cast<Level*>(curState)->InitSpawners();
            break;
        }
    }
}

#pragma endregion