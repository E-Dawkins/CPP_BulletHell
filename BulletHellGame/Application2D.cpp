#include "Application2D.h"
#include "Font.h"
#include "Input.h"
#include "../dependencies/glfw/include/GLFW/glfw3.h"
#include "MainMenu.h"
#include "Level.h"
#include "LevelSelect.h"

Application2D::Application2D() = default;
Application2D::~Application2D() = default;

// Initialise all memory pointers
bool Application2D::startup()
{
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	AddState("MainMenu", new MainMenu(m_2dRenderer, *this));
	AddState("Level", new Level(m_2dRenderer, *this));
	AddState("LevelSelect", new LevelSelect(m_2dRenderer, *this));
	
	return true;
}

// Cleanup all memory pointers
void Application2D::shutdown()
{
	delete m_2dRenderer;
	delete m_font;
	
	for (const auto& state : m_states)
		delete state.second;
}

// Main game loop
void Application2D::update(const float _deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	m_states.at(m_curState)->Update(_deltaTime);

	char fps[32];
	sprintf_s(fps, 32, "Bullet Hell | FPS: %i", getFPS());
	glfwSetWindowTitle(getWindowPtr(), fps);
	
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

// Draw all game entities
void Application2D::draw()
{
	clearScreen();
	
	m_2dRenderer->begin();

	m_states.at(m_curState)->Draw();
	
	m_2dRenderer->end();
}

void Application2D::AddState(std::string _stateName, IState* _newState)
{
	std::string stateNameLower;

	for (const auto character : _stateName)
		stateNameLower += (char)std::tolower(character);
	
	m_states.insert({stateNameLower, _newState});

	if (m_states.size() == 1) // auto-sets first state
		m_curState = stateNameLower;
}
	
void Application2D::SetState(const std::string _stateName)
{
	if (m_states.find(_stateName) != m_states.end()) // found state with _stateName
	{
		m_curState = _stateName;
	}
}

IState*& Application2D::GetState()
{
	return m_states.at(m_curState);
}
