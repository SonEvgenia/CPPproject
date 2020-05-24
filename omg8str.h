#ifndef OMG8STR_H
#define OMG8STR_H

#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <sstream>
#include <stdlib.h>

class omg8str {
public:
    /* a constructor that encodes a string using omg8 */
    omg8str(std::string s = "");
    /* method that returns the length of the string */
    int length() const;
    /* Change symbol on the position given  */
    void change(int, unsigned char);
    /* substrate retrieval function */
    omg8str slice(int, int b = -1);
    /* substring insertion function */
    void insert(omg8str, int position = 0);
    /* character insertion function */
    void insert(unsigned char, int position = 0);
    /* substring removal function */
    void del(int, int);
    /* substring search function (returns the first position
     * from which the searched substring begins) */
    int isin(omg8str);


    /* overloading */
    /* overload << for output*/
    friend std::ostream& operator<<(std::ostream&, const omg8str&);
    /* overload >> for input */
    friend std::istream& operator>>(std::istream&, omg8str&);
    /* Overload [] to take the i-th element*/
    unsigned char operator[](int);
    /* Overload == for comparison */
    friend bool operator==(const omg8str&, const omg8str&);
    /* Overload + for concatenation */
    friend omg8str operator+(const omg8str&, const omg8str&);
    /* Overload + = to concatenate with string */
    friend omg8str& operator+=(omg8str&, const omg8str&);
    /* Overload + = to join a character */
    friend omg8str& operator+=(omg8str&, const unsigned char&);
    /* Overload int() */
    operator int() const;

private:
    /* length  */
    int len;
    /* vector 128-bit */
    std::vector <unsigned long int> int_vector;
    /* converting a string to a 128-bit vector */
    static std::vector <unsigned long int> to128(std::string);
    /* string decoding*/
    std::string tostring() const;
    /* a constructor that defines an omg8 string based on a 128-bit vector */
    omg8str(std::vector <unsigned long int>);
};

/* Helper functions */
/* Checks if a string is a number */
bool is_number(omg8str, int base = 10);
omg8str convert(omg8str, int from, int to = 10);

#endif