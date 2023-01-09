#pragma once
#include "Renderer2D.h"
#include "Application.h"
#include "Input.h"
#include "Vector2.h"

class IEntity
{
public:
    IEntity(aie::Renderer2D*& _renderer, aie::Application& _application)
    {
        renderer2D = _renderer;
        application = &_application;
    }
    virtual ~IEntity() = default;

    virtual void Start();
    virtual void Update(float _deltaTime);
    virtual void Draw();

    aie::Renderer2D* renderer2D;
    aie::Application* application;

    Vector2 pos = Vector2();
    float size = 5;
    bool isActive = true;
};

inline void IEntity::Start() { }
inline void IEntity::Update(float _deltaTime) { }
inline void IEntity::Draw() { }