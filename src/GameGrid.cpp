#include "GameGrid.h"
#include <algorithm>

constexpr float GRID_SPACING = 25.0f, GRID_HOLE_SCALE = 75.0f;
constexpr float GLOBAL_PADDING = 25.0f, PADDING_TOP = (GLOBAL_PADDING * 2) + GRID_HOLE_SCALE;

GameGrid::GameGrid() :
	m_columns(0), m_rows(0), m_window(nullptr), m_scalingX(1.0f), m_scalingY(1.0f), m_hoveredColumn(nullptr), m_currentPlayer(1),
	m_winningRowLength(0), m_currentGameCompleted(false)
{}

GameGrid::GameGrid(AppWindow& window, uint8_t columns, uint8_t rows, uint8_t winningRowLength) :
	m_window(&window), m_hoveredColumn(nullptr), m_currentPlayer(1), m_currentGameCompleted(false)
{
	// Enforce constraints
	// Min columns/rows: 5
	// Max columns/rows: 10
	// Min winning row length requirement: 3
	// Max winning row length requirement: 6
	constexpr uint8_t MIN_COLUMNS_ROWS = 5, MAX_COLUMNS_ROWS = 10;
	constexpr uint8_t MIN_WINNING_ROW_LENGTH = 3, MAX_WINNING_ROW_LENGTH = 6;

	m_columns = std::clamp(columns, MIN_COLUMNS_ROWS, MAX_COLUMNS_ROWS);
	m_rows = std::clamp(rows, MIN_COLUMNS_ROWS, MAX_COLUMNS_ROWS);
	m_winningRowLength = std::clamp(winningRowLength, MIN_WINNING_ROW_LENGTH, MAX_WINNING_ROW_LENGTH);

	// Initialize the game grid
	m_grid.resize(m_columns, std::vector<uint8_t>((size_t)m_rows, 0));
	
	// Calculate the scaling required to scale the game grid scene to the size of the window
	const float requiredGridWidth = (GRID_SPACING * (m_columns + 1)) + (m_columns * GRID_HOLE_SCALE);
	const float requiredGridHeight = (GRID_SPACING * (m_rows + 1)) + (m_rows * GRID_HOLE_SCALE);

	m_scalingX = (float)window.GetWidth() / (requiredGridWidth + (GLOBAL_PADDING * 2.0f));
	m_scalingY = (float)window.GetHeight() / (requiredGridHeight + (GLOBAL_PADDING + PADDING_TOP));

	// Initialize each grid column button
	m_columnButtons.reserve(m_columns);
	for (uint8_t i = 0; i < m_columns; i++)
	{
		SDL_FRect bounds;
		bounds.x = (((GRID_SPACING / 2 ) + GLOBAL_PADDING + (i * (GRID_SPACING + GRID_HOLE_SCALE))) * m_scalingX);
		bounds.y = PADDING_TOP * m_scalingY;
		bounds.w = (GRID_HOLE_SCALE + GRID_SPACING) * m_scalingX;
		bounds.h = (float)m_window->GetHeight() - ((GLOBAL_PADDING + PADDING_TOP) * m_scalingY);

		m_columnButtons.push_back(Button(bounds));
	}
}

void GameGrid::PlacePlayerCounter(int column)
{
	std::vector<uint8_t>& gridColumn = m_grid[column];

	// Iterate from the bottom of the column to the top
	for (int i = (int)(m_rows - 1); i >= 0; i--)
	{
		uint8_t& gridValue = m_grid[column][i];
		if (gridValue == 0) // Empty grid found?
		{
			gridValue = m_currentPlayer; // Place the current player's counter in the empty grid
			m_currentGameCompleted = this->CheckIfPlayerWon(m_currentPlayer, i, column);
			m_currentPlayer = std::max((m_currentPlayer + 1) % 3, 1); // Ensures that the current player value is always either 1 or 2 
			break;
		}
	}
}

