#include <iostream>
#include <filesystem>
#include "config_file.hpp"
#include "setup.hpp"

int main() {
	//setup part
	MCHelper::ConfigFile config_file;
	config_file.openAndLoadFile(".config_file.json");

	//if setup wasn't already done, do it.
	if (!config_file.getConfigWasGenerated()) {
		std::cout << "Initializing setup...\n";

		//copies MinecraftLauncher.exe on this folder, and executes it to generate .minecraft.
		MCHelper::Setup setup(config_file.getMCLauncherPath());

		//change config file for further uses.
		//the last three options are, in order: isBool, isInt and isString.
		config_file.editConfigFile(".config_file.json", "config", "configWasGenerated", true);
	}

	return 0;
}