#include "config_file.hpp"
#include <iostream>

namespace MCHelper {
    ConfigFile::ConfigFile() {
        std::cout << "Looking for config file...\n";
        if (std::filesystem::exists(".config_file.json")) {
            std::cout << "Config file found! Welcome back.\n";
        }
        else {
            std::cout << "Config file not found. Creating a new on.\n";
            createFile(".config_file.json"); //create AND load default configs.
        }
    }

    void ConfigFile::openFile(const std::string& file_name) {
        try {
            std::ifstream file {file_name};

            if (file.is_open()) {
                file >> jsonData;
                MCLauncher_path = jsonData["config"]["MCLauncherPath"];
                folderWasGenerated = jsonData["config"]["folderWasGenerated"];
            }
            else {
                throw std::runtime_error("Failed to open file.");
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Failed to open the file.\n";
            std::cerr << e.what();
            std::exit(EXIT_FAILURE);
        }
    }

    std::string ConfigFile::getMCLauncherPath() {
        return MCLauncher_path;
    }

    bool ConfigFile::getFolderWasGenerated() {
        return folderWasGenerated;
    }

    //creates a new file if the user doesn't have one.
	void ConfigFile::createFile(const std::string& file_name) {
        try {
            std::ofstream file{file_name};
            if (file.is_open()) {
                loadDefaultConfig(file);
            }
            else {
                throw std::runtime_error("Failed to create the file.");
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Failed to create the file.\n";
            std::cerr << e.what();
            std::exit(EXIT_FAILURE);
        }
	}

    void ConfigFile::loadDefaultConfig(std::ofstream& file) {
        nlohmann::json data; //the main JSON object.

        //comments for the user, because JSON does not officially supports comments.
        data["comments"] = "File generated automatically, do NOT change anything unless you know what you are doing.";

        nlohmann::json config; //the config JSON object.
        config["MCLauncherPath"] = "C:/Program Files (x86)/Minecraft Launcher/MinecraftLauncher.exe";
        config["folderWasGenerated"] = false;
        data["config"] = config;

        nlohmann::json profiles; //the minecraft profiles.
        data["profiles"] = profiles;

        file << data.dump(4); //4 = pretty print.
    }
}