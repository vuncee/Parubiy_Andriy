#ifndef SEMESTERBOOK_H
#define SEMESTERBOOK_H

#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>
#include "LibraryItem.h"
#include "Book.h"
#include "GradeBook.h"
#include "SemesterBookIterator.h"

class SemesterBook {
private:
    std::vector<std::unique_ptr<LibraryItem>> items;

public:
    void addLibraryItem(std::unique_ptr<LibraryItem> item) {
        items.push_back(std::move(item));
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Error opening file for writing.\n";
            return;
        }

        for (const auto& item : items) {
            item->save(outFile);
            outFile << "\n";  // Add a new line after each item for readability
        }

        outFile.close();
        std::cout << "Data saved to " << filename << " successfully.\n";
    }

    void loadFromFile(const std::string& filename) {
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

                std::getline(inFile, line);  // UDC
                udc = line.substr(line.find(":") + 2);

                std::getline(inFile, line);  // Author
                author = line.substr(line.find(":") + 2);

                std::getline(inFile, line);  // Title
                title = line.substr(line.find(":") + 2);

                std::getline(inFile, line);  // Publisher
                publisher = line.substr(line.find(":") + 2);

                std::getline(inFile, line);  // Year
                year = std::stoi(line.substr(line.find(":") + 2));

                addLibraryItem(std::make_unique<Book>(udc, author, title, publisher, year));
            }
            else if (line == "Grade Book Details:") {
                std::string subject, studentName;
                std::vector<int> grades;
                int grade;

                std::getline(inFile, line);  // Student Name
                studentName = line.substr(line.find(":") + 2);

                std::getline(inFile, line);  // Subject
                subject = line.substr(line.find(":") + 2);

                std::getline(inFile, line);  // Average Grade (skipped)
                std::getline(inFile, line);  // Grades
                std::istringstream iss(line.substr(line.find(":") + 2));
                while (iss >> grade) {
                    grades.push_back(grade);
                }

                GradeBook gradeBook(subject, studentName, 0); // Initialize course to 0
                for (int g : grades) {
                    gradeBook.addGrade(g);
                }

                addLibraryItem(std::make_unique<GradeBook>(gradeBook));
            }
        }

        inFile.close();
        std::cout << "Data loaded from " << filename << " successfully.\n";
    }

    void displayItems() const {
        for (const auto& item : items) {
            std::cout << *item << std::endl;
        }
    }

    SemesterBookIterator begin() {
        return SemesterBookIterator(items.begin());
    }

    SemesterBookIterator end() {
        return SemesterBookIterator(items.end());
    }
};

#endif // SEMESTERBOOK_H
