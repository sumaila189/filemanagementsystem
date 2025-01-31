#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void createFile(const std::string& path) {
    std::ofstream file(path);
    if (file) {
        std::cout << "File created: " << path << std::endl;
    } else {
        std::cout << "Failed to create file." << std::endl;
    }
}

void createDirectory(const std::string& path) {
    if (fs::create_directories(path)) {
        std::cout << "Directory created: " << path << std::endl;
    } else {
        std::cout << "Failed to create directory or it already exists." << std::endl;
    }
}

void deleteFile(const std::string& path) {
    if (fs::remove(path)) {
        std::cout << "File deleted: " << path << std::endl;
    } else {
        std::cout << "File not found." << std::endl;
    }
}

void deleteDirectory(const std::string& path) {
    if (fs::remove_all(path)) {
        std::cout << "Directory deleted: " << path << std::endl;
    } else {
        std::cout << "Directory not found." << std::endl;
    }
}

void moveItem(const std::string& src, const std::string& dest) {
    try {
        fs::rename(src, dest);
        std::cout << "Moved " << src << " to " << dest << std::endl;
    } catch (fs::filesystem_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void copyItem(const std::string& src, const std::string& dest) {
    try {
        if (fs::is_directory(src)) {
            fs::copy(src, dest, fs::copy_options::recursive);
        } else {
            fs::copy_file(src, dest);
        }
        std::cout << "Copied " << src << " to " << dest << std::endl;
    } catch (fs::filesystem_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void displayHierarchy(const std::string& path, int level = 0) {
    if (fs::exists(path)) {
        std::cout << std::string(level * 2, ' ') << "|-- " << fs::path(path).filename().string() << std::endl;
        if (fs::is_directory(path)) {
            for (const auto& entry : fs::directory_iterator(path)) {
                displayHierarchy(entry.path().string(), level + 1);
            }
        }
    } else {
        std::cout << "Path not found." << std::endl;
    }
}

int main() {
    while (true) {
        std::cout << "\nFile Management System" << std::endl;
        std::cout << "1. Create File\n2. Create Directory\n3. Delete File\n4. Delete Directory\n5. Move Item\n6. Copy Item\n7. Display Hierarchy\n8. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;
        std::string path, src, dest;
        
        switch (choice) {
            case 1:
                std::cout << "Enter file path: ";
                std::cin >> path;
                createFile(path);
                break;
            case 2:
                std::cout << "Enter directory path: ";
                std::cin >> path;
                createDirectory(path);
                break;
            case 3:
                std::cout << "Enter file path to delete: ";
                std::cin >> path;
                deleteFile(path);
                break;
            case 4:
                std::cout << "Enter directory path to delete: ";
                std::cin >> path;
                deleteDirectory(path);
                break;
            case 5:
                std::cout << "Enter source path: ";
                std::cin >> src;
                std::cout << "Enter destination path: ";
                std::cin >> dest;
                moveItem(src, dest);
                break;
            case 6:
                std::cout << "Enter source path: ";
                std::cin >> src;
                std::cout << "Enter destination path: ";
                std::cin >> dest;
                copyItem(src, dest);
                break;
            case 7:
                std::cout << "Enter directory path: ";
                std::cin >> path;
                displayHierarchy(path);
                break;
            case 8:
                std::cout << "Exiting..." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}