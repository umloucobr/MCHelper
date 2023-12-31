#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib> 
#include <filesystem>

namespace MCHelper {
	class Setup {
	private:
		std::string MCLauncher_path{};
		void copyLauncher(); //gets launcher from the path on .config_file.json and copy it.
		void createProfilesFolder();
	public:
		Setup(std::string MCLauncher_path);
	};
}