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

/* example of profile.
"b5a696697b6e6e568de8b6347241e85c" : {
      "created" : "1970-01-02T00:00:00.000Z",
      "icon" : "Grass",
      "lastUsed" : "1970-01-02T00:00:00.000Z",
      "lastVersionId" : "latest-release",
      "name" : "",
      "type" : "latest-release"
    }*/