#pragma once
#include <string>

/**
 * @namespace Utils
 * @brief Collection of input validation and display helper functions.
 */
namespace Utils {

    /**
     * @brief Prompts for and reads a validated integer from stdin.
     * @param prompt  The message to display to the user.
     * @return A valid integer entered by the user.
     */
    int getIntInput(const std::string& prompt);

    /**
     * @brief Prompts for a double within [minVal, maxVal].
     * @param prompt  The message to display.
     * @param minVal  Minimum acceptable value.
     * @param maxVal  Maximum acceptable value.
     * @return A valid double in range.
     */
    double getDoubleInput(const std::string& prompt, double minVal, double maxVal);

    /**
     * @brief Prompts for a non-empty string, trims leading/trailing whitespace.
     * @param prompt  The message to display.
     * @return A trimmed, non-empty string.
     */
    std::string getStringInput(const std::string& prompt);

    /**
     * @brief Prints a formatted section header to stdout.
     * @param title  The header title text.
     */
    void printHeader(const std::string& title);

    /**
     * @brief Prints the column headers for the student table.
     */
    void printTableHeader();

    /**
     * @brief Converts a string to lowercase.
     * @param str  Input string.
     * @return Lowercase version of str.
     */
    std::string toLower(const std::string& str);

    /**
     * @brief Clears the terminal screen (cross-platform).
     */
    void clearScreen();

    /**
     * @brief Pauses execution until the user presses Enter.
     */
    void pauseScreen();

} // namespace Utils
