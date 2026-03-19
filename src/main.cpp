#include "Student.h"
#include "RecordManager.h"
#include "FileHandler.h"
#include "Utils.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>

// ─── Constants ────────────────────────────────────────────────────────────────
const std::string DATA_FILE = "data/students.csv";

// ─── Forward Declarations ────────────────────────────────────────────────────
void menuAddStudent(RecordManager& mgr);
void menuDisplayAll(RecordManager& mgr);
void menuSearch(RecordManager& mgr);
void menuUpdate(RecordManager& mgr);
void menuDelete(RecordManager& mgr);
void menuSort(RecordManager& mgr);

// ─── Main ─────────────────────────────────────────────────────────────────────

int main() {
    RecordManager mgr;

    // Load existing records from CSV
    try {
        auto loaded = FileHandler::loadFromCSV(DATA_FILE);
        mgr.setStudents(loaded);
        if (!loaded.empty())
            std::cout << "  [+] Loaded " << loaded.size()
                      << " record(s) from " << DATA_FILE << "\n";
    } catch (const std::exception& e) {
        std::cerr << "  [Warning] Could not load data: " << e.what() << "\n";
    }

    int choice = 0;
    bool running = true;

    while (running) {
        Utils::printHeader("STUDENT RECORD MANAGEMENT SYSTEM");

        std::cout << "  [1] Add Student\n"
                  << "  [2] Display All Students\n"
                  << "  [3] Search Student\n"
                  << "  [4] Update Student\n"
                  << "  [5] Delete Student\n"
                  << "  [6] Sort Records\n"
                  << "  [7] Save & Exit\n\n";

        choice = Utils::getIntInput("  Enter your choice (1-7): ");

        switch (choice) {
            case 1: menuAddStudent(mgr);  break;
            case 2: menuDisplayAll(mgr);  break;
            case 3: menuSearch(mgr);      break;
            case 4: menuUpdate(mgr);      break;
            case 5: menuDelete(mgr);      break;
            case 6: menuSort(mgr);        break;
            case 7: running = false;      break;
            default:
                std::cout << "  [!] Invalid choice. Please enter 1-7.\n";
                Utils::pauseScreen();
        }
    }

    // Auto-save on exit
    try {
        FileHandler::saveToCSV(mgr.getAllStudents(), DATA_FILE);
        std::cout << "\n  [+] Data saved to " << DATA_FILE << "\n";
    } catch (const std::exception& e) {
        std::cerr << "  [!] Failed to save data: " << e.what() << "\n";
    }

    std::cout << "  Goodbye!\n\n";
    return 0;
}

// ─── Menu Handlers ───────────────────────────────────────────────────────────

void menuAddStudent(RecordManager& mgr) {
    Utils::printHeader("ADD NEW STUDENT");
    try {
        int    id    = Utils::getIntInput("  Student ID    : ");
        std::string name  = Utils::getStringInput("  Full Name     : ");
        int    age   = Utils::getIntInput("  Age           : ");
        std::string major = Utils::getStringInput("  Major         : ");
        double gpa   = Utils::getDoubleInput("  GPA (0.0-4.0) : ", 0.0, 4.0);

        Student s(id, name, age, major, gpa);
        mgr.addStudent(s);
        std::cout << "\n  [+] Student added successfully!\n";
    } catch (const std::exception& e) {
        std::cout << "\n  [!] Error: " << e.what() << "\n";
    }
    Utils::pauseScreen();
}

void menuDisplayAll(RecordManager& mgr) {
    Utils::printHeader("ALL STUDENTS");
    mgr.displayAll();
    Utils::pauseScreen();
}

void menuSearch(RecordManager& mgr) {
    Utils::printHeader("SEARCH STUDENT");
    std::cout << "  [1] Search by ID\n"
              << "  [2] Search by Name\n";
    int opt = Utils::getIntInput("  Choose (1-2): ");

    if (opt == 1) {
        int id = Utils::getIntInput("  Enter Student ID: ");
        const Student* s = mgr.findByID(id);
        if (s) {
            RecordManager::displayStudent(*s);
        } else {
            std::cout << "  [!] No student found with ID " << id << "\n";
        }
    } else if (opt == 2) {
        std::string name = Utils::getStringInput("  Enter name to search: ");
        auto results = mgr.findByName(name);
        if (results.empty()) {
            std::cout << "  [!] No students matched \"" << name << "\"\n";
        } else {
            Utils::printTableHeader();
            for (const auto& s : results)
                std::cout << "  " << s << "\n";
            std::cout << "\n  Found: " << results.size() << " record(s)\n";
        }
    } else {
        std::cout << "  [!] Invalid option.\n";
    }
    Utils::pauseScreen();
}

void menuUpdate(RecordManager& mgr) {
    Utils::printHeader("UPDATE STUDENT");
    int id = Utils::getIntInput("  Enter Student ID to update: ");
    const Student* existing = mgr.findByID(id);
    if (!existing) {
        std::cout << "  [!] No student found with ID " << id << "\n";
        Utils::pauseScreen();
        return;
    }
    std::cout << "\n  Current record:\n";
    RecordManager::displayStudent(*existing);

    try {
        std::cout << "\n  Enter new values (press Enter to keep current):\n";
        std::string name  = Utils::getStringInput("  Full Name     : ");
        int    age   = Utils::getIntInput("  Age           : ");
        std::string major = Utils::getStringInput("  Major         : ");
        double gpa   = Utils::getDoubleInput("  GPA (0.0-4.0) : ", 0.0, 4.0);

        Student updated(id, name, age, major, gpa);
        mgr.updateStudent(updated);
        std::cout << "\n  [+] Record updated successfully!\n";
    } catch (const std::exception& e) {
        std::cout << "\n  [!] Error: " << e.what() << "\n";
    }
    Utils::pauseScreen();
}

void menuDelete(RecordManager& mgr) {
    Utils::printHeader("DELETE STUDENT");
    int id = Utils::getIntInput("  Enter Student ID to delete: ");

    const Student* s = mgr.findByID(id);
    if (!s) {
        std::cout << "  [!] No student found with ID " << id << "\n";
        Utils::pauseScreen();
        return;
    }
    std::cout << "\n  Record to delete:\n";
    RecordManager::displayStudent(*s);

    std::string confirm = Utils::getStringInput("\n  Confirm deletion? (yes/no): ");
    if (confirm == "yes" || confirm == "y") {
        try {
            mgr.deleteByID(id);
            std::cout << "  [+] Student with ID " << id << " deleted.\n";
        } catch (const std::exception& e) {
            std::cout << "  [!] Error: " << e.what() << "\n";
        }
    } else {
        std::cout << "  [-] Deletion cancelled.\n";
    }
    Utils::pauseScreen();
}

void menuSort(RecordManager& mgr) {
    Utils::printHeader("SORT RECORDS");
    std::cout << "  [1] Sort by GPA (ascending)\n"
              << "  [2] Sort by Name (A-Z)\n";
    int opt = Utils::getIntInput("  Choose (1-2): ");

    if (opt == 1) {
        mgr.sortByGPA();
        std::cout << "  [+] Records sorted by GPA.\n";
    } else if (opt == 2) {
        mgr.sortByName();
        std::cout << "  [+] Records sorted by Name.\n";
    } else {
        std::cout << "  [!] Invalid option.\n";
        Utils::pauseScreen();
        return;
    }
    mgr.displayAll();
    Utils::pauseScreen();
}
