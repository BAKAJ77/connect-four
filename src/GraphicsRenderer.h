#ifndef GRAPHICS_RENDERER_H
#define GRAPHICS_RENDERER_H

#include <SDL3/SDL.h>

class GraphicsRenderer
{
public:
	GraphicsRenderer();

    /**
     * @brief Creates a rendering context for the window frame provided.
     * @param[in] frame The window frame to create a rendering context for.
     */
	GraphicsRenderer(SDL_Window* window);

    GraphicsRenderer(const GraphicsRenderer&) = delete;
    GraphicsRenderer(GraphicsRenderer&& temp) noexcept;

	~GraphicsRenderer();

    void operator=(const GraphicsRenderer&) = delete;
    void operator=(GraphicsRenderer&& temp) noexcept;

    /**
     * @brief Sets the color which will be used when clearing the back render buffer.
     * @param[in] color The color to be used when clearing.
     */
    void SetClearColor(SDL_Color color);

    /**
     * @brief Draws a rectangle of specified position, size, and color, onto the back render buffer.
     * @param[in] rect The position and size of the rectangle.
     * @param[in] color The color of the rectangle.
     */
    void DrawRect(SDL_FRect rect, SDL_Color color);

    /**
     * @brief Draws a filled rectangle of specified position, size, and color, onto the back render buffer.
     * @param[in] rect The position and size of the rectangle.
     * @param[in] color The color of the rectangle.
     */
    void DrawFillRect(SDL_FRect rect, SDL_Color color);

    /**
     * @brief Clears the back render buffer and fills it with the current set clear color.
     */
    void Clear();

    /**
     * @brief Swaps the front and back render buffers.
     */
    void Update();

    /**
     * @brief Gets the current set renderer clear color.
     * @return The current assigned clear color.
     */
    SDL_Color GetClearColor() const;
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderingContext;
    SDL_Color m_clearColor;
};

#endif