#include "RecordManager.h"
#include "Utils.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <iomanip>

// ─── CRUD ─────────────────────────────────────────────────────────────────────

void RecordManager::addStudent(const Student& student) {
    // Check for duplicate ID
    if (findByID(student.getId()) != nullptr)
        throw std::runtime_error("Student with ID " +
                                 std::to_string(student.getId()) + " already exists.");
    m_students.push_back(student);
}

void RecordManager::deleteByID(int id) {
    auto it = std::find_if(m_students.begin(), m_students.end(),
                           [id](const Student& s) { return s.getId() == id; });
    if (it == m_students.end())
        throw std::runtime_error("No student found with ID " + std::to_string(id));
    m_students.erase(it);
}

void RecordManager::updateStudent(const Student& updated) {
    auto it = std::find_if(m_students.begin(), m_students.end(),
                           [&updated](const Student& s) {
                               return s.getId() == updated.getId();
                           });
    if (it == m_students.end())
        throw std::runtime_error("No student found with ID " +
                                 std::to_string(updated.getId()));
    *it = updated;
}

// ─── Search ───────────────────────────────────────────────────────────────────

const Student* RecordManager::findByID(int id) const {
    for (const auto& s : m_students)
        if (s.getId() == id)
            return &s;
    return nullptr;
}

std::vector<Student> RecordManager::findByName(const std::string& name) const {
    std::string query = Utils::toLower(name);
    std::vector<Student> results;
    for (const auto& s : m_students)
        if (Utils::toLower(s.getName()).find(query) != std::string::npos)
            results.push_back(s);
    return results;
}

// ─── Sort ─────────────────────────────────────────────────────────────────────

void RecordManager::sortByGPA() {
    std::sort(m_students.begin(), m_students.end(),
              [](const Student& a, const Student& b) {
                  return a.getGpa() < b.getGpa();
              });
}

void RecordManager::sortByName() {
    std::sort(m_students.begin(), m_students.end(),
              [](const Student& a, const Student& b) {
                  return a.getName() < b.getName();
              });
}

// ─── Display ──────────────────────────────────────────────────────────────────

void RecordManager::displayAll() const {
    if (m_students.empty()) {
        std::cout << "  (No records found.)\n";
        return;
    }
    Utils::printTableHeader();
    for (const auto& s : m_students) {
        std::cout << "  " << s << "\n";
    }
    std::cout << "\n  Total records: " << m_students.size() << "\n";
}

void RecordManager::displayStudent(const Student& s) {
    Utils::printTableHeader();
    std::cout << "  " << s << "\n";
}
