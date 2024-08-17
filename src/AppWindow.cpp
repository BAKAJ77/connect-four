#include "AppWindow.h"
#include <stdexcept>

AppWindow::AppWindow() :
	m_window(nullptr), m_width(0), m_height(0)
{}

AppWindow::AppWindow(std::string_view title, uint16_t width, uint16_t height) :
	m_title(title), m_width(width), m_height(height)
{
	m_window = SDL_CreateWindow(title.data(), width, height, NULL);
	if (!m_window)
	{
		throw std::runtime_error(SDL_GetError());
	}

	SDL_SetWindowPosition(m_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	m_renderer = GraphicsRenderer(m_window); // Init the graphics renderer
}

AppWindow::~AppWindow()
{
	if (SDL_WasInit(SDL_INIT_VIDEO) != 0)
	{
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	}
}

bool AppWindow::GetNextEvent(SDL_Event* event)
{
	return SDL_PollEvent(event);
}

GraphicsRenderer& AppWindow::GetRenderer()
{
	return m_renderer;
}

std::string_view AppWindow::GetTitle() const
{
	return m_title;
}

uint16_t AppWindow::GetWidth() const
{
	return m_width;
}

uint16_t AppWindow::GetHeight() const
{
	return m_height;
}

SDL_Window* AppWindow::GetSDLWindowStruct()
{
	return m_window;
}
