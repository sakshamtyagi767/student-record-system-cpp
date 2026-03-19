# Student Record Management System

A **CLI-based Student Record Management System** built in **C++17** demonstrating professional-grade OOP, STL algorithms, file persistence, and exception handling.

---

## Features

| Feature | Details |
|---------|---------|
| **Add Student** | Validates ID, age (16–100), GPA (0.0–4.0) |
| **Display All** | Formatted table with column headers |
| **Search** | By ID (exact) or Name (case-insensitive substring) |
| **Update** | Edit any field of an existing record |
| **Delete** | Requires confirmation before removing |
| **Sort** | By GPA (ascending) or Name (A–Z) |
| **Persistence** | Auto-loads on start, auto-saves to CSV on exit |

---

## Tech Stack

- **Language:** C++17
- **Build:** GNU Make + g++
- **Storage:** CSV (`data/students.csv`)
- **Testing:** Hand-written unit tests (no external library)

---

## C++ Concepts Demonstrated

- OOP — Classes, encapsulation, operator overloading
- STL — `std::vector`, `std::sort`, `std::find_if`, lambdas
- File I/O — `std::fstream` with RAII
- Exception Handling — `std::runtime_error`, `std::invalid_argument`
- Namespaces — `Utils` namespace
- `const` correctness throughout

---

## Build & Run

> **Requires:** g++ with C++17 support. Install via [MinGW-w64](https://www.mingw-w64.org/) on Windows.

```bash
# Compile
g++ -std=c++17 -Wall -I include src/Student.cpp src/RecordManager.cpp src/FileHandler.cpp src/Utils.cpp src/main.cpp -o StudentRecordSystem.exe

# Run
.\StudentRecordSystem.exe
```

---

## Run Unit Tests

```bash
g++ -std=c++17 -Wall -I include tests/test_runner.cpp src/Student.cpp src/RecordManager.cpp src/FileHandler.cpp src/Utils.cpp -o tests/test_runner.exe
.\tests\test_runner.exe
```

Expected output:
```
  [PASS] Add and retrieve student by ID
  [PASS] Duplicate ID throws runtime_error
  [PASS] Case-insensitive search by name
  [PASS] Sort by GPA (ascending)
  [PASS] File save and load round-trip
  [PASS] Invalid GPA (5.0) throws invalid_argument
  [PASS] Delete student by ID

  Results: 7 passed, 0 failed
```

---

## Sample Output

```
  ============================================================
              STUDENT RECORD MANAGEMENT SYSTEM
  ============================================================

  [1] Add Student
  [2] Display All Students
  [3] Search Student
  [4] Update Student
  [5] Delete Student
  [6] Sort Records
  [7] Save & Exit

  Enter your choice (1-7):
```

---

## Project Structure

```
StudentRecordSystem/
├── include/          ← Header files
├── src/              ← Source files
├── tests/            ← Unit tests
├── data/             ← CSV data (auto-created)
└── README.md
```

---

*Built as a portfolio project demonstrating intermediate C++ skills for software engineering internship applications.*
