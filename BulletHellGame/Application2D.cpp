#include "Application2D.h"
#include "Font.h"
#include "Input.h"
#include "Level.h"
#include "../dependencies/glfw/include/GLFW/glfw3.h"

Application2D::Application2D() = default;
Application2D::~Application2D() = default;

// Initialise all memory pointers
bool Application2D::startup()
{
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_level = new Level(m_2dRenderer, *this);
	
	return true;
}

// Cleanup all memory pointers
void Application2D::shutdown()
{
	delete m_2dRenderer;
	delete m_font;
	
	delete m_level;
}

// Main game loop
void Application2D::update(const float _deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	m_level->Update(_deltaTime);

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

	m_level->Draw();
	
	m_2dRenderer->end();
}