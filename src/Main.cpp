#include "AppWindow.h"
#include "ConfigHandler.h"

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
		// Initialize the JSON configuration handler
		const std::filesystem::path CONFIG_FILE_PATH = "ConfigSettings.json";
		ConfigHandler jsonConfigFile;

		if (!std::filesystem::exists(CONFIG_FILE_PATH)) // Default config setting values
		{
			jsonConfigFile.SetAttribute("windowResolution", { 800, 800 });
			jsonConfigFile.SetAttribute("gridDimensions", { 7, 6 });
			jsonConfigFile.SetAttribute("winningRowLength", 4);
			jsonConfigFile.WriteToFile(CONFIG_FILE_PATH);
		}
		else // Load the config setting values from existing file
		{
			jsonConfigFile.LoadFromFile(CONFIG_FILE_PATH);
		}

		if (SDL_Init(SDL_INIT_VIDEO) < 0) // Initialize the SDL video subsystem
		{
			throw std::runtime_error(SDL_GetError());
		}

		// Create the application window
		AppWindow applicationWindow("Connect Four", jsonConfigFile.GetAttribute("windowResolution")[0].get<uint16_t>(),
			jsonConfigFile.GetAttribute("windowResolution")[1].get<uint16_t>());

		GraphicsRenderer& renderer = applicationWindow.GetRenderer();

		bool shouldTerminate = false;
		while (!shouldTerminate) // The main game loop
		{
			SDL_Event event;
			while (applicationWindow.GetNextEvent(&event)) // Process each pending event
			{
				if (event.type == SDL_EVENT_QUIT)
					shouldTerminate = true;
			}

			renderer.Clear();

			renderer.DrawFillRect({ 10, 10, 100, 100 }, { 255, 0, 0, 255 });

			renderer.Update();
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
