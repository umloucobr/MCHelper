#include <iostream>
#include <filesystem>
#include "config_file.hpp"
#include "setup.hpp"
#include "launcher.hpp"

int main() {
	//setup part
	MCHelper::Launcher launcher;
	MCHelper::ConfigFile config_file;
	config_file.openAndLoadFile(".config_file.json");

	//if setup wasn't already done, do it.
	if (!config_file.getConfigWasGenerated()) {
		std::cout << "Initializing setup...\n";

		//copies MinecraftLauncher.exe on this folder, executes it to generate .minecraft, creates the "profiles" folder.
		MCHelper::Setup setup(config_file.getMCLauncherPath());

		//change config file for further uses.
		//the last three options are, in order: isBool, isInt and isString.
		config_file.editConfigFile(".config_file.json", "config", "configWasGenerated", true);
	}

	//user input, add and get profiles, open minecraft.
	config_file.addProfile("hi", "1.20.1");
	config_file.addProfile("test", "1.20");
	config_file.addProfile("a", "1.19");
	config_file.addProfile("b", "1.18");
	std::cout << std::setw(4) << config_file.getJsonObject("profiles");
	config_file.removeProfile("test");
	return 0;
}