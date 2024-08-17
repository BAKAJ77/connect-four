#include "Button.h"

Button::Button() :
	m_bounds({ 0, 0, 0, 0 }), m_isPressed(false), m_isReleased(true), m_isHovering(false)
{}

Button::Button(SDL_FRect bounds) :
	m_bounds(bounds), m_isPressed(false), m_isReleased(true), m_isHovering(false)
{}

void Button::Update(AppWindow& window)
{
	SDL_FPoint cursorPosition = { 0, 0 };
	uint32_t mouseButtonMask = SDL_GetMouseState(&cursorPosition.x, &cursorPosition.y);
	m_isHovering = SDL_PointInRectFloat(&cursorPosition, &m_bounds);

	if (m_isReleased && m_isHovering && ((mouseButtonMask & SDL_BUTTON_LMASK) != 0))
	{
		m_isPressed = true;
		m_isReleased = false;
	}
	else
	{
		m_isPressed = false;
	}

	if (!m_isReleased && (mouseButtonMask & SDL_BUTTON_LMASK) == 0)
	{
		m_isReleased = true;
	}
}

void Button::Draw(GraphicsRenderer& renderer) const {}

bool Button::IsPressed() const
{
	return m_isPressed;
}

bool Button::IsHovering() const
{
	return m_isHovering;
}

SDL_FRect Button::GetBounds() const
{
	return m_bounds;
}
