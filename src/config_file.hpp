#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include "../include/json/json.hpp"

namespace MCHelper {
	class ConfigFile {
	private:
		nlohmann::json jsonData;
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
		void addProfile(const std::string& profile_name, const std::string& profile_version);

		void editConfigFile(const std::string& file_name, const std::string& key_to_edit, const std::string& key_to_edit2, const bool& new_value);
		void editConfigFile(const std::string& file_name, const std::string& key_to_edit, const std::string& key_to_edit2, const int& new_value);
		void editConfigFile(const std::string& file_name, const std::string& key_to_edit, const std::string& key_to_edit2, const std::string& new_value);
		void addConfigFile(const std::string& file_name, const std::string& key_to_edit, const std::string& key_to_edit2, const nlohmann::json& new_value);
	};
}