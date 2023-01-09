#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "Level.h"

class Application2D final : public aie::Application
{
public:

	Application2D();
	~Application2D() override;

	bool startup() override;
	void shutdown() override;

	void update(float _deltaTime) override;
	void draw() override;

	void AddState(std::string _stateName, IState* _newState);
	void SetState(std::string _stateName);
	IState*& GetState();

protected:

	aie::Renderer2D* m_2dRenderer = nullptr;
	aie::Font* m_font = nullptr;

	std::map<std::string, IState*> m_states;
	std::string m_curState;
};