#include <iostream>
#include <filesystem>
#include "config_file.hpp"
#include "setup.hpp"

int main() {
	//setup part
	MCHelper::ConfigFile config_file;
	config_file.openFile(".config_file.json");

	//if setup wasn't already done, do it.
	if (!config_file.getFolderWasGenerated()) {
		std::cout << "Initializing setup\n";
		MCHelper::Setup setup(config_file.getMCLauncherPath());
	}

	return 0;
}