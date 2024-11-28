#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H

#include <string>
#include <ostream>

class LibraryItem {
public:
    virtual ~LibraryItem() = default;

    virtual void save(std::ofstream& outFile) const = 0;
    virtual std::string getId() const = 0;
    virtual void print(std::ostream& os) const = 0;  // Add this line
};

inline std::ostream& operator<<(std::ostream& os, const LibraryItem& item) {
    item.print(os);
    return os;
}

#endif // LIBRARYITEM_H

