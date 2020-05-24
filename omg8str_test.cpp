#include <fstream>

/* Including omg8string class */
#include "omg8str.h"

int main(int arc, char *argv[]) {
    char ch;
    int i, a, b;
    std::string temp;
    omg8str input, input_file;
    omg8str s1("10101"), s2("A4F6"), s3("1995");

    std::cout << "Enter a value: 0 - read from console, 1 - read from file: ";
    std::cin >> i;
    /* Якщо 1, то читаємо з файлу In.txt */
    if (i) {
        std::cout << "Reading from file..." << std::endl;
        std::ifstream reader;
        reader.open("In.txt");

        reader >> input;
        reader.close();
    } else {
        std::cout << "Reading from console..." << std::endl;
        std::cout << "Enter a string: ";
        std::cin >> input;
    }

    /* 1) Виведення */
    std::cout << "1) " << input << std::endl;

    /* 2) Взяття i-го символу */
    std::cout << "Enter a position of an element: ";
    std::cin >> i;
    char c = input[i];
    std::cout << "2) " << c << " (" << i+1 << " symbol)" << std::endl;

    /* 3) Видалення підрядку */
    std::cout << "Enter positions to delete a substring: ";
    std::cin >> a >> b;
    input.del(a, b);
    std::cout << "3) " << input << " (deleted substring from " << a << " to " << b << ")" << std::endl;

    /* 4) Вставка підрядку */
    std::cout << "Enter a position to insert a substring: ";
    std::cin >> i;
    std::cout << "Enter a substring to insert at a position: ";
    std::cin >> temp;
    input.insert(omg8str(temp), i);
    std::cout << "4) " << input << " (added a string: \"" << temp << "\")" << std::endl;

    /* 5) Копіювання підрядку */
    std::cout << "Enter two positions to copy a string: ";
    std::cin >> a >> b;
    omg8str slice = input.slice(a, b);
    std::cout << "5) " << slice << " (taken slice from " << a << " to " << b << ")" << std::endl;

    /* 6) Пошук підрядку */
    std::cout << "Enter a substring to search: ";
    std::cin >> temp;
    int position = input.isin(omg8str(temp));
    std::cout << "6) " << position << " (show the position of a substring \"" << temp << "\" ocurring in input)" << std::endl;

    /* 7) Конкатенація */
    std::cout << "Enter a string to concatenate: ";
    std::cin >> temp;
    omg8str add(temp);
    omg8str result = input + add;
    std::cout << "7) " << result << " (concatenates input with \"" << temp << "\")" << std::endl;

    /* 8) Чи є числом */
    std::cout << "8) Testing the number:" << std::endl;
    std::cout << "10101 in base 2: " << is_number(s1, 2) << std::endl;
    std::cout << "A4F6 in base 2: " << is_number(s2, 2) << std::endl;
    std::cout << "A4F6 in base 16: " << is_number(s2, 16) << std::endl;

    /* 10) Переведення */
    std::cout << "10) Testing number conversions:" << std::endl;
    std::cout << "10101 from 2 to 16: " << convert(s1, 2, 16) << std::endl;
    std::cout << "A4F6 from 16 to 10: " << convert(s2, 16, 10) << std::endl;
    std::cout << "1995 16 to 2: " << convert(s3, 16, 2) << std::endl;

    /* 11) Заміна символу */
    std::cout << "Enter a position and a symbol to change: ";
    std::cin >> i >> ch;
    input.change(i, ch);
    std::cout << "11) " << input << " (changes " << i << " symbol to \"" << ch << "\")" << std::endl;

    /* 12) Додавання до кінця і початку */
    std::cout << "Enter a symbol to add both to start and end of the string: ";
    std::cin >> ch;
    input.insert(ch); input.insert(ch, input.length());
    std::cout << "12) " << input << " (adds \"" << ch << "\" to both sides of the string)" << std::endl;

    /* 13) Запис у файл */
    std::ofstream writer;
    writer.open("Out.txt");

    writer << input;
    writer.close();
    std::cout << "13) string input has been written into file" << std::endl;
}
