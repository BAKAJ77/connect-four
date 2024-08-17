#include "GameGrid.h"

constexpr float GRID_SPACING = 25.0f, GRID_HOLE_SCALE = 75.0f;
constexpr float GLOBAL_PADDING = 25.0f, PADDING_TOP = (GLOBAL_PADDING * 2) + GRID_HOLE_SCALE;

GameGrid::GameGrid() :
	m_columns(0), m_rows(0), m_window(nullptr), m_scalingX(1.0f), m_scalingY(1.0f), m_hoveredColumn(nullptr), m_currentPlayer(1)
{}

GameGrid::GameGrid(AppWindow& window, uint8_t columns, uint8_t rows) :
	m_columns(columns), m_rows(rows), m_window(&window), m_hoveredColumn(nullptr), m_currentPlayer(1)
{
	// Initialize the game grid
	m_grid.resize(columns, std::vector<uint8_t>((size_t)rows, 0));
	
	// Calculate the scaling required to scale the game grid scene to the size of the window
	const float requiredGridWidth = (GRID_SPACING * (columns + 1)) + (columns * GRID_HOLE_SCALE);
	const float requiredGridHeight = (GRID_SPACING * (rows + 1)) + (rows * GRID_HOLE_SCALE);

	m_scalingX = (float)window.GetWidth() / (requiredGridWidth + (GLOBAL_PADDING * 2.0f));
	m_scalingY = (float)window.GetHeight() / (requiredGridHeight + (GLOBAL_PADDING + PADDING_TOP));

	// Initialize each grid column button
	m_columnButtons.reserve(columns);
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
	for (auto revIt = gridColumn.rbegin(); revIt != gridColumn.rend(); revIt++)
	{
		if (*revIt == 0) // Empty grid found?
		{
			*revIt = m_currentPlayer; // Place the current player's counter in the empty grid
			m_currentPlayer = std::max((m_currentPlayer + 1) % 3, 1); // Ensures that the current player value is always either 1 or 2 
			break;
		}
	}
}

void GameGrid::ResetGrid()
{
	for (size_t i = 0; i < m_columns * m_rows; i++)
	{
		m_grid[i % m_columns][(size_t)(i / m_columns)] = 0;
	}
}

void GameGrid::Update()
{
	m_hoveredColumn = nullptr;
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

