#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include "../include/json/json.hpp"

namespace MCHelper {
	class ConfigFile {
	private:
		std::string MCLauncher_path{};
		bool configWasGenerated{};

		std::ifstream ifstreamFile(const std::string& file_name);
		std::ofstream ofstreamFile(const std::string& file_name);
		std::fstream fstreamFile(const std::string& file_name);
		void createFile(const std::string& file_name);
		void loadDefaultConfig(std::ofstream& file);
	public:
		ConfigFile();
		void openAndLoadFile(const std::string& file_name);

		std::string getMCLauncherPath();
		bool getConfigWasGenerated();
		nlohmann::json getJsonObject(const std::string& json_object);
		nlohmann::json getJsonObject(const std::string& json_object, const std::string& json_object2);
		nlohmann::json getJsonObject(const std::string& json_object, const std::string& json_object2, const std::string& json_object3);

		void editConfigFile(const std::string& file_name, const std::string& key_to_edit, const std::string& key_to_edit2, const bool& new_value);
		void editConfigFile(const std::string& file_name, const std::string& key_to_edit, const std::string& key_to_edit2, const int& new_value);
		void editConfigFile(const std::string& file_name, const std::string& key_to_edit, const std::string& key_to_edit2, const std::string& new_value);
		void addToConfigFile(const std::string& file_name, const std::string& key_to_edit, const std::string& key_to_edit2, const nlohmann::json& new_value);

		void addProfile(const std::string& profile_name, const std::string& profile_version);
		void removeProfile(const std::string& profile_name);
	};
}