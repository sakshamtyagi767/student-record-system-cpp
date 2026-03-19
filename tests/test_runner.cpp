/**
 * test_runner.cpp
 * ─────────────────────────────────────────────────────────
 * Hand-written unit tests for Student Record Management System.
 * No external framework needed — just compile and run.
 *
 * Usage:
 *   g++ -std=c++17 -Wall -I include tests/test_runner.cpp
 *       src/Student.cpp src/RecordManager.cpp src/FileHandler.cpp
 *       src/Utils.cpp -o tests/test_runner.exe
 *   .\tests\test_runner.exe
 */

#include "Student.h"
#include "RecordManager.h"
#include "FileHandler.h"
#include <iostream>
#include <cassert>
#include <stdexcept>
#include <cstdio>   // std::remove

// ─── Minimal Test Harness ─────────────────────────────────────────────────────

int testsPassed = 0;
int testsFailed = 0;

void reportResult(const std::string& testName, bool passed) {
    if (passed) {
        std::cout << "  [PASS] " << testName << "\n";
        ++testsPassed;
    } else {
        std::cout << "  [FAIL] " << testName << "\n";
        ++testsFailed;
    }
}

// ─── Test: Add and Retrieve Student ──────────────────────────────────────────

void testAddStudent() {
    RecordManager mgr;
    Student s(1001, "Alice Johnson", 20, "Computer Science", 3.85);
    mgr.addStudent(s);

    const Student* found = mgr.findByID(1001);
    bool passed = (found != nullptr) &&
                  (found->getName() == "Alice Johnson") &&
                  (found->getGpa()  == 3.85);
    reportResult("Add and retrieve student by ID", passed);
}

// ─── Test: Duplicate ID Throws Exception ─────────────────────────────────────

void testDuplicateID() {
    RecordManager mgr;
    Student s1(1002, "Bob Smith", 21, "Mathematics", 3.50);
    mgr.addStudent(s1);

    bool exceptionThrown = false;
    try {
        Student s2(1002, "Charlie Brown", 22, "Physics", 2.90);
        mgr.addStudent(s2);
    } catch (const std::runtime_error&) {
        exceptionThrown = true;
    }
    reportResult("Duplicate ID throws runtime_error", exceptionThrown);
}

// ─── Test: Case-Insensitive Search by Name ───────────────────────────────────

void testSearchByName() {
    RecordManager mgr;
    mgr.addStudent(Student(1003, "Diana Prince", 19, "History", 3.10));
    mgr.addStudent(Student(1004, "Eve Adams",    22, "Biology", 3.70));

    auto results = mgr.findByName("diana");  // lowercase query
    bool passed  = (results.size() == 1) &&
                   (results[0].getName() == "Diana Prince");
    reportResult("Case-insensitive search by name", passed);
}

// ─── Test: Sort by GPA ───────────────────────────────────────────────────────

void testSortByGPA() {
    RecordManager mgr;
    mgr.addStudent(Student(1005, "Frank Castle", 23, "Law",     3.90));
    mgr.addStudent(Student(1006, "Grace Hopper", 21, "CS",      2.50));
    mgr.addStudent(Student(1007, "Hank Pym",     24, "Physics", 3.20));

    mgr.sortByGPA();
    const auto& students = mgr.getAllStudents();

    bool passed = (students[0].getGpa() <= students[1].getGpa()) &&
                  (students[1].getGpa() <= students[2].getGpa());
    reportResult("Sort by GPA (ascending)", passed);
}

// ─── Test: File Save and Load (Round-trip) ───────────────────────────────────

void testFileRoundtrip() {
    const std::string testFile = "data/test_temp.csv";

    RecordManager mgr;
    mgr.addStudent(Student(2001, "Iris West",  20, "Journalism",   3.60));
    mgr.addStudent(Student(2002, "Jake Long",  22, "Engineering",  3.30));

    FileHandler::saveToCSV(mgr.getAllStudents(), testFile);
    auto loaded = FileHandler::loadFromCSV(testFile);

    bool passed = (loaded.size() == 2) &&
                  (loaded[0].getId()   == 2001) &&
                  (loaded[1].getName() == "Jake Long");

    reportResult("File save and load round-trip", passed);

    // Cleanup temp file
    std::remove(testFile.c_str());
}

// ─── Test: Invalid GPA Throws ────────────────────────────────────────────────

void testInvalidGPA() {
    bool exceptionThrown = false;
    try {
        Student s(3001, "Karl Urban", 25, "Drama", 5.0);  // GPA > 4.0
    } catch (const std::invalid_argument&) {
        exceptionThrown = true;
    }
    reportResult("Invalid GPA (5.0) throws invalid_argument", exceptionThrown);
}

// ─── Test: Delete Student ────────────────────────────────────────────────────

void testDeleteStudent() {
    RecordManager mgr;
    mgr.addStudent(Student(4001, "Laura Palmer", 20, "Nursing", 2.80));
    mgr.deleteByID(4001);

    bool passed = (mgr.findByID(4001) == nullptr) && mgr.isEmpty();
    reportResult("Delete student by ID", passed);
}

// ─── Main Runner ─────────────────────────────────────────────────────────────

int main() {
    std::cout << "\n  ============================\n"
              << "   Running Unit Tests\n"
              << "  ============================\n\n";

    testAddStudent();
    testDuplicateID();
    testSearchByName();
    testSortByGPA();
    testFileRoundtrip();
    testInvalidGPA();
    testDeleteStudent();

    std::cout << "\n  ----------------------------\n";
    std::cout << "  Results: " << testsPassed << " passed, "
              << testsFailed << " failed\n";
    std::cout << "  ----------------------------\n\n";

    return (testsFailed == 0) ? 0 : 1;
}
