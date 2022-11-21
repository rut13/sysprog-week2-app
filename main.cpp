#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <memory>

#include "PluginWrapper.hpp"
#include "IPlugin.hpp"

std::vector<std::string> scan_dir(const std::string& path, const std::string& ext) {
    std::vector<std::string> plugins;
    for (const auto& entry : std::filesystem::directory_iterator {path}) {
        std::string filename {entry.path().string()};
        if (filename.substr(filename.size() - ext.size(), ext.size()) == ext) {
            plugins.push_back(filename);
        }
    }
    return plugins;
}

int main(int argc, char* argv[]) {
    try {
        // (1) scan directory for plugins
        std::vector<std::string> files {scan_dir("plugins", "plug")};

        // (2) open them
        std::vector<sp::PluginWrapper> plugins;
        for (const std::string& file : files) {
            plugins.emplace_back(file);
        }

        // (3) instantiate objects
        using factory = sp::IPlugin*(*)();
        std::vector<std::unique_ptr<sp::IPlugin>> objects;
        for (const sp::PluginWrapper& wrapper : plugins) {
            factory func = reinterpret_cast<factory>(wrapper.lookup("create_instance"));
            objects.emplace_back(func());
        }

        // (4) call methods
        for (const auto& obj : objects) {
            std::cout << obj->name() << ": " << obj->description() << '\n';
        }
    } catch (const std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
