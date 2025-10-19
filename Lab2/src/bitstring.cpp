#include "bitstring.h"
#include <stdexcept>
#include <algorithm>
#include <cctype>

void BitString::validate_bits() {
    for (size_t i = 0; i < data_.Size(); ++i) {
        if (data_.Data()[i] != 0 && data_.Data()[i] != 1) {
            throw std::invalid_argument("BitString может содержать только 0 и 1");
        }
    }
}

void BitString::normalize() {
    if (data_.IsEmpty()) {
        data_.PushBack(0);
        return;
    }
    size_t leading_zeros = 0;
    for (size_t i = data_.Size(); i > 0; --i) {
        if (data_.Data()[i - 1] == 0) {
            leading_zeros++;
        } else {
            break;
        }
    }
    if (leading_zeros > 0 && leading_zeros < data_.Size()) {
         data_.Erase(data_.Size() - leading_zeros, data_.Size());
    } else if (leading_zeros == data_.Size()) {
        data_.Clear();
        data_.PushBack(0);
    }
    if (data_.IsEmpty()) {
        data_.PushBack(0);
    }
}

int BitString::compare_magnitude(const Vector& a, const Vector& b) {
    if (a.Size() != b.Size()) {
        return a.Size() > b.Size() ? 1 : -1;
    }
    for (int i = static_cast<int>(a.Size()) - 1; i >= 0; --i) {
        if (a.Data()[i] != b.Data()[i]) {
            return a.Data()[i] > b.Data()[i] ? 1 : -1;
        }
    }
    return 0;
}

BitString::BitString() : data_{} {
    data_.PushBack(0);
}

BitString::BitString(size_t n, unsigned char t) : data_(n, t) {
    validate_bits(); 
    normalize(); 
}

BitString::BitString(const std::string &s) {
    std::string clean;
    for (char ch : s) {
        if (ch == '0') {
            clean += '0';
        } else if (ch == '1') {
            clean += '1';
        } else if (std::isspace(ch)) {
            continue; 
        } else {
            throw std::invalid_argument("Недопустимые символы");
        }
    }

    if (clean.empty()) {
        data_.PushBack(0);
    } else {
        for (int i = static_cast<int>(clean.size()) - 1; i >= 0; --i) {
            data_.PushBack(clean[i] == '1' ? 1 : 0);
        }
    }
    normalize(); 
}

BitString::BitString(const BitString &other) : data_(other.data_) {}

BitString::BitString(BitString &&other) noexcept : data_(std::move(other.data_)) {}

BitString::BitString(const std::initializer_list<unsigned char> &init) : data_() {
    if (init.size() == 0) {
        data_.PushBack(0);
    } else {
        const unsigned char* arr = init.begin();
        size_t n = init.size();
        for (size_t i = 0; i < n; ++i) {
            unsigned char val = arr[n - 1 - i];
            if (val != 0 && val != 1) {
                throw std::invalid_argument("BitString может содержать только 0 и 1");
            }
            data_.PushBack(val);
        }
    }
    normalize(); 
}

BitString::~BitString() {} 

BitString BitString::add(const BitString &other1, const BitString &other2) {
    BitString result;
    result.data_.Clear(); 

    size_t max_size = std::max(other1.data_.Size(), other2.data_.Size());
    unsigned char carry = 0;
    result.data_.Reserve(max_size + 1); 

    for (size_t i = 0; i < max_size || carry; ++i) {
        unsigned char bit_a = (i < other1.data_.Size()) ? other1.data_.Data()[i] : 0;
        unsigned char bit_b = (i < other2.data_.Size()) ? other2.data_.Data()[i] : 0;

        unsigned char sum = bit_a + bit_b + carry;
        result.data_.PushBack(sum % 2);
        carry = sum / 2; 
    }

    result.normalize(); 
    return result;
}

BitString BitString::subtract(const BitString &other1, const BitString &other2) {
    if (other1.is_less(other2)) {
        throw std::invalid_argument("Вычитание дает отрицательный результат");
    }

    BitString result;
    result.data_.Clear(); 

    result.data_.Reserve(other1.data_.Size()); 
    int borrow = 0;

    for (size_t i = 0; i < other1.data_.Size(); ++i) {
        int bit_a = other1.data_.Data()[i];
        int bit_b = (i < other2.data_.Size()) ? other2.data_.Data()[i] : 0;

        int diff = bit_a - bit_b - borrow;
        if (diff < 0) {
            diff += 2; 
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.data_.PushBack(static_cast<unsigned char>(diff));
    }

    result.normalize(); 
    return result;
}

BitString BitString::copy(const BitString &other) {
    return BitString(other); 
}

bool BitString::equals(const BitString &other) const {
    return compare_magnitude(this->data_, other.data_) == 0;
}

bool BitString::is_greater(const BitString &other) const {
    return compare_magnitude(this->data_, other.data_) > 0;
}

bool BitString::is_less(const BitString &other) const {
    return compare_magnitude(this->data_, other.data_) < 0;
}

BitString BitString::bit_and(const BitString &other1, const BitString &other2) {
    BitString result;
    result.data_.Clear();

    size_t max_size = std::max(other1.data_.Size(), other2.data_.Size());
    result.data_.Reserve(max_size);

    for (size_t i = 0; i < max_size; ++i) {
        unsigned char bit_a = (i < other1.data_.Size()) ? other1.data_.Data()[i] : 0;
        unsigned char bit_b = (i < other2.data_.Size()) ? other2.data_.Data()[i] : 0;
        result.data_.PushBack(bit_a & bit_b); 
    }
    result.normalize(); 
    return result;
}

BitString BitString::bit_or(const BitString &other1, const BitString &other2) {
    BitString result;
    result.data_.Clear();

    size_t max_size = std::max(other1.data_.Size(), other2.data_.Size());
    result.data_.Reserve(max_size);

    for (size_t i = 0; i < max_size; ++i) {
        unsigned char bit_a = (i < other1.data_.Size()) ? other1.data_.Data()[i] : 0;
        unsigned char bit_b = (i < other2.data_.Size()) ? other2.data_.Data()[i] : 0;
        result.data_.PushBack(bit_a | bit_b); 
    }
    result.normalize(); 
    return result;
}

BitString BitString::bit_xor(const BitString &other1, const BitString &other2) {
    BitString result;
    result.data_.Clear();

    size_t max_size = std::max(other1.data_.Size(), other2.data_.Size());
    result.data_.Reserve(max_size);

    for (size_t i = 0; i < max_size; ++i) {
        unsigned char bit_a = (i < other1.data_.Size()) ? other1.data_.Data()[i] : 0;
        unsigned char bit_b = (i < other2.data_.Size()) ? other2.data_.Data()[i] : 0;
        result.data_.PushBack(bit_a ^ bit_b); 
    }
    result.normalize(); 
    return result;
}

BitString BitString::bit_not() const {
    BitString result;
    result.data_.Clear();

    result.data_.Reserve(this->data_.Size()); 

    for (size_t i = 0; i < this->data_.Size(); ++i) {
        result.data_.PushBack(1 - this->data_.Data()[i]); 
    }
    result.normalize(); 
    return result;
}

BitString BitString::assign_add(const BitString &other) const {
    return BitString::add(*this, other);
}

BitString BitString::assign_subtract(const BitString &other) const {
    return BitString::subtract(*this, other);
}

void BitString::print(std::ostream &os) const {
    if (data_.IsEmpty()) {
        os << "0";
        return;
    }

    for (size_t i = data_.Size(); i > 0; --i) {
        os << static_cast<int>(data_.Data()[i-1]);
    }
}