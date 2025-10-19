#pragma once
#include "vector.h"
#include <string>
#include <initializer_list>
#include <ostream>
#include <cstddef>

class BitString {
public:
    BitString(); 
    BitString(size_t n, unsigned char t = 0); 
    BitString(const std::string &s); 
    BitString(const BitString &other);
    BitString(BitString &&other) noexcept; 
    BitString(const std::initializer_list<unsigned char> &init); 
    ~BitString(); 

    static BitString add(const BitString &other1, const BitString &other2);
    static BitString subtract(const BitString &other1, const BitString &other2);
    static BitString copy(const BitString &other); 

    bool equals(const BitString &other) const;
    bool is_greater(const BitString &other) const;
    bool is_less(const BitString &other) const;

    static BitString bit_and(const BitString &other1, const BitString &other2);
    static BitString bit_or(const BitString &other1, const BitString &other2);
    static BitString bit_xor(const BitString &other1, const BitString &other2);
    BitString bit_not() const;

    BitString assign_add(const BitString &other) const;
    BitString assign_subtract(const BitString &other) const;

    void print(std::ostream &os) const;

private:
    Vector data_;
    void validate_bits();
    void normalize();  
    static int compare_magnitude(const Vector& a, const Vector& b); 
};