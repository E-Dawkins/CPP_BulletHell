#pragma once
#include <functional>
#include <string>

#include "Application.h"
#include "Font.h"
#include "Input.h"
#include "Renderer2D.h"
#include "Vector2.h"

class Button
{
public:
    Button(const Vector2 _pos, const Vector2 _padding = {10,10}, const std::string _buttonText = "", const std::function<void()> _delegate = [] {})
    {
        m_centerPos = _pos;
        m_padding = _padding;
        m_delegate = _delegate;
        m_text = _buttonText;
        
        m_font = new aie::Font("./font/consolas.ttf", 64);
        
        if (!_buttonText.empty())
        {
            m_textSize.x = m_font->getStringWidth(_buttonText.c_str());
            m_textSize.y = m_font->getStringHeight(_buttonText.c_str());
        }

        m_textPos = m_centerPos - m_textSize * 0.5f;
        m_textPos += Vector2(-m_font->GetStartOffset(_buttonText.c_str()) * 0.5f, m_font->getLowestHeight(_buttonText.c_str()));
    }

    ~Button()
    {
        delete m_font;
    }

    void OnPressed();
    void Draw(aie::Renderer2D* _renderer2D) const;

    // Helper Functions
    bool IsHovering() const
    {
        aie::Input* input = aie::Input::getInstance();
    
        const Vector2 mousePos = {(float)input->getMouseX(), (float)input->getMouseY()};

        return mousePos.x >= m_centerPos.x - m_textSize.x * 0.5f && mousePos.x <= m_centerPos.x + m_textSize.x * 0.5f &&
            mousePos.y >= m_centerPos.y - m_textSize.y * 0.5f && mousePos.y <= m_centerPos.y + m_textSize.y * 0.5f;
    }
    
    bool WasPressed() const
    {
        return m_clicked;
    }

protected:
    Vector2 m_centerPos;
    Vector2 m_textPos;
    
    std::string m_text;
    Vector2 m_textSize;
    Vector2 m_padding;
    
    std::function<void()> m_delegate;
    aie::Font* m_font = nullptr;

    bool m_clicked = false;
};
