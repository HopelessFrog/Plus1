#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include "MenuOptions.h"

void manualInput(std::string& text) {
    std::cout << "Enter text: ";
    std::getline(std::cin, text);

    if (text.empty()) {
        std::cout << "No text was entered. Please try again.\n";
        return;
    }

    std::string saveOption;
    std::cout << "Do you want to save the entered text to a file? (y/n): ";
    std::getline(std::cin, saveOption);

    if (saveOption == "y" || saveOption == "Y") {
        std::string filename;
        while (true) {
            std::cout << "Enter filename to save text (or 'E' to skip): ";
            std::getline(std::cin, filename);
            if (filename == "E" || filename == "e") {
                std::cout << "Skipping saving text to file.\n";
                break;
            }

            std::ofstream outFile(filename);
            if (outFile.is_open()) {
                outFile << text;
                outFile.close();
                std::cout << "Text successfully saved to " << filename << ".\n";
                break;
            }
            else {
                std::cout << "Failed to open file for saving. Please try a different filename.\n";
            }
        }
    }
}

bool fileInput(std::string& text) {
    std::string filename;
    while (true) {
        std::cout << "Enter filename (or 'E' to skip): ";
        std::getline(std::cin, filename);
        if (filename == "E" || filename == "e") {
            std::cout << "Skipping file input.\n";
            return false;
        }

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
            break;
        }
        else {
            std::cout << "Failed to open file. Please try a different filename.\n";
        }
    }
    return true;
}

void saveResultsToFile(const std::vector<std::string>& wordsWithChar, char symbol) {
    std::string filename;
    while (true) {
        std::cout << "Enter filename to save results (or 'E' to skip): ";
        std::getline(std::cin, filename);
        if (filename == "E" || filename == "e") {
            std::cout << "Skipping saving results to file.\n";
            break;
        }

        std::ofstream outFile(filename);
        if (outFile.is_open()) {
            outFile << "Symbol searched: " << symbol << "\n";
            for (const auto& word : wordsWithChar) {
                outFile << word << "\n";
            }
            outFile.close();
            std::cout << "Results successfully saved to " << filename << ".\n";
            break;
        }
        else {
            std::cout << "Failed to open file for saving. Please try a different filename.\n";
        }
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

        std::string saveOption;
        std::cout << "Do you want to save these results to a file? (y/n): ";
        std::getline(std::cin, saveOption);

        if (saveOption == "y" || saveOption == "Y") {
            saveResultsToFile(wordsWithChar, symbol);
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

        std::string choiceInput;
        std::getline(std::cin, choiceInput);
        try {
            choice = std::stoi(choiceInput);
        }
        catch (...) {
            choice = -1;  
        }

        switch (choice) {
        case MANUAL_INPUT:
            manualInput(text);
            break;
        case FILE_INPUT:
            if (!fileInput(text))
            {
                continue;
            }
           
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
                std::getline(std::cin, input);
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
