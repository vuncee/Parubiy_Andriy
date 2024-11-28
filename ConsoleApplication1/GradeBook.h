#ifndef GRADEBOOK_H
#define GRADEBOOK_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "LibraryItem.h"

class GradeBook : public LibraryItem {
private:
    std::string subject;
    std::string studentName;
    int course;
    std::vector<int> grades;

public:
    GradeBook() : subject(""), studentName(""), course(0) {}
    GradeBook(const std::string& subject, const std::string& studentName, int course)
        : subject(subject), studentName(studentName), course(course) {}

    void addGrade(int grade) {
        grades.push_back(grade);
    }

    double calculateAverageGrade() const {
        if (grades.empty()) {
            return 0.0;
        }

        double total = 0.0;
        for (int grade : grades) {
            total += grade;
        }

        return total / grades.size();
    }

    std::string getSubject() const {
        return subject;
    }

    std::string getStudentName() const {
        return studentName;
    }

    const std::vector<int>& getGrades() const {
        return grades;
    }

    void save(std::ofstream& outFile) const override {
        outFile << "Grade Book Details:\n";
        outFile << "Student Name: " << studentName << "\n";
        outFile << "Subject: " << subject << "\n";
        outFile << "Average Grade: " << calculateAverageGrade() << "\n";
        outFile << "Grades: ";
        for (int grade : grades) {
            outFile << grade << " ";
        }
        outFile << "\n";
    }

    std::string getId() const override {
        return studentName;
    }

    void print(std::ostream& os) const override {
        os << "Grade Book Details:\n";
        os << "Student Name: " << studentName << "\n";
        os << "Subject: " << subject << "\n";
        os << "Average Grade: " << calculateAverageGrade() << "\n";
        os << "Grades: ";
        for (int grade : grades) {
            os << grade << " ";
        }
        os << "\n";
    }
};

#endif // GRADEBOOK_H
