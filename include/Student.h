#pragma once
#include <string>
#include <iostream>

/**
 * @class Student
 * @brief Represents a single student record with validation on setters.
 */
class Student {
private:
    int         m_id;
    std::string m_name;
    int         m_age;
    std::string m_major;
    double      m_gpa;

public:
    // --- Constructors ---
    Student() = default;
    Student(int id, const std::string& name, int age,
            const std::string& major, double gpa);

    // --- Getters ---
    int                getId()    const { return m_id;    }
    const std::string& getName()  const { return m_name;  }
    int                getAge()   const { return m_age;   }
    const std::string& getMajor() const { return m_major; }
    double             getGpa()   const { return m_gpa;   }

    // --- Setters (with validation, throw std::invalid_argument on bad input) ---
    void setId(int id);
    void setName(const std::string& name);
    void setAge(int age);
    void setMajor(const std::string& major);
    void setGpa(double gpa);

    /**
     * @brief Converts student data to a CSV row string.
     * @return Comma-separated string: id,name,age,major,gpa
     */
    std::string toCSV() const;

    /**
     * @brief Constructs a Student object from a CSV row string.
     * @param csvLine A comma-separated string with 5 fields.
     * @return Parsed Student object.
     * @throws std::invalid_argument if the CSV line is malformed.
     */
    static Student fromCSV(const std::string& csvLine);

    // --- Operator overload for easy printing ---
    friend std::ostream& operator<<(std::ostream& os, const Student& s);
};
