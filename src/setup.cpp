#include "setup.hpp"
#include "launcher.hpp"

namespace MCHelper {
	Setup::Setup(std::string MCLauncher_path) {
		this->MCLauncher_path = MCLauncher_path;
		copyLauncher();
		Launcher::executeLauncher();
	}

	void Setup::copyLauncher() {
		try {
			std::ifstream source_file(MCLauncher_path, std::ios::binary);

			if (!source_file.is_open()) {
				throw std::runtime_error("Failed to open SOURCE file (launcher).");
			}

			std::ofstream destination_file("MinecraftLauncher.exe", std::ios::binary);

			if (!destination_file.is_open()) {
				throw std::runtime_error("Failed to write DESTINATION file (launcher).");
			}

			destination_file << source_file.rdbuf();
		}
		catch (const std::exception& e) {
			std::cerr << "Failed setup part.\n";
			std::cout << e.what();
			std::exit(EXIT_FAILURE);
		}
	}
}