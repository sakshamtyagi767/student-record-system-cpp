#pragma once
#include "Student.h"
#include <vector>
#include <string>

/**
 * @class RecordManager
 * @brief Manages a collection of Student records in memory.
 *
 * Provides CRUD operations, search by ID or name, and sorting.
 * Throws std::runtime_error for operations that fail (e.g., duplicate ID).
 */
class RecordManager {
private:
    std::vector<Student> m_students;

public:
    // --- CRUD ---

    /**
     * @brief Adds a student. Throws if ID already exists.
     */
    void addStudent(const Student& student);

    /**
     * @brief Deletes a student by ID. Throws if not found.
     */
    void deleteByID(int id);

    /**
     * @brief Updates an existing student record. Throws if not found.
     */
    void updateStudent(const Student& updated);

    // --- Read ---

    /**
     * @brief Returns a const reference to all student records.
     */
    const std::vector<Student>& getAllStudents() const { return m_students; }

    /**
     * @brief Finds a student by ID. Returns nullptr if not found.
     */
    const Student* findByID(int id) const;

    /**
     * @brief Case-insensitive search by name substring.
     * @return Vector of matching students.
     */
    std::vector<Student> findByName(const std::string& name) const;

    // --- Sort ---

    /** @brief Sorts records in ascending order by GPA. */
    void sortByGPA();

    /** @brief Sorts records alphabetically by name. */
    void sortByName();

    // --- Display ---

    /** @brief Prints all records as a formatted table to stdout. */
    void displayAll() const;

    /** @brief Prints a single student as a formatted table row. */
    static void displayStudent(const Student& s);

    /** @brief Replaces all records (used when loading from file). */
    void setStudents(const std::vector<Student>& students) { m_students = students; }

    /** @brief Returns true if no records exist. */
    bool isEmpty() const { return m_students.empty(); }

    /** @brief Returns the total count of records. */
    size_t count() const { return m_students.size(); }
};
