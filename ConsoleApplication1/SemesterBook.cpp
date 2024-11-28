#include "SemesterBook.h"
#include "Book.h"
#include "GradeBook.h"
#include <iostream>
#include <fstream>
#include <sstream>

void SemesterBook::addLibraryItem(std::unique_ptr<LibraryItem> item) {
    items.push_back(std::move(item));
}

void SemesterBook::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    for (const auto& item : items) {
        item->save(outFile);
    }

    outFile.close();
}

void SemesterBook::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Error opening file for reading.\n";
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        if (line == "Book Information:") {
            std::string udc, author, title, publisher;
            int year;

            std::getline(inFile, line); // UDC
            udc = line.substr(line.find(":") + 2);

            std::getline(inFile, line); // Author
            author = line.substr(line.find(":") + 2);

            std::getline(inFile, line); // Title
            title = line.substr(line.find(":") + 2);

            std::getline(inFile, line); // Publisher
            publisher = line.substr(line.find(":") + 2);

            std::getline(inFile, line); // Year
            year = std::stoi(line.substr(line.find(":") + 2));

            std::cout << "Loaded Book: " << udc << ", " << author << ", " << title << ", " << publisher << ", " << year << "\n";

            addLibraryItem(std::make_unique<Book>(udc, author, title, publisher, year));
        }
        else if (line == "Grade Book Details:") {
            std::string studentName, subject;
            std::vector<int> grades;

            std::getline(inFile, line); // Student Name
            studentName = line.substr(line.find(":") + 2);

            std::getline(inFile, line); // Subject
            subject = line.substr(line.find(":") + 2);

            std::getline(inFile, line); // Grades
            std::istringstream gradeStream(line.substr(line.find(":") + 2));
            int grade;
            while (gradeStream >> grade) {
                grades.push_back(grade);
            }

            std::cout << "Loaded GradeBook: " << studentName << ", " << subject << ", Grades: ";
            for (int g : grades) {
                std::cout << g << " ";
            }
            std::cout << "\n";

            GradeBook gradeBook(subject, studentName, 0);
            for (int grade : grades) {
                gradeBook.addGrade(grade);
            }

            addLibraryItem(std::make_unique<GradeBook>(gradeBook));
        }
    }

    inFile.close();
    std::cout << "Data loaded from " << filename << " successfully.\n";
}