bool GameGrid::CheckIfPlayerWon(uint8_t currentPlayer, int row, int column)
{
	int numConsecutiveCounters = 0;

	// Check vertically
	for (const uint8_t& gridValue : m_grid[column])
	{
		gridValue == currentPlayer ? numConsecutiveCounters++ : numConsecutiveCounters = 0;
		if (numConsecutiveCounters == m_winningRowLength)
		{
			return true;
		}
	}

	numConsecutiveCounters = 0;

	// Check horizontally
	for (const auto& gridColumn : m_grid)
	{
		gridColumn[row] == currentPlayer ? numConsecutiveCounters++ : numConsecutiveCounters = 0;
		if (numConsecutiveCounters == m_winningRowLength)
		{
			return true;
		}
	}

	numConsecutiveCounters = 0;

	// Check diagonally (top-left to bottom-right)
	int gridPosX = 0, gridPosY = 0;
	column > row ? gridPosX = (column - row) : gridPosY = (row - column); // Find the furtherest top-left point to start the diagonal check from

	for (; gridPosX < m_columns && gridPosY < m_rows;)
	{
		m_grid[gridPosX][gridPosY] == currentPlayer ? numConsecutiveCounters++ : numConsecutiveCounters = 0;
		if (numConsecutiveCounters == m_winningRowLength)
		{
			return true;
		}

		gridPosX++;
		gridPosY++;
	}

	numConsecutiveCounters = 0;

	// Check diagonally (bottom-left to top-right)
	gridPosX = 0, gridPosY = m_rows - 1;
	((m_rows - 1) - row) > column ? gridPosY = (row + column) : gridPosX = (column - ((m_rows - 1) - row)); // Find the furtherest bottom-left point to start the diagonal check from

	for (; gridPosX < m_columns && gridPosY > 0;)
	{
		m_grid[gridPosX][gridPosY] == currentPlayer ? numConsecutiveCounters++ : numConsecutiveCounters = 0;
		if (numConsecutiveCounters == m_winningRowLength)
		{
			return true;
		}

		gridPosX++;
		gridPosY--;
	}

	return false;
}

void GameGrid::ResetGrid()
{
	for (size_t i = 0; i < (size_t)(m_columns * m_rows); i++)
	{
		m_grid[i % m_columns][(size_t)(i / m_columns)] = 0;
	}

	m_currentGameCompleted = false;
}

void GameGrid::Update()
{
	m_hoveredColumn = nullptr; // Reset current hovered column pointer back to null

	if (!m_currentGameCompleted) // Only bother updating if there is no winner for the current game yet
	{
		for (size_t i = 0; i < m_columnButtons.size(); i++)
		{
			Button& button = m_columnButtons[i];
			button.Update(*m_window);

			if (button.IsHovering())
			{
				m_hoveredColumn = &button; // Set as the current hovered column
			}

			if (button.IsPressed())
			{
				this->PlacePlayerCounter(i);
			}
		}
	}
}

void GameGrid::Draw(GraphicsRenderer& renderer) const
{
	// Draw blue grid background
	renderer.DrawFillRect({ GLOBAL_PADDING * m_scalingX, PADDING_TOP * m_scalingY, 
		(float)m_window->GetWidth() - ((GLOBAL_PADDING * 2) * m_scalingX), 
		(float)m_window->GetHeight() - ((GLOBAL_PADDING + PADDING_TOP) * m_scalingY) }, { 0, 103, 208, 255 });

	// Render pending current player counter over the grid column that's being hovered on
	if (m_hoveredColumn)
	{
		SDL_Color counterColor = m_currentPlayer == 1 ? SDL_Color({ 255, 0, 0, 255 }) : SDL_Color({ 255, 255, 0, 255 });

		const SDL_FRect hoveredColumnBounds = m_hoveredColumn->GetBounds();
		renderer.DrawFillRect({ (hoveredColumnBounds.x + (GRID_SPACING / 2) * m_scalingX), GLOBAL_PADDING * m_scalingY, 
			GRID_HOLE_SCALE * m_scalingX, GRID_HOLE_SCALE * m_scalingY }, counterColor);
	}

	// Render each grid hole
	for (int i = 0; i < m_columns * m_rows; i++)
	{
		// Figure out the color of the grid hole
		const uint8_t gridValue = m_grid[i % m_columns][(size_t)(i / m_columns)];
		SDL_Color gridColor = { 0, 0, 0, 0 };

		if (gridValue == 0) // Grid is empty
		{
			gridColor = { 50, 50, 50, 255 };
		}
		else if (gridValue == 1) // Player 1 is red counter
		{
			gridColor = { 255, 0, 0, 255 };
		}
		else if (gridValue == 2) // Player 2 is yellow counter
		{
			gridColor = { 255, 255, 0, 255 };
		}

		// Calculate the position and scaling of the grid hole
		SDL_FRect rect;
		rect.x = ((GRID_SPACING + GLOBAL_PADDING + ((i % m_columns) * (GRID_SPACING + GRID_HOLE_SCALE))) * m_scalingX);
		rect.y = ((GRID_SPACING + PADDING_TOP + ((int)(i / m_columns) * (GRID_SPACING + GRID_HOLE_SCALE))) * m_scalingY);
		rect.w = GRID_HOLE_SCALE * m_scalingX;
		rect.h = GRID_HOLE_SCALE * m_scalingY;

		renderer.DrawFillRect(rect, gridColor);
	}
}