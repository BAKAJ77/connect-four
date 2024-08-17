#ifndef CONFIG_HANDLER_H
#define CONFIG_HANDLER_H

#include <filesystem>
#include <nlohmann/json.hpp>

class ConfigHandler
{
public:
	ConfigHandler() = default;

	/**
	 * @brief Loads the JSON config file at the specified path.
	 * @param[in] filePath The JSON config file path.
	 */
	ConfigHandler(const std::filesystem::path& filePath);

	~ConfigHandler();

	/**
	 * @brief Loads the JSON config file at the specified path.
	 * @param[in] filePath The JSON config file path.
	 * 
	 * @return True if successful, otherwise False is returned.
	 */
	bool LoadFromFile(const std::filesystem::path& filePath);

	/**
	 * @brief Writes the stored JSON config data to file at the specified path.
	 * @param[in] filePath The JSON config file path.
	 */
	void WriteToFile(const std::filesystem::path& filePath);
	
	/**
	 * @brief Sets the value of the JSON config setting attribute.
	 * 
	 * @param[in] id The ID of the attribute.
	 * @param[in] value The value to be assigned to the attribute.
	 */
	void SetAttribute(std::string_view id, nlohmann::json value);

	/**
	 * @brief Gets the value of the specified JSON config setting attribute.
	 * 
	 * @param[in] id The ID of the attribute.
	 * @return The value assigned to the specified attribute.
	 */
	nlohmann::json GetAttribute(std::string_view id) const;
private:
	nlohmann::json m_root;
	std::filesystem::path m_filePath;
};

#endif