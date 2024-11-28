#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>
#include <fstream> 
#include "LibraryItem.h"

class Book : public LibraryItem {
private:
    std::string udc;
    std::string author;
    std::string title;
    std::string publisher;
    int year;

public:
    // Конструктор ініціалізації
    Book(const std::string& udc, const std::string& author, const std::string& title, const std::string& publisher, int year)
        : udc(udc), author(author), title(title), publisher(publisher), year(year) {}

    // Конструктор копіювання
    Book(const Book& other)
        : udc(other.udc), author(other.author), title(other.title), publisher(other.publisher), year(other.year) {}

    // Конструктор переміщення
    Book(Book&& other) noexcept
        : udc(std::move(other.udc)), author(std::move(other.author)), title(std::move(other.title)), publisher(std::move(other.publisher)), year(other.year) {
        other.year = 0;
    }

    // Оператор присвоєння копіюванням
    Book& operator=(const Book& other) {
        if (this != &other) {
            udc = other.udc;
            author = other.author;
            title = other.title;
            publisher = other.publisher;
            year = other.year;
        }
        return *this;
    }

    
    Book& operator=(Book&& other) noexcept {
        if (this != &other) {
            udc = std::move(other.udc);
            author = std::move(other.author);
            title = std::move(other.title);
            publisher = std::move(other.publisher);
            year = other.year;
            other.year = 0;
        }
        return *this;
    }

    ~Book() {}

  
    std::string getUdc() const {
        return udc;
    }

    std::string getAuthor() const {
        return author;
    }

    std::string getTitle() const {
        return title;
    }

    std::string getPublisher() const {
        return publisher;
    }

    int getYear() const {
        return year;
    }


    void setUdc(const std::string& udc) {
        this->udc = udc;
    }

    void setAuthor(const std::string& author) {
        this->author = author;
    }

    void setTitle(const std::string& title) {
        this->title = title;
    }

    void setPublisher(const std::string& publisher) {
        this->publisher = publisher;
    }

    void setYear(int year) {
        this->year = year;
    }

    // Перевантаження віртуального методу save
    void save(std::ofstream& outFile) const override {
        outFile << "Book Information:\n";
        outFile << "UDC: " << udc << "\n";
        outFile << "Author: " << author << "\n";
        outFile << "Title: " << title << "\n";
        outFile << "Publisher: " << publisher << "\n";
        outFile << "Year: " << year << "\n";
    }

    // Перевантаження віртуального методу getId
    std::string getId() const override {
        return udc;
    }

    // Перевантаження віртуального методу print
    void print(std::ostream& os) const override {
        os << "Book Information:\n";
        os << "UDC: " << udc << "\n";
        os << "Author: " << author << "\n";
        os << "Title: " << title << "\n";
        os << "Publisher: " << publisher << "\n";
        os << "Year: " << year << "\n";
    }

    // Метод для визначення відповідності книги пошуковим критеріям
    bool matchesCriteria(const std::string& searchTerm) const {
        return (udc.find(searchTerm) != std::string::npos) ||
            (author.find(searchTerm) != std::string::npos) ||
            (title.find(searchTerm) != std::string::npos) ||
            (publisher.find(searchTerm) != std::string::npos) ||
            (std::to_string(year).find(searchTerm) != std::string::npos);
    }
};

#endif // BOOK_H
