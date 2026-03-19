#include "Student.h"
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <vector>

// ─── Constructor ─────────────────────────────────────────────────────────────

Student::Student(int id, const std::string& name, int age,
                 const std::string& major, double gpa) {
    setId(id);
    setName(name);
    setAge(age);
    setMajor(major);
    setGpa(gpa);
}

// ─── Setters with Validation ──────────────────────────────────────────────────

void Student::setId(int id) {
    if (id <= 0)
        throw std::invalid_argument("Student ID must be a positive integer.");
    m_id = id;
}

void Student::setName(const std::string& name) {
    if (name.empty())
        throw std::invalid_argument("Student name cannot be empty.");
    m_name = name;
}

void Student::setAge(int age) {
    if (age < 16 || age > 100)
        throw std::invalid_argument("Age must be between 16 and 100.");
    m_age = age;
}

void Student::setMajor(const std::string& major) {
    if (major.empty())
        throw std::invalid_argument("Major cannot be empty.");
    m_major = major;
}

void Student::setGpa(double gpa) {
    if (gpa < 0.0 || gpa > 4.0)
        throw std::invalid_argument("GPA must be between 0.0 and 4.0.");
    m_gpa = gpa;
}

// ─── Serialization ────────────────────────────────────────────────────────────

std::string Student::toCSV() const {
    return std::to_string(m_id) + "," +
           m_name + "," +
           std::to_string(m_age) + "," +
           m_major + "," +
           std::to_string(m_gpa);
}

Student Student::fromCSV(const std::string& csvLine) {
    std::istringstream stream(csvLine);
    std::string token;
    std::vector<std::string> tokens;

    while (std::getline(stream, token, ','))
        tokens.push_back(token);

    if (tokens.size() != 5)
        throw std::invalid_argument("Malformed CSV line: " + csvLine);

    try {
        int    id    = std::stoi(tokens[0]);
        std::string name  = tokens[1];
        int    age   = std::stoi(tokens[2]);
        std::string major = tokens[3];
        double gpa   = std::stod(tokens[4]);
        return Student(id, name, age, major, gpa);
    } catch (const std::exception&) {
        throw std::invalid_argument("Failed to parse CSV line: " + csvLine);
    }
}

// ─── Output Operator ──────────────────────────────────────────────────────────

std::ostream& operator<<(std::ostream& os, const Student& s) {
    os << std::left
       << std::setw(6)  << s.m_id
       << std::setw(22) << s.m_name
       << std::setw(6)  << s.m_age
       << std::setw(20) << s.m_major
       << std::fixed << std::setprecision(2) << s.m_gpa;
    return os;
}
