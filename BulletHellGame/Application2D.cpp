#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Player.h"
#include "Spawner.h"

Application2D::Application2D() = default;
Application2D::~Application2D() = default;

// Initialise all memory pointers
bool Application2D::startup()
{
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_entities.push_back(new Player(m_2dRenderer, *this));
	m_entities.push_back(new Spawner(m_2dRenderer, *this, (Player*&)m_entities[0]));
	
	return true;
}

// Cleanup all memory pointers
void Application2D::shutdown()
{
	delete m_2dRenderer;
	delete m_font;

	for (const auto entity : m_entities)
		delete entity;
}

// Main game loop
void Application2D::update(const float _deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	for (const auto entity : m_entities)
	{
		if (entity->isActive)
			entity->Update(_deltaTime);
	}
	
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

// Draw all game entities
void Application2D::draw()
{
	clearScreen();
	
	m_2dRenderer->begin();

	for (const auto entity : m_entities)
	{
		if (entity->isActive)
			entity->Draw();
	}
	
	// Draws fps top left
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	
	m_2dRenderer->end();
}