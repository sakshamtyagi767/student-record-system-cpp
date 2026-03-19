#pragma once
#include "Student.h"
#include <vector>
#include <string>

/**
 * @class FileHandler
 * @brief Handles reading and writing student records to/from a CSV file.
 */
class FileHandler {
public:
    /**
     * @brief Saves all student records to a CSV file.
     * @param students  The list of students to save.
     * @param filename  Path to the output CSV file.
     * @throws std::runtime_error if the file cannot be opened for writing.
     */
    static void saveToCSV(const std::vector<Student>& students,
                          const std::string& filename);

    /**
     * @brief Loads student records from a CSV file.
     * @param filename  Path to the input CSV file.
     * @return Vector of Student objects. Returns empty vector if file not found.
     */
    static std::vector<Student> loadFromCSV(const std::string& filename);
};
