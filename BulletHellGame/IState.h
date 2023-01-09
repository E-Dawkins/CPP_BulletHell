#pragma once
#include <string>

#include "Application.h"
#include "Renderer2D.h"

class IState
{
public:
    IState(aie::Renderer2D*& _renderer, aie::Application& _application)
    {
        renderer2D = _renderer;
        application = &_application;
    }
    virtual ~IState() = default;

    virtual void Start();
    virtual void Update(float _deltaTime);
    virtual void Draw();

    aie::Renderer2D* renderer2D;
    aie::Application* application;
};

inline void IState::Start() { }
inline void IState::Update(const float _deltaTime) { }
inline void IState::Draw() { }