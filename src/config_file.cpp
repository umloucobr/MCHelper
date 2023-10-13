#include "config_file.hpp"
#include <iostream>

namespace MCHelper {
	ConfigFile::ConfigFile() {
		std::cout << "Looking for config file...\n";
		if (std::filesystem::exists(".config_file.json")) {
			std::cout << "Config file found! Welcome back.\n";
		}
		else {
			std::cout << "Config file not found. Creating a new one.\n";
			createFile(".config_file.json"); //create AND load default configs.
		}
	}

	void ConfigFile::openAndLoadFile(const std::string& file_name) {
		std::ifstream file {ifstreamFile(file_name)};

		file >> jsonData;
		MCLauncher_path = jsonData["config"]["MCLauncherPath"];
		configWasGenerated = jsonData["config"]["configWasGenerated"];
	}

	/*
	EDIT CONFIG FILE, 3 OVERLOADS, IN ORDER.
	bool.
	int.
	std::string.
	*/
	void ConfigFile::editConfigFile(const std::string& file_name, const std::string& key_to_edit, const std::string& key_to_edit2, const bool& new_value) {
		//get and load the file.
		std::fstream fstream_file {fstreamFile(file_name)};
		nlohmann::json tempJsonData;

		fstream_file >> tempJsonData;

		//here, if key_to_edit2 is null (no nested JSON object) we only use key_to_edit.
		if (key_to_edit2 == "") {
			tempJsonData[key_to_edit] = new_value;
		}
		else {
			tempJsonData[key_to_edit][key_to_edit2] = new_value;
		}

		fstream_file.seekp(0);
		fstream_file << tempJsonData.dump(4); //4 = pretty print.
	}

	//int.
	void ConfigFile::editConfigFile(const std::string& file_name, const std::string& key_to_edit, const std::string& key_to_edit2, const int& new_value) {
		std::fstream fstream_file {fstreamFile(file_name)};
		nlohmann::json tempJsonData;

		fstream_file >> tempJsonData;

		if (key_to_edit2 == "") {
			tempJsonData[key_to_edit] = new_value;
		}
		else {
			tempJsonData[key_to_edit][key_to_edit2] = new_value;
		}

		fstream_file << tempJsonData.dump(4);
	}

	//std::string.
	void ConfigFile::editConfigFile(const std::string& file_name, const std::string& key_to_edit, const std::string& key_to_edit2, const std::string& new_value) {
		std::fstream fstream_file {fstreamFile(file_name)};
		nlohmann::json tempJsonData;

		fstream_file >> tempJsonData;

		if (key_to_edit2 == "") {
			tempJsonData[key_to_edit] = new_value;
		}
		else {
			tempJsonData[key_to_edit][key_to_edit2] = new_value;
		}

		fstream_file << tempJsonData.dump(4);
	}
	//END OF EDIT.
	//END OF EDIT.
	//END OF EDIT.
	//END OF EDIT.

	std::string ConfigFile::getMCLauncherPath() {
		return MCLauncher_path;
	}

	bool ConfigFile::getConfigWasGenerated() {
		return configWasGenerated;
	}

	//creates a new file if the user doesn't have one.
	void ConfigFile::createFile(const std::string& file_name) {
			std::ofstream file {ofstreamFile(file_name)};
			loadDefaultConfig(file);
	}

	void ConfigFile::loadDefaultConfig(std::ofstream& file) {
		nlohmann::json data; //the main JSON object.

		//comments for the user, because JSON does not officially supports comments.
		data["comments"] = "File generated automatically, do NOT change anything unless you know what you are doing.";

		nlohmann::json config; //the config JSON object.
		config["MCLauncherPath"] = "C:/Program Files (x86)/Minecraft Launcher/MinecraftLauncher.exe";
		config["configWasGenerated"] = false;
		data["config"] = config;

		nlohmann::json profiles; //the minecraft profiles.
		data["profiles"] = profiles;

		file << data.dump(4); //4 = pretty print.
	}

	std::ifstream ConfigFile::ifstreamFile(const std::string& file_name) {
		try {
			std::ifstream file {file_name};

			if (file.is_open()) {
				return file;
			}
			else {
				throw std::runtime_error("Failed to open file CongfigFile::ifstreamFile().");
			}
		}
		catch (const std::exception& e) {
			std::cerr << "Failed to open file CongfigFile::ifstreamFile().\n";
			std::cerr << e.what();
			std::exit(EXIT_FAILURE);
		}
	}

	std::ofstream ConfigFile::ofstreamFile(const std::string& file_name) {
		try {
			std::ofstream file {file_name};

			if (file.is_open()) {
				return file;
			}
			else {
				throw std::runtime_error("Failed to open file CongfigFile::ofstreamFile().");
			}
		}
		catch (const std::exception& e) {
			std::cerr << "Failed to open file CongfigFile::ofstreamFile().\n";
			std::cerr << e.what();
			std::exit(EXIT_FAILURE);
		}
	}

	std::fstream ConfigFile::fstreamFile(const std::string& file_name) {
		try {
			std::fstream file {file_name, std::ios::in | std::ios::out };

			if (file.is_open()) {
				return file;
			}
			else {
				throw std::runtime_error("Failed to open file CongfigFile::fstreamFile().");
			}
		}
		catch (const std::exception& e) {
			std::cerr << "Failed to open file CongfigFile::fstreamFile().\n";
			std::cerr << e.what();
			std::exit(EXIT_FAILURE);
		}
	}
}