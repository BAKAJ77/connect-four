#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include "GraphicsRenderer.h"

#include <SDL3/SDL.h>
#include <string>

class AppWindow
{
public:
	AppWindow();

	/**
	 * @brief Creates a new SDL3 based application window.
	 * 
	 * @param[in] title The title of the window.
	 * @param[in] width The width of the window.
	 * @param[in] height The height of the window.
	 */
	AppWindow(std::string_view title, uint16_t width, uint16_t height);

	~AppWindow();

	/**
	 * @brief Gets the next event stored in the events queue and pops it from the queue.
	 * @param[out] event Pointer to the fetched event.
	 * 
	 * @return True if an event was fetched, otherwise the queue was empty therefore returning False.
	 */
	bool GetNextEvent(SDL_Event* event);
	
	/**
	 * @brief Gets the application window's graphics renderer.
	 * @return The graphics renderer attached to the application window.
	 */
	GraphicsRenderer& GetRenderer();

	/**
	 * @brief Gets the title of the window.
	 * @return The title of the window.
	 */
	std::string_view GetTitle() const;

	/**
	 * @brief Gets the width of the window.
	 * @return The width of the window.
	 */
	uint16_t GetWidth() const;

	/**
	 * @brief Gets the height of the window.
	 * @return The height of the window.
	 */
	uint16_t GetHeight() const;

	/**
	 * @brief Gets the underlying SDL3 window struct.
	 * @return Pointer to the underlying SDL3 window struct.
	 */
	SDL_Window* GetSDLWindowStruct();
private:
	SDL_Window* m_window;
	std::string m_title;
	uint16_t m_width, m_height;

	GraphicsRenderer m_renderer;
};

#endif