#include "setup.hpp"
#include "launcher.hpp"

namespace MCHelper {
	Setup::Setup(std::string MCLauncher_path) {
		/*Here the setup is being made.
		1-Launcher is copied in the folder.
		2-Launcher is executed, so .minecraft is generated
		*/
		this->MCLauncher_path = MCLauncher_path;
		copyLauncher();
		std::cout << "WARNING: CLOSE THE LAUNCHER AFTER IT OPENS.\n";
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