cmake_minimum_required (VERSION 3.8)

project ("MCHelper")

add_executable (MCHelper "main.cpp" "config_file.hpp" "config_file.cpp" "setup.hpp" "setup.cpp" "launcher.cpp" "launcher.hpp" "../include/json/json.hpp" "../include/json/json_fwd.hpp")

set_property (TARGET MCHelper PROPERTY CXX_STANDARD 20)

