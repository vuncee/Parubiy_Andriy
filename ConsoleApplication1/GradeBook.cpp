#include "GradeBook.h"

void GradeBook::addGrade(int grade) {
    grades.push_back(grade);
}

double GradeBook::calculateAverageGrade() const {
    if (grades.empty()) {
        return 0.0;
    }

    double total = 0.0;
    for (int grade : grades) {
        total += grade;
    }

    return total / grades.size();
}

std::string GradeBook::getSubject() const {
    return subject;
}

std::string GradeBook::getStudentName() const {
    return studentName;
}
