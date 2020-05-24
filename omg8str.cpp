#include "omg8str.h"

/* a constructor that encodes a string using omg8 */
omg8str::omg8str(std::string s) {
    std::vector <unsigned long int> int_vector;
    int_vector = omg8str::to128(s);
    this->int_vector = int_vector;
    len = int_vector.size();
}
/* vector 128-bit */
omg8str::omg8str(std::vector<unsigned long int> int_vector) {
    this->int_vector = int_vector;
    len = int_vector.size();
}

int omg8str::length() const {
    return len;
}


void omg8str::change(int position, unsigned char c) {
    int_vector[position] = c;
}

/* Саме кодування */
std::vector<unsigned long int> omg8str::to128(std::string s) {
    std::vector<unsigned long int> int_vector;
    for (auto it = s.cbegin(); it != s.cend(); ++it) {
        std::bitset<8> bits = std::bitset<8>(*it);
        std::string tmp = "";

        if (bits[7] == 0) {
            int_vector.push_back(bits.to_ulong());
        } else {
            std::cout << "String can not be encoded with OMG8" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    return int_vector;
}
/* string decoding*/
std::string omg8str::tostring() const {
    std::string s = "";
    unsigned char tmp;
    std::string::iterator beg;
    beg = s.begin();

    for (auto it = int_vector.cbegin(); it != int_vector.cend(); ++it) {
        tmp = static_cast<unsigned char>(*it);
        s.push_back(tmp);
    }
    return s;
}
/* substrate retrieval function */
omg8str omg8str::slice(int a, int b) {
    if (b == -1) {
        b = len;
    }
    if (a > len || b > len || a < 0 || b < 0 || a > b) {
        std::cout << "Index out of range" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector <unsigned long int> I;
    for (int i = a; i < b; i++) {
        I.push_back(int_vector[i]);
    }
    return omg8str(I);
}

/* Insert substring. Accepts (string) and position (int)*/
void omg8str::insert(omg8str s, int position) {
    omg8str left = slice(0, position);
    omg8str right = slice(position);
    /* Initializes class variables */
    omg8str resulting_string = left + s + right;
    int_vector = resulting_string.int_vector;
    len = resulting_string.len;
}
/* Insert substring. Accepts (char) and position (int)*/
void omg8str::insert(unsigned char c, int position) {
    omg8str A = slice(0, position);
    omg8str B = slice(position);
    A += c;
    int_vector = (A + B).int_vector;
    len += 1;
}
/* substring removal function */
void omg8str::del(int a, int b)
{
    omg8str A = slice(0, a);
    omg8str B = slice(b);

    int_vector = (A + B).int_vector;
    len = (A + B).len;
}
/* substring search function */
int omg8str::isin(omg8str s) {
    for (int i = 0; i < len - s.len; i++) {
        if (slice(i, i + s.len) == s) {
            return i;
        }
    }
    return -1;
}

/* Output operator */
std::ostream& operator<<(std::ostream& output, const omg8str& str) {
    return output << str.tostring();
}

/* Input operator*/
std::istream& operator>>(std::istream& input, omg8str& str) {
    std::string s;
    std::vector <unsigned long int> int_vector;

    input >> s;
    int_vector = omg8str::to128(s);

    str.len = int_vector.size();
    str.int_vector = int_vector;

    return input;
}
/* Overload [] to take the i-th element*/
unsigned char omg8str::operator[](int index) {
    unsigned char tmp;
    if (index >= len) {
        std::cout << "Index out of range" << std::endl;
        exit(EXIT_FAILURE);
    }
    tmp = static_cast<unsigned char>(int_vector[index]);
    return tmp;
}

omg8str::operator int() const {
    int res = 0;
    for (auto it = int_vector.cbegin(); it != int_vector.cend(); ++it) {
        if (*it < 48 || *it > 57) {
            std::cout << "String is not an integer" << std::endl;
            exit(EXIT_FAILURE);
        } else {
            res = res * 10 + (*it - 48);
        }
    }
    return res;
}

bool operator==(const omg8str& a, const omg8str& b) {
    return (a.int_vector == b.int_vector);
}

omg8str operator+(const omg8str& a, const omg8str& b) {
    std::vector <unsigned long int> A = a.int_vector;
    std::vector <unsigned long int> B = b.int_vector;

    for (auto it = B.cbegin(); it != B.cend(); ++it) {
        A.push_back(*it);
    }
    return omg8str(A);
}

omg8str& operator+=(omg8str& self, const omg8str& other) {
    self = self + other;
    return self;
}

omg8str& operator+=(omg8str& self, const unsigned char& other) {
    self = omg8str(self.tostring() += other);
    return self;
}

omg8str operator*(int n, const omg8str& str) {
    omg8str s;
    for (int i = 0; i < n; i++) {
        s += str;
    }
    return s;
}

/* Returns true if the string s is a number in base base */
bool is_number(omg8str s, int base) {
    if (s[0] == '0') {
        return false;
    }
    switch (base) {
        case 2:
            for (int i = 0; i < s.length(); i++) {
                /* Condition for a number in binary */
                if (s[i] - 48 < 0 || s[i] - 48 > 1) {
                    return false;
                }
            }
            return true;
        case 10:
            for (int i = 0; i < s.length(); i++) {
                /* Condition for a number in the decimal system */
                if (s[i] - 48 < 0 || s[i] - 48 > 9) {
                    return false;
                }
            }
            return true;
        case 16:
            for (int i = 0; i < s.length(); i++) {
                /* Condition for a number in the hexadecimal system */
                if (s[i] < 48 || (s[i] > 57 && s[i] < 65) || s[i] > 70) {
                    return false;
                }
            }
            return true;
    }
    std::cout << "Unsupported base" << std::endl;
    exit(EXIT_FAILURE);
}

/* Convert (from) into (to)  */
omg8str convert(omg8str s, int from, int to) {
    omg8str str;
    if (!is_number(s, from)) {
        std::cout << "Wrong base" << std::endl;
        exit(EXIT_FAILURE);
    }
    /* The form is the same */
    if (from == to) {
        return s;
    }
    if (from == 10) {
        int f = int(s);
        std::string tmp;
        int tmpint;
        switch (to) {
            case 2:
                while (f != 0) {
                    tmpint = f % 2;
                    tmp = tmpint + 48;
                    str.insert(tmp, 0);
                    f = (f - tmpint) / 2;
                }
                return str;
            case 16:
                while (f != 0) {
                    tmpint = f % 16;
                    if (tmpint < 10) {
                        tmp = tmpint + 48;
                    } else {
                        tmp = tmpint + 55;
                    }
                    str.insert(tmp, 0);
                    f = (f - tmpint) / 16;
                }
                return str;
        }
    } else if (to == 10) {
        int f = 0;
        int p = 1;
        std::stringstream ss;
        std::string stdstr;
        switch (from) {
            case 2:
                for (int i = s.length() - 1; i >= 0; i--) {
                    f += (s[i] - 48) * p;
                    p *= 2;
                }
                ss << f;
                stdstr = ss.str();
                return omg8str(stdstr);
            case 16:
                for (int i = s.length() - 1; i >= 0; i--) {
                    if ((s[i] > 47 && s[i] < 58)) {
                        f += (s[i] - 48) * p;
                    } else {
                        f += (s[i] - 55) * p;
                    }
                    p *= 16;
                }
                ss << f;
                stdstr = ss.str();
                return omg8str(stdstr);
        }
    } else if (from == 2 && to == 16) {
        str = convert(s, 2);
        return convert(str, 10, 16);
    } else {
        str = convert(s, 16);
        return convert(str, 10, 2);
    }
}
