#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

void listDirectory(const fs::path& path) {
    std::cout << "Listing directory: " << path << std::endl;
    for (const auto& entry : fs::directory_iterator(path)) {
        std::cout << (entry.is_directory() ? "[DIR] " : "[FILE] ") << entry.path().filename().string() << std::endl;
    }
}

void viewFile(const fs::path& path) {
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Error: Could not open file " << path << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
}

void createDirectory(const fs::path& path) {
    if (fs::create_directory(path)) {
        std::cout << "Directory created: " << path << std::endl;
    } else {
        std::cerr << "Error: Could not create directory " << path << std::endl;
    }
}

void copyFile(const fs::path& source, const fs::path& destination) {
    try {
        fs::copy(source, destination, fs::copy_options::overwrite_existing);
        std::cout << "File copied from " << source << " to " << destination << std::endl;
    } catch (fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void deleteFile(const fs::path& path) {
    try {
        if (fs::remove(path)) {
            std::cout << "File deleted: " << path << std::endl;
        } else {
            std::cerr << "Error: Could not delete file " << path << std::endl;
        }
    } catch (fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void moveFile(const fs::path& source, const fs::path& destination) {
    try {
        fs::rename(source, destination);
        std::cout << "File moved from " << source << " to " << destination << std::endl;
    } catch (fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void renameFile(const fs::path& oldName, const fs::path& newName) {
    try {
        fs::rename(oldName, newName);
        std::cout << "File renamed from " << oldName << " to " << newName << std::endl;
    } catch (fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void searchFile(const fs::path& path, const std::string& filename) {
    bool found = false;
    for (const auto& entry : fs::recursive_directory_iterator(path)) {
        if (entry.path().filename() == filename) {
            std::cout << "Found: " << entry.path() << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "File not found: " << filename << std::endl;
    }
}

void displayFileProperties(const fs::path& path) {
    try {
        if (fs::exists(path)) {
            std::cout << "File: " << path << std::endl;
            std::cout << "Size: " << fs::file_size(path) << " bytes" << std::endl;
            std::cout << "Last modified: " << fs::last_write_time(path).time_since_epoch().count() << std::endl;
        } else {
            std::cerr << "Error: File does not exist" << std::endl;
        }
    } catch (fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void displayMenu() {
    std::cout << "File Manager Menu:" << std::endl;
    std::cout << "1. List Directory" << std::endl;
    std::cout << "2. View File" << std::endl;
    std::cout << "3. Create Directory" << std::endl;
    std::cout << "4. Copy File" << std::endl;
    std::cout << "5. Delete File" << std::endl;
    std::cout << "6. Move File" << std::endl;
    std::cout << "7. Rename File" << std::endl;
    std::cout << "8. Search File" << std::endl;
    std::cout << "9. Display File Properties" << std::endl;
    std::cout << "10. Exit" << std::endl;
}

int main() {
    int choice;
    fs::path path, source, destination;
    std::string filename;

    while (true) {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter directory path: ";
                std::cin >> path;
                listDirectory(path);
                break;
            case 2:
                std::cout << "Enter file path: ";
                std::cin >> path;
                viewFile(path);
                break;
            case 3:
                std::cout << "Enter directory path: ";
                std::cin >> path;
                createDirectory(path);
                break;
            case 4:
                std::cout << "Enter source file path: ";
                std::cin >> source;
                std::cout << "Enter destination file path: ";
                std::cin >> destination;
                copyFile(source, destination);
                break;
            case 5:
                std::cout << "Enter file path: ";
                std::cin >> path;
                deleteFile(path);
                break;
            case 6:
                std::cout << "Enter source file path: ";
                std::cin >> source;
                std::cout << "Enter destination file path: ";
                std::cin >> destination;
                moveFile(source, destination);
                break;
            case 7:
                std::cout << "Enter old file name: ";
                std::cin >> source;
                std::cout << "Enter new file name: ";
                std::cin >> destination;
                renameFile(source, destination);
                break;
            case 8:
                std::cout << "Enter directory path: ";
                std::cin >> path;
                std::cout << "Enter filename to search: ";
                std::cin >> filename;
                searchFile(path, filename);
                break;
            case 9:
                std::cout << "Enter file path: ";
                std::cin >> path;
                displayFileProperties(path);
                break;
            case 10:
                std::cout << "Exiting..." << std::endl;
                return 0;
            default:
                std::cerr << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}