#ifndef KFD_TEST_ASSIGNMENT_FOR_STUDENTS_BOOK_H
#define KFD_TEST_ASSIGNMENT_FOR_STUDENTS_BOOK_H
#include "bits/stdc++.h"
using namespace std;

struct Book {
    string title, author, isbn;
    bool available = true;

    Book() = default;

    Book(string t, string a, string i) : title(t), author(a), isbn(i), available(true) {}
};

#endif //KFD_TEST_ASSIGNMENT_FOR_STUDENTS_BOOK_H
