#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "Input.h"
#include "Vector2.h"

class Entity
{
public:
    Entity(aie::Renderer2D*& _renderer, aie::Application& _application)
    {
        renderer2D = _renderer;
        application = &_application;
    }
    virtual ~Entity() = default;

    virtual void Start();
    virtual void Update(float _deltaTime);
    virtual void Draw();

    aie::Renderer2D* renderer2D;
    aie::Application* application;
    
    Vector2 pos = Vector2();
    float size = 5;
    bool isActive = true;
};

inline void Entity::Start() { }
inline void Entity::Update(float _deltaTime) { }
inline void Entity::Draw() { }