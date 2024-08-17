#include <iostream>
#include <SDL3/SDL.h>

#ifdef CF_WIN64
#ifdef CF_DEBUG_MODE
int main(int argc, char** argv)
#else
#include <Windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow)
#endif
#else
int main(int argc, char** argv)
#endif
{
	try
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0) // Initialize the SDL video subsystem
		{
			throw std::runtime_error(SDL_GetError());
		}

		SDL_Quit();
	}
	catch (std::exception& e)
	{
		std::printf("%s\n", e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
