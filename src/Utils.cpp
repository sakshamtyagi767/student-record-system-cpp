#include "Utils.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <cctype>
#include <iomanip>

namespace Utils {

// ─── Input Helpers ────────────────────────────────────────────────────────────

int getIntInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        // Clear error flags and discard bad input
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  [!] Invalid input. Please enter a whole number.\n";
    }
}

double getDoubleInput(const std::string& prompt, double minVal, double maxVal) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (value >= minVal && value <= maxVal)
                return value;
            std::cout << "  [!] Value must be between " << minVal
                      << " and " << maxVal << ".\n";
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "  [!] Invalid input. Please enter a number.\n";
        }
    }
}

std::string getStringInput(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);

        // Trim leading whitespace
        size_t start = value.find_first_not_of(" \t");
        // Trim trailing whitespace
        size_t end   = value.find_last_not_of(" \t");

        if (start == std::string::npos) {
            std::cout << "  [!] Input cannot be empty. Please try again.\n";
            continue;
        }
        return value.substr(start, end - start + 1);
    }
}

// ─── Display Helpers ──────────────────────────────────────────────────────────

void printHeader(const std::string& title) {
    std::string border(60, '=');
    std::cout << "\n  " << border << "\n";
    // Centre the title
    int padding = static_cast<int>((58 - static_cast<int>(title.size())) / 2);
    std::cout << "  " << std::string(padding, ' ') << title << "\n";
    std::cout << "  " << border << "\n\n";
}

void printTableHeader() {
    std::cout << "\n  "
              << std::left
              << std::setw(6)  << "ID"
              << std::setw(22) << "Name"
              << std::setw(6)  << "Age"
              << std::setw(20) << "Major"
              << "GPA"
              << "\n";
    std::cout << "  " << std::string(57, '-') << "\n";
}

// ─── String Utilities ─────────────────────────────────────────────────────────

std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

// ─── Screen Utilities ─────────────────────────────────────────────────────────

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void pauseScreen() {
    std::cout << "\n  Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

} // namespace Utils
