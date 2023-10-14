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

	/*
	*  PRIVATE:
	*/

	void ConfigFile::openAndLoadFile(const std::string& file_name) {
		std::ifstream file {ifstreamFile(file_name)};
		nlohmann::json jsonData;

		file >> jsonData;
		MCLauncher_path = jsonData["config"]["MCLauncherPath"];
		configWasGenerated = jsonData["config"]["configWasGenerated"];
	}


	std::ifstream ConfigFile::ifstreamFile(const std::string& file_name) {
		try {
			std::ifstream file{ file_name };

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
			std::ofstream file {file_name, std::ios::trunc};

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
			std::fstream file{ file_name, std::ios::in | std::ios::out};

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

	//creates a new file if the user doesn't have one.
	void ConfigFile::createFile(const std::string& file_name) {
		std::ofstream file{ ofstreamFile(file_name) };
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

	/*
	* PUBLIC:
	*/

	/*
	EDIT CONFIG FILE, 3 OVERLOADS, IN ORDER.
	bool.
	int.
	std::string.
	nlohmann::json. this one adds.
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

		fstream_file.seekp(0);
		fstream_file << tempJsonData.dump(4);
	}

	//std::string.
	void ConfigFile::editConfigFile(const std::string& file_name, const std::string& key_to_edit, const std::string& key_to_edit2, const std::string& new_value) {
		std::fstream fstream_file {fstreamFile(file_name)};
		nlohmann::json tempJsonData;

		fstream_file >> tempJsonData;

		if (key_to_edit2 == "") {
			tempJsonData[key_to_edit].emplace_back(new_value);
		}
		else {
			tempJsonData[key_to_edit][key_to_edit2] = new_value;
		}

		fstream_file.seekp(0);
		fstream_file << tempJsonData.dump(4);
	}

	//nlohmann::json.
	void ConfigFile::addToConfigFile(const std::string& file_name, const std::string& key_to_edit, const std::string& key_to_edit2, const nlohmann::json& new_value) {
		std::fstream fstream_file {fstreamFile(file_name)};
		nlohmann::json tempJsonData;

		fstream_file >> tempJsonData;

		if (key_to_edit2 == "") {
			for (const auto& [key, value] : new_value.items()) { //if you use emplace_back() it gives square brackets in the "profiles"
				tempJsonData[key_to_edit][key] = value;			 //JSON object.
			}
		}
		else {
			for (const auto& [key, value] : new_value.items()) {
				tempJsonData[key_to_edit][key_to_edit2][key] = value;
			}
		}

		fstream_file.seekp(0);
		fstream_file << tempJsonData.dump(4);
	}

	//END OF EDIT.
	//END OF EDIT.
	//END OF EDIT.
	//END OF EDIT.

	void ConfigFile::addProfile(const std::string& profile_name, const std::string& profile_version) {
		nlohmann::json profile{
		{"created", "1970-01-02T00:00:00.000Z"},
		{"icon", "Furnace"},
		{"lastUsed", "1970-01-02T00:00:00.000Z"},
		{"lastVersionId", profile_version},
		{"name", profile_name},
		{"type", "custom"}
		};

		nlohmann::json profiles;
		profiles[profile_name] = profile;

		addToConfigFile(".config_file.json", "profiles", "", profiles);
	}

	void ConfigFile::removeProfile(const std::string& profile_name) {
		std::ifstream ifstream_file {ifstreamFile(".config_file.json")};
		nlohmann::json tempJsonData;

		ifstream_file >> tempJsonData;
		tempJsonData["profiles"].erase(profile_name);

		std::ofstream ofstream_file {ofstreamFile(".config_file.json")}; //can't use std::fstream because we need the flag std::ios::trunc,
		ofstream_file << tempJsonData.dump(4);								//only availible in the std::ofstream function.
	}

	nlohmann::json ConfigFile::getJsonObject(const std::string& json_object) {
		std::ifstream ifstream_file {ifstreamFile(".config_file.json")};
		nlohmann::json jsonData;

		ifstream_file >> jsonData;
		return jsonData[json_object];
	}
	nlohmann::json ConfigFile::getJsonObject(const std::string& json_object, const std::string& json_object2) {
		std::ifstream ifstream_file {ifstreamFile(".config_file.json")};
		nlohmann::json jsonData;

		ifstream_file >> jsonData;
		return jsonData[json_object][json_object2];
	}
	nlohmann::json ConfigFile::getJsonObject(const std::string& json_object, const std::string& json_object2, const std::string& json_object3) {
		std::ifstream ifstream_file {ifstreamFile(".config_file.json")};
		nlohmann::json jsonData;

		ifstream_file >> jsonData;
		return jsonData[json_object][json_object2][json_object3];
	}

	std::string ConfigFile::getMCLauncherPath() {
		return MCLauncher_path;
	}

	bool ConfigFile::getConfigWasGenerated() {
		return configWasGenerated;
	}
}