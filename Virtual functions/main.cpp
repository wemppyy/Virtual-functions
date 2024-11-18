#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

class FileHandler {
public:
    virtual ~FileHandler() = default;

    virtual void Display(const char* path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << path << "\n";
            return;
        }
        std::cout << "Content of the file:\n";
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << "\n";
        }
        file.close();
    }

    void CreateFileIfNotExists(const char* path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::ofstream newFile(path);
            if (newFile.is_open()) {
                newFile << "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\n";
                newFile << "Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\n";
                newFile << "Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris.\n";
                newFile.close();
                std::cout << "File created: " << path << "\n";
            }
            else {
                std::cerr << "Error: Could not create file " << path << "\n";
            }
        }
        else {
            std::cout << "File already exists: " << path << "\n";
        }
    }
};

class AsciiFileHandler : public FileHandler {
public:
    void Display(const char* path) override {
        std::ifstream file(path);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << path << "\n";
            return;
        }
        std::cout << "Content as ASCII codes:\n";
        char ch;
        while (file.get(ch)) {
            std::cout << static_cast<int>(ch) << " ";
        }
        std::cout << "\n";
        file.close();
    }
};

class BinaryFileHandler : public FileHandler {
public:
    void Display(const char* path) override {
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << path << "\n";
            return;
        }
        std::cout << "Content in binary format:\n";
        char ch;
        while (file.get(ch)) {
            std::cout << std::bitset<8>(ch) << " ";
        }
        std::cout << "\n";
        file.close();
    }
};

int main() {
    const char* filePath = "example.txt";

    FileHandler baseHandler;
    AsciiFileHandler asciiHandler;
    BinaryFileHandler binaryHandler;

    baseHandler.CreateFileIfNotExists(filePath);

    std::cout << "\nBase Handler:\n";
    baseHandler.Display(filePath);

    std::cout << "\nASCII Handler:\n";
    asciiHandler.Display(filePath);

    std::cout << "\nBinary Handler:\n";
    binaryHandler.Display(filePath);

    return 0;
}
