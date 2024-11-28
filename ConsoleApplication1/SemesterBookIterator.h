#ifndef SEMESTERBOOKITERATOR_H
#define SEMESTERBOOKITERATOR_H

#include <vector>
#include <memory>
#include "LibraryItem.h"

class SemesterBookIterator {
private:
    std::vector<std::unique_ptr<LibraryItem>>::iterator iter;

public:
    SemesterBookIterator(std::vector<std::unique_ptr<LibraryItem>>::iterator it) : iter(it) {}

    LibraryItem& operator*() {
        return **iter;
    }

    LibraryItem* operator->() {
        return iter->get();
    }

    
    SemesterBookIterator& operator++() {
        ++iter;
        return *this;
    }

    bool operator==(const SemesterBookIterator& other) const {
        return iter == other.iter;
    }

    bool operator!=(const SemesterBookIterator& other) const {
        return iter != other.iter;
    }
};

#endif
#pragma once
