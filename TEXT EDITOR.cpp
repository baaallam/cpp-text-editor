#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <cctype> // for toupper, tolower

// --- Function Declarations ---
void displayMenu();
void displayText(const std::vector<std::string>& buffer);
void editText(std::vector<std::string>& buffer);
void openFile(std::vector<std::string>& buffer, std::string& currentFilename);
void saveFile(const std::vector<std::string>& buffer, std::string& currentFilename);

// --- Main Function ---
int main() {
    std::vector<std::string> buffer;
    std::string currentFilename = "untitled.txt";
    char choice;

    std::cout << "--- Simple C++ Text Editor ---" << std::endl;

    do {
        displayMenu();

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        // Clear trailing characters
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        switch (std::toupper(choice)) {
            case 'N':
                buffer.clear();
                currentFilename = "untitled.txt";
                std::cout << "New file created. Buffer is now empty." << std::endl;
                break;
            case 'O':
                openFile(buffer, currentFilename);
                break;
            case 'S':
                saveFile(buffer, currentFilename);
                break;
            case 'E':
                editText(buffer);
                break;
            case 'D':
                displayText(buffer);
                break;
            case 'Q':
                std::cout << "Exiting editor. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
        std::cout << std::endl;

    } while (std::toupper(choice) != 'Q');

    return 0;
}

// --- Function Implementations ---
void displayMenu() {
    std::cout << "------------------------" << std::endl;
    std::cout << "Menu:" << std::endl;
    std::cout << " (N)ew File" << std::endl;
    std::cout << " (O)pen File" << std::endl;
    std::cout << " (S)ave File" << std::endl;
    std::cout << " (E)dit Text" << std::endl;
    std::cout << " (D)isplay Text" << std::endl;
    std::cout << " (Q)uit" << std::endl;
    std::cout << "------------------------" << std::endl;
    std::cout << "Enter your choice: ";
}

void displayText(const std::vector<std::string>& buffer) {
    std::cout << "\n--- Document Content ---" << std::endl;
    if (buffer.empty()) {
        std::cout << "[Empty]" << std::endl;
    } else {
        for (size_t i = 0; i < buffer.size(); ++i) {
            std::cout << i + 1 << ": " << buffer[i] << std::endl;
        }
    }
    std::cout << "--- End of Document ---\n" << std::endl;
}

void editText(std::vector<std::string>& buffer) {
    std::cout << "\n--- Editing Mode ---" << std::endl;
    std::cout << "Enter text. Type '~' on a new line to save and exit editing mode." << std::endl;
    
    std::string line;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);
        if (line == "~") break;
        buffer.push_back(line);
    }
    std::cout << "Exited editing mode." << std::endl;
}

void openFile(std::vector<std::string>& buffer, std::string& currentFilename) {
    std::cout << "Enter filename to open: ";
    std::getline(std::cin, currentFilename);

    std::ifstream inFile(currentFilename);
    if (!inFile) {
        std::cerr << "Error: Could not open file '" << currentFilename << "'." << std::endl;
        return;
    }

    buffer.clear();
    std::string line;
    while (std::getline(inFile, line)) {
        buffer.push_back(line);
    }

    inFile.close();
    std::cout << "Successfully opened '" << currentFilename << "'." << std::endl;
}

void saveFile(const std::vector<std::string>& buffer, std::string& currentFilename) {
    std::cout << "Current filename is '" << currentFilename << "'. Save with this name? (y/n): ";
    char choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Save aborted.\n";
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (std::tolower(choice) != 'y') {
        std::cout << "Enter new filename: ";
        std::getline(std::cin, currentFilename);
    }

    std::ofstream outFile(currentFilename);
    if (!outFile) {
        std::cerr << "Error: Could not open file '" << currentFilename << "' for writing." << std::endl;
        return;
    }

    for (const auto& line : buffer) {
        outFile << line << std::endl;
    }

    outFile.close();
    std::cout << "File saved successfully as '" << currentFilename << "'." << std::endl;
}
