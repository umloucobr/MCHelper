#pragma once
#include <iostream>
#include "config_file.hpp"

namespace MCHelper {
	class Launcher {
	private:
	public:
		static void executeLauncher();
		void addProfile(ConfigFile& config_file, const std::string& profile_name, const std::string& profile_version);
	};
}