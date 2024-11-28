#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include "Book.h"
#include "GradeBook.h"
#include "LibraryItem.h"
#include "SemesterBook.h"

void saveToFile(const Book& book, const GradeBook& gradeBook) {
    std::ofstream outFile("library_data.txt", std::ios::app);
    if (outFile.is_open()) {
        book.save(outFile);
        gradeBook.save(outFile);
        outFile.close();
        std::cout << "Data saved to library_data.txt successfully.\n";
    }
    else {
        std::cerr << "Error opening file for writing.\n";
    }
}

void recordBook(SemesterBook& semesterBook) {
    std::string udc, author, title, publisher;
    int year;

    std::cout << "Enter UDC: ";
    std::getline(std::cin, udc);

    std::cout << "Enter Author: ";
    std::getline(std::cin, author);

    std::cout << "Enter Title: ";
    std::getline(std::cin, title);

    std::cout << "Enter Publisher: ";
    std::getline(std::cin, publisher);

    std::cout << "Enter Year: ";
    std::cin >> year;
    std::cin.ignore(); 

    Book book(udc, author, title, publisher, year);
    semesterBook.addLibraryItem(std::make_unique<Book>(book));

    std::cout << "\nBook Information:\n";
    std::cout << "UDC: " << book.getUdc() << "\n";
    std::cout << "Author: " << book.getAuthor() << "\n";
    std::cout << "Title: " << book.getTitle() << "\n";
    std::cout << "Publisher: " << book.getPublisher() << "\n";
    std::cout << "Year: " << book.getYear() << "\n";
}

void recordGrades(SemesterBook& semesterBook) {
    std::string subject, studentName;
    std::cout << "\nEnter the subject: ";
    std::cin.ignore();
    std::getline(std::cin, subject);

    std::cout << "Enter student name: ";
    std::getline(std::cin, studentName);

    GradeBook gradeBook(subject, studentName, 0);
    int grade;
    std::cout << "Enter grades (enter -1 to finish): ";
    while (std::cin >> grade && grade != -1) {
        gradeBook.addGrade(grade);
    }
    std::cin.ignore();

    semesterBook.addLibraryItem(std::make_unique<GradeBook>(gradeBook));

    std::cout << "\nGrade Book Details:\n";
    std::cout << "Student Name: " << gradeBook.getStudentName() << "\n";
    std::cout << "Subject: " << gradeBook.getSubject() << "\n";
    std::cout << "Average Grade: " << gradeBook.calculateAverageGrade() << "\n";
}

void loadFromFile(SemesterBook& semesterBook) {
    semesterBook.loadFromFile("library_data.txt");
    semesterBook.displayItems();  // Display loaded items
}

int main() {
    SemesterBook semesterBook;
    char choice;

    while (true) {
        std::cout << "Menu:\n";
        std::cout << "1. Write down Book Info\n";
        std::cout << "2. Write down Grades Info \n";
        std::cout << "3. Read From File\n";
        std::cout << "4. Exit\n";
        std::cout << "Choose: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case '1':
            recordBook(semesterBook);
            break;
        case '2':
            recordGrades(semesterBook);
            break;
        case '3':
            loadFromFile(semesterBook);
            break;
        case '4':
            std::cout << "Program terminated.\n";
            return 0;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }

        std::cout << "\nWhat would you like to do next?\n";
        std::cout << "1. Continue recording\n";
        std::cout << "2. Record other information\n";
        std::cout << "3. Save everything to file\n";
        std::cout << "4. Exit program\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;
        std::cin.ignore();

        if (choice == '1') {
            continue; // Continue recording current information
        }
        else if (choice == '2') {
            std::cout << "What information would you like to record?\n";
            std::cout << "1. Book Info\n";
            std::cout << "2. Grades Info\n";
            std::cout << "Choose an option: ";
            std::cin >> choice;
            std::cin.ignore();

            if (choice == '1') {
                recordBook(semesterBook);
            }
            else if (choice == '2') {
                recordGrades(semesterBook);
            }
            else {
                std::cout << "Invalid choice. Returning to main menu.\n";
            }
        }
        else if (choice == '3') {
            semesterBook.saveToFile("library_data.txt");
        }
        else if (choice == '4') {
            std::cout << "Exiting program.\n";
            return 0;
        }
        else {
            std::cout << "Invalid choice. Returning to main menu.\n";
        }
    }

    return 0;
}
