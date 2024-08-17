#include "Config.h"
#include "ConfigHandler.h"

#include <SDL3/SDL.h>
#include <iostream>
#include <random>
#include <ctime>

// This is a test to ensure that the attribute value modification, loading from file, and writing to file mechanisms work correctly. 

int main(int argc, char** argv)
{
	try
	{
		srand((uint32_t)time(nullptr)); // Init random engine seed
		const std::filesystem::path FILE_PATH = CF_PROJECT_DIR + std::string("/tests/TestConfig.json");

		// Generate random attribute values
		const int attrib1Values[4] = { rand(), rand(), rand(), rand() };
		const float attrib2Value = (float)(rand() % 100) / (float)(rand() % 100);
		const bool attrib3Value = (bool)(rand() % 1);
		std::string attrib4Value;
		
		for (int i = 0; i < rand() % 15; i++)
		{
			attrib4Value.push_back((rand() % 25) + 97); // Push random ascii chars between 'a' to 'z'
		}

		std::printf("Testing JSON attibutes value assignment and file writing...\n");

		ConfigHandler testConfig;
		testConfig.SetAttribute("attrib1", attrib1Values);
		testConfig.SetAttribute("attrib2", attrib2Value);
		testConfig.SetAttribute("attrib3", attrib3Value);
		testConfig.SetAttribute("attrib4", attrib4Value);
		testConfig.WriteToFile(FILE_PATH); // Write JSON attributes to file

		std::printf("Testing JSON file loading...\n");

		if (!testConfig.LoadFromFile(FILE_PATH)) // Attempt to load the same file
		{
			throw std::runtime_error("Failed to load the test JSON configuration file");
		}

		// Check that the values loaded are correct
		std::printf("Checking values of loaded JSON attributes...\n");

		for (int i = 0; i < 4; i++)
		{
			if (testConfig.GetAttribute("attrib1")[i].get<int>() != attrib1Values[i])
			{
				throw std::runtime_error("Unexpected array values for attribute 1");
			}
		}

		if (testConfig.GetAttribute("attrib2").get<float>() != attrib2Value)
		{
			throw std::runtime_error("Unexpected value for attribute 2");
		}

		if (testConfig.GetAttribute("attrib3").get<bool>() != attrib3Value)
		{
			throw std::runtime_error("Unexpected value for attribute 3");
		}

		if (testConfig.GetAttribute("attrib4").get<std::string>() != attrib4Value)
		{
			throw std::runtime_error("Unexpected value for attribute 4");
		}
	}
	catch (std::exception& e)
	{
		std::printf("%s\n", e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
