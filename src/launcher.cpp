#include "launcher.hpp"

namespace MCHelper {
	void Launcher::executeLauncher() {
		try {
			int exit_code {std::system("MinecraftLauncher.exe --workDir=.")};
			if (exit_code != 0) {
				throw std::runtime_error("Can't execute Minecraft Launcher.");
			}
		}
		catch (const std::exception& e) {
			std::cerr << "Can't execute Minecraft Launcher.\n";
			std::cerr << e.what();
			std::exit(EXIT_FAILURE);
		}
	}
}