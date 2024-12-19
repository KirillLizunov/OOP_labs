#include "BitString.h"
#include <stdexcept>

BitString::BitString(const std::string& bitString) {
    size = bitString.length();
    bitArray = new unsigned char[size];
    end = bitArray + size;

    unsigned char* ptr = bitArray;

    for (char ch : bitString) {
        if (ch == '0') {
            *ptr = 0;
        } else if (ch == '1') {
            *ptr = 1;
        } else {
            throw std::invalid_argument("Использовать можно только '0' и '1'");
        }
        ++ptr;  
    }
}

BitString::BitString(size_t size) : size(size) {
    bitArray = new unsigned char[size];
    end = bitArray + size;

    unsigned char* ptr = bitArray;


    while (ptr != end) {
        *ptr = 0;
        ++ptr;
    }
}


BitString::BitString(const BitString& other) : size(other.size) {
    bitArray = new unsigned char[size];
    end = bitArray + size;

    unsigned char* src = other.bitArray;
    unsigned char* dest = bitArray;


    while (src != other.end) {
        *dest++ = *src++;
    }
}


BitString::~BitString() {
    delete[] bitArray;
}


BitString& BitString::operator=(const BitString& other) {
    if (this != &other) {

        delete[] bitArray;

        size = other.size;
        bitArray = new unsigned char[size];
        end = bitArray + size;

        unsigned char* src = other.bitArray;
        unsigned char* dest = bitArray;


        while (src != other.end) {
            *dest++ = *src++;
        }
    }
    return *this;
}


BitString BitString::operator+(const BitString& other) const {
    if (size != other.size) {
        throw std::invalid_argument("Битовые строки должны быть одного размера");
    }

    BitString result(size);
    unsigned char* resultPtr = result.bitArray;
    unsigned char* lhsPtr = bitArray;
    unsigned char* rhsPtr = other.bitArray;

    while (lhsPtr != end) {
        *resultPtr++ = *lhsPtr++ | *rhsPtr++;
    }
    return result;
}


BitString BitString::operator-(const BitString& other) const {
    if (size != other.size) {
        throw std::invalid_argument("Битовые строки должны быть одного размера");
    }

    BitString result(size);
    unsigned char* resultPtr = result.bitArray;
    unsigned char* lhsPtr = bitArray;
    unsigned char* rhsPtr = other.bitArray;


    for (size_t i = 0; i < size; ++i) {
        *resultPtr++ = (*lhsPtr++ - *rhsPtr++ + 2) % 2;
    }

    BitString result(size + 1); // бит под знак
    unsigned char* resultPtr = result.bitArray;
    unsigned char* lhsPtr = bitArray;
    unsigned char* rhsPtr = other.bitArray;

    bool carry = false;
    for (size_t i = 0; i < size; ++i) {
        unsigned char lhsBit = lhsPtr[i];
        unsigned char rhsBit = rhsPtr[i];
        unsigned char diff = lhsBit - rhsBit - carry;
        if (diff < 0) {
            diff += 2;
            carry = true;
        } else {
            carry = false;
        }
        resultPtr[i + 1] = diff;
    }
    resultPtr[0] = carry ? 1 : 0; // бит знака

    return result;
}

BitString BitString::operator&(const BitString& other) const {
    return *this - other;
}

BitString BitString::operator|(const BitString& other) const {
    return *this + other;
}

BitString BitString::operator^(const BitString& other) const {
    if (size != other.size) {
        throw std::invalid_argument("Битовые строки должны быть одного размера");
    }

    BitString result(size);
    unsigned char* resultPtr = result.bitArray;
    unsigned char* lhsPtr = bitArray;
    unsigned char* rhsPtr = other.bitArray;


    while (lhsPtr != end) {
        *resultPtr++ = *lhsPtr++ ^ *rhsPtr++;
    }
    return result;
}

BitString BitString::operator~() const {
    BitString result(size);
    unsigned char* resultPtr = result.bitArray;
    unsigned char* lhsPtr = bitArray;


    while (lhsPtr != end) {
        *resultPtr++ = ~(*lhsPtr++) & 0x01;
    }
    return result;
}


BitString& BitString::operator+=(const BitString& other) {
    *this = *this + other;
    return *this;
}

BitString& BitString::operator-=(const BitString& other) {
    *this = *this - other;
    return *this;
}

bool BitString::operator==(const BitString& other) const {
    if (size != other.size) {
        return false;
    }
    for (size_t i = 0; i < size; ++i) {
        if (bitArray[i] != other.bitArray[i]) {
            return false;
        }
    }
    return true;
}

bool BitString::operator!=(const BitString& other) const {
    return !(*this == other);
}

bool BitString::operator<(const BitString& other) const {
    if (size != other.size) {
        return size < other.size;
    }
    for (size_t i = 0; i < size; ++i) {
        if (bitArray[i] < other.bitArray[i]) {
            return true;
        } else if (bitArray[i] > other.bitArray[i]) {
            return false;
        }
    }
    return false;
}

bool BitString::operator>(const BitString& other) const {
    return other < *this;
}

bool BitString::operator<=(const BitString& other) const {
    return !(other < *this);
}

bool BitString::operator>=(const BitString& other) const {
    return !(*this < other);
}

std::ostream& operator<<(std::ostream& os, const BitString& bitStr) {
    for (unsigned char* ptr = bitStr.bitArray; ptr != bitStr.end; ++ptr) {
        os << static_cast<int>(*ptr);
    }
    return os;
}