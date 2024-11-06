#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include "MenuOptions.h"

void manualInput(std::string& text) {
    std::cout << "Enter text: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
    std::getline(std::cin, text);
    if (text.empty()) {
        std::cout << "No text was entered. Please try again.\n";
    }
}

void fileInput(std::string& text) {
    std::string filename;
    std::cout << "Enter filename: ";
    std::cin >> filename;

    std::ifstream file(filename);
    if (file.is_open()) {
        std::ostringstream ss;
        ss << file.rdbuf();
        text = ss.str();
        file.close();
        if (text.empty()) {
            std::cout << "The file is empty.\n";
        }
        else {
            std::cout << "Text successfully read from file.\n";
        }
    }
    else {
        std::cout << "Failed to open file. Please check if the file exists.\n";
    }
}

void printWordsWithChar(const std::string& text, char symbol) {
    if (text.empty()) {
        std::cout << "No text available to search.\n";
        return;
    }

    std::istringstream stream(text);
    std::string word;
    std::vector<std::string> wordsWithChar;

    while (stream >> word) {
        if (word.find(symbol) != std::string::npos) {
            wordsWithChar.push_back(word);
        }
    }

    if (!wordsWithChar.empty()) {
        std::cout << "Words containing the symbol '" << symbol << "':\n";
        for (const auto& w : wordsWithChar) {
            std::cout << w << "\n";
        }
    }
    else {
        std::cout << "No words contain the symbol '" << symbol << "'.\n";
    }
}

int main() {
    std::string text;
    int choice;

    do {
        std::cout << "\nMenu:\n";
        std::cout << "1 - Manual text input\n";
        std::cout << "2 - File text input\n";
        std::cout << "3 - Exit\n";
        std::cout << "Choose an option: ";

        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Choose an option: ";
        }

        switch (choice) {
        case MANUAL_INPUT:
            manualInput(text);
            break;
        case FILE_INPUT:
            fileInput(text);
            break;
        case EXIT:
            std::cout << "Exiting the program.\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }

        if ((choice == MANUAL_INPUT || choice == FILE_INPUT) && !text.empty()) {
            std::string input;
            char symbol;

            do {
                std::cout << "Enter a single symbol to search for words: ";
                std::cin >> input;
                if (input.size() == 1) {
                    symbol = input[0];
                }
                else {
                    std::cout << "Please enter only one character.\n";
                }
            } while (input.size() != 1);

            printWordsWithChar(text, symbol);
        }

    } while (choice != EXIT);

    return 0;
}
