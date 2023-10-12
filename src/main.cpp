#include <iostream>
#include <filesystem>
#include "config_file.hpp"

int main() {
	//setup part
	MCHelper::ConfigFile config_file;
	config_file.openFile(".config_file.json");

	return 0;
}