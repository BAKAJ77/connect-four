#include "ConfigHandler.h"
#include <fstream>

ConfigHandler::ConfigHandler(const std::filesystem::path& filePath)
{
	this->LoadFromFile(filePath);
}

ConfigHandler::~ConfigHandler()
{
	this->WriteToFile(m_filePath);
}

bool ConfigHandler::LoadFromFile(const std::filesystem::path& filePath)
{
	if (std::filesystem::exists(filePath))
	{
		std::ifstream file(filePath);
		m_root = nlohmann::json::parse(file);
		m_filePath = filePath;
		return true;
	}

	return false;
}

void ConfigHandler::WriteToFile(const std::filesystem::path& filePath)
{
	std::ofstream file(filePath);
	file << m_root.dump(4);
	m_filePath = filePath;
}

void ConfigHandler::SetAttribute(std::string_view id, nlohmann::json value)
{
	m_root[id.data()] = value;
}

nlohmann::json ConfigHandler::GetAttribute(std::string_view id) const
{
	return m_root[id.data()];
}
