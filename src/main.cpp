#include <iostream>
#include <filesystem>
#include <string> 
#include <cstdlib>
#include <map>
namespace fs = std::filesystem;

using FolderMap = std::map<fs::path, std::uintmax_t>;

std::uintmax_t scan(const fs::path& current_path, FolderMap& sizes) {
    std::uintmax_t size = 0;

    try {
        for(const auto& entry : fs::directory_iterator(current_path)) {
            if(entry.is_directory()) {
                size += scan(entry.path(), sizes);
            } else {
                size += entry.file_size();
            }
        }
    } catch(const std::filesystem::filesystem_error& e) {
        std::cerr << "Error: " << current_path.string() << ": " << e.what() << "\n";
    }
    sizes[current_path] = size;
    return size;
}

int main() {
    const char* home_Dir = std::getenv("HOME");
    if(home_Dir == nullptr) {
        std::cerr << "Home directory not found\n";
        return 1;
    }
    fs::path path = fs::path(home_Dir) / "Nsync";
    FolderMap sizes;
    scan(path, sizes);
    for(const auto& entry : sizes) {
        std::cout << entry.first.string() << ": " << entry.second << "\n";
    }

    return 0;
}