#ifndef BITSTRING_H
#define BITSTRING_H

#include <iostream>
#include <string>

class BitString {
private:
    unsigned char* bitArray;
    unsigned char* end;
    size_t size;

public:

    BitString(const std::string& bitString);
    BitString(size_t size);
    BitString(const BitString& other);
    ~BitString();


    BitString& operator=(const BitString& other);
    BitString operator+(const BitString& other) const;
    BitString operator-(const BitString& other) const;
    BitString operator&(const BitString& other) const;
    BitString operator|(const BitString& other) const;
    BitString operator^(const BitString& other) const;
    BitString operator~() const;  

    BitString& operator+=(const BitString& other);
    BitString& operator-=(const BitString& other);

    bool operator==(const BitString& other) const;
    bool operator!=(const BitString& other) const;
    bool operator<(const BitString& other) const;
    bool operator>(const BitString& other) const;
    bool operator<=(const BitString& other) const;
    bool operator>=(const BitString& other) const;

    friend std::ostream& operator<<(std::ostream& os, const BitString& bitStr);
    size_t getSize() const { return size; } 
};

#endif 