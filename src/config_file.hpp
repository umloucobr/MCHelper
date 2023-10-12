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
		bool folderWasGenerated{};

		void createFile(const std::string& file_name);
		void loadDefaultConfig(std::ofstream& file);
	public:
		ConfigFile();
		void openFile(const std::string& file_name);
	};
}