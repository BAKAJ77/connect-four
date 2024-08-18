#ifndef BUTTON_H
#define BUTTON_H

#include "AppWindow.h"

class Button
{
public:
	Button();

	/**
	 * @brief Initializes the bounds of the button.
	 * @param[in] bounds The position and size of the button.
	 */
	Button(SDL_FRect bounds);

	virtual ~Button() = default;

	/**
	 * @brief Updates the button's state.
	 * @param[in] window The current application window.
	 */
	virtual void Update(AppWindow& window);

	/**
	 * @brief Draws the button.
	 * @param[in] renderer The current graphics renderer.
	 */
	virtual void Draw(GraphicsRenderer& renderer) const;

	/**
	 * @brief Gets whether or not the button is currently being pressed.
	 * @return True if being pressed, otherwise False is returned.
	 */
	bool IsPressed() const;

	/**
	 * @brief Gets whether or not the button is currently being hovered over.
	 * @return True if being hovered over, otherwise False is returned.
	 */
	bool IsHovering() const;

	/**
	 * @brief Gets the buttons position and size.
	 * @return The position and size of the button.
	 */
	SDL_FRect GetBounds() const;
private:
	SDL_FRect m_bounds;
	bool m_isPressed, m_isHovering;
	static bool sm_isReleased;
};

#endif