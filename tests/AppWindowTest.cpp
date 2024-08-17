#include "AppWindow.h"

#include <SDL3/SDL.h>
#include <iostream>
#include <random>
#include <ctime>

// This is a test to ensure that the functionality provided by the application window class works correctly.

int main(int argc, char** argv)
{
	try
	{
		srand((uint32_t)time(nullptr)); // Initialize random engine seed

		if (SDL_Init(SDL_INIT_VIDEO) < 0)
			throw std::runtime_error("Failed to initialize the SDL3 video module");

		std::printf("Testing application window creation...\n");

		const uint16_t WIDTH = (uint16_t)(rand() % 700) + 200, HEIGHT = (uint16_t)(rand() % 700) + 200;
		AppWindow testWindow("Test Window", WIDTH, HEIGHT);

		std::printf("Checking stored application window member data...\n");

		if (testWindow.GetTitle() != "Test Window")
		{
			throw std::runtime_error("Unexpected application window title member value");
		}

		if (testWindow.GetWidth() != WIDTH)
		{
			throw std::runtime_error("Unexpected application window width member value");
		}

		if (testWindow.GetHeight() != HEIGHT)
		{
			throw std::runtime_error("Unexpected application window height member value");
		}
	}
	catch (std::exception& e)
	{
		std::printf("%s\n", e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
