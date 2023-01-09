#include "MainMenu.h"
#include "Application2D.h"

void MainMenu::Start()
{
    const Vector2 windowCenter = Vector2(application->getWindowWidth(), application->getWindowHeight()) * 0.5f;
    
    m_buttons.push_back(new Button({windowCenter.x, windowCenter.y * 1.5f}, {20, 10}, "Play Game", [this] {PlayFunction();}));
    m_buttons.push_back(new Button(windowCenter, {20, 10}, "Level Select", [this] {LevelSelect();}));
    m_buttons.push_back(new Button({windowCenter.x, windowCenter.y * 0.5f}, {20, 10}, "Quit Game", [this] {QuitFunction();}));
}

void MainMenu::Update(float _deltaTime)
{
    for (const auto button : m_buttons)
        button->OnPressed();
}

void MainMenu::Draw()
{
    for (const auto button : m_buttons)
        button->Draw(renderer2D);
}

#pragma region Button Functions

void MainMenu::PlayFunction() const
{
    dynamic_cast<Application2D*>(application)->SetState("level");
}

void MainMenu::LevelSelect() const
{
    dynamic_cast<Application2D*>(application)->SetState("levelselect");
}

void MainMenu::QuitFunction() const
{
    application->quit();
}

#pragma endregion