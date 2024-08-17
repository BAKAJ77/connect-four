#ifndef GAME_GRID_H
#define GAME_GRID_H

#include "Button.h"

#include <vector>
#include <memory>

class GameGrid
{
public:
	GameGrid();

	/**
	 * @brief Initializes the game grid.
	 * 
	 * @param[in] window The current application window.
	 * @param[in] columns The amount of columns to set for the game grid.
	 * @param[in] rows The amount of rows to set for the game grid.
	 */
	GameGrid(AppWindow& window, uint8_t columns, uint8_t rows);

	~GameGrid() = default;

	/**
	 * @brief Resets every game grid cell to empty.
	 */
	void ResetGrid();

	/**
	 * @brief Updates the game grid state.
	 */
	void Update();

	/**
	 * @brief Draws the game grid scene.
	 * @param[in] renderer The current graphics renderer.
	 */
	void Draw(GraphicsRenderer& renderer) const;
private:
	/**
	 * @brief Places counter of current player into the specified column (if not full).
	 * Also, the current player value is updated if a counter is placed successfully.
	 * 
	 * @param[in] column The column index to place the counter in.
	 */
	void PlacePlayerCounter(int column);
private:
	uint8_t m_currentPlayer;

	std::vector<std::vector<uint8_t>> m_grid;
	uint8_t m_columns, m_rows;
	AppWindow* m_window;

	std::vector<Button> m_columnButtons;
	float m_scalingX, m_scalingY;
	Button* m_hoveredColumn;
};

#endif