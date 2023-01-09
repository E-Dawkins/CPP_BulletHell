#include "Button.h"

void Button::OnPressed()
{
    aie::Input* input = aie::Input::getInstance();
     
    if (IsHovering() && input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT))
    {
        m_delegate();
        m_clicked = true;
    }
}

void Button::Draw(aie::Renderer2D* _renderer2D) const
{
    _renderer2D->setRenderColour(1, 1, 1, 1);
    _renderer2D->drawBox(m_centerPos.x, m_centerPos.y, m_textSize.x + m_padding.x, m_textSize.y + m_padding.y);

    _renderer2D->setRenderColour(0, 0, 0, 1);
    _renderer2D->drawText(m_font, m_text.c_str(), m_textPos.x, m_textPos.y);
}