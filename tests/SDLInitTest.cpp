#include <SDL3/SDL.h>
#include <iostream>

// This is a test to ensure that the SDL3 modules required initialize correctly.

int main(int argc, char** argv)
{
	try
	{
		std::printf("Testing SDL3 Video module initialisation...\n");

		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			throw std::runtime_error("Failed to initialize the SDL3 video module");
		}
	}
	catch (std::exception& e)
	{
		std::printf("%s\n", e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
