#include "FileHandler.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

void FileHandler::saveToCSV(const std::vector<Student>& students,
                             const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Cannot open file for writing: " + filename);

    for (const auto& s : students)
        file << s.toCSV() << "\n";

    // ofstream closes automatically via RAII — no explicit close needed
}

std::vector<Student> FileHandler::loadFromCSV(const std::string& filename) {
    std::vector<Student> students;
    std::ifstream file(filename);

    // Gracefully return empty vector if file doesn't exist yet (first run)
    if (!file.is_open())
        return students;

    std::string line;
    int lineNumber = 0;
    while (std::getline(file, line)) {
        ++lineNumber;
        if (line.empty()) continue;  // skip blank lines
        try {
            students.push_back(Student::fromCSV(line));
        } catch (const std::exception& e) {
            std::cerr << "  [Warning] Skipping malformed line " << lineNumber
                      << ": " << e.what() << "\n";
        }
    }
    return students;
}
