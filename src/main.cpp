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
	launcher.addProfile(config_file, "hi", "1.20.1");
	launcher.addProfile(config_file, "test", "1.20");
	launcher.addProfile(config_file, "a", "1.19");
	launcher.addProfile(config_file, "b", "1.18");
	return 0;
}