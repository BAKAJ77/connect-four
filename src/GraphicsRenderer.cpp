#include "GraphicsRenderer.h"
#include <stdexcept>

GraphicsRenderer::GraphicsRenderer() :
	m_window(nullptr), m_renderingContext(nullptr), m_clearColor({ 0, 0, 0, 0 })
{}

GraphicsRenderer::GraphicsRenderer(SDL_Window* window) :
	m_window(window), m_clearColor({ 0, 0, 0, 0 })
{
	m_renderingContext = SDL_CreateRenderer(window, nullptr);
	if (!m_renderingContext)
	{
		throw std::runtime_error(SDL_GetError());
	}
}

GraphicsRenderer::GraphicsRenderer(GraphicsRenderer&& temp) noexcept :
	m_window(temp.m_window), m_renderingContext(temp.m_renderingContext), m_clearColor(temp.m_clearColor)
{
	temp.m_renderingContext = nullptr;
}

GraphicsRenderer::~GraphicsRenderer()
{
	if (SDL_WasInit(SDL_INIT_VIDEO) != 0 && m_renderingContext)
	{
		SDL_DestroyRenderer(m_renderingContext);
		m_renderingContext = nullptr;
	}
}

void GraphicsRenderer::operator=(GraphicsRenderer&& temp) noexcept
{
	m_window = temp.m_window;
	m_renderingContext = temp.m_renderingContext;
	m_clearColor = temp.m_clearColor;
	temp.m_renderingContext = nullptr;
}

void GraphicsRenderer::SetClearColor(SDL_Color color)
{
	m_clearColor = color;
}

void GraphicsRenderer::DrawRect(SDL_FRect rect, SDL_Color color)
{
	if (SDL_SetRenderDrawColor(m_renderingContext, color.r, color.g, color.b, color.a) < 0)
	{
		throw std::runtime_error(SDL_GetError());
	}

	if (SDL_RenderRect(m_renderingContext, &rect) < 0)
	{
		throw std::runtime_error(SDL_GetError());
	}
}

void GraphicsRenderer::DrawFillRect(SDL_FRect rect, SDL_Color color)
{
	if (SDL_SetRenderDrawColor(m_renderingContext, color.r, color.g, color.b, color.a) < 0)
	{
		throw std::runtime_error(SDL_GetError());
	}

	if (SDL_RenderFillRect(m_renderingContext, &rect) < 0)
	{
		throw std::runtime_error(SDL_GetError());
	}
}

void GraphicsRenderer::Clear()
{
	if (SDL_SetRenderDrawColor(m_renderingContext, m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a) < 0)
	{
		throw std::runtime_error(SDL_GetError());
	}

	if (SDL_RenderClear(m_renderingContext) < 0)
	{
		throw std::runtime_error(SDL_GetError());
	}
}

void GraphicsRenderer::Update()
{
	if (SDL_RenderPresent(m_renderingContext) < 0)
	{
		throw std::runtime_error(SDL_GetError());
	}
}

SDL_Color GraphicsRenderer::GetClearColor() const
{
	return m_clearColor;
}
