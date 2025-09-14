#ifndef KFD_TEST_ASSIGNMENT_FOR_STUDENTS_USERS_H
#define KFD_TEST_ASSIGNMENT_FOR_STUDENTS_USERS_H
#include "bits/stdc++.h"
using namespace std;

class User {
protected:
    string name, id, email;
    unordered_set<string> borrowed;
public:

    User() = default;

    User(string n, string uid, string e) : name(n), id(uid), email(e) {}

    virtual ~User() = default;

    virtual int getMaxBooks() const = 0;

    virtual int getBorrowDays() const = 0;

    virtual double getFinePerDay() const = 0;

    bool canBorrow() const { return (int) borrowed.size() < getMaxBooks(); }

    bool has(const string &isbn) const { return borrowed.count(isbn) > 0; }

    bool take(const string &isbn) {
        if (!canBorrow() || has(isbn)) return false;
        borrowed.insert(isbn);
        return true;
    }

    bool giveBack(const string &isbn) { return borrowed.erase(isbn) > 0; }

    virtual string typeName() const = 0;

    string getId(){return this->id;}
    string getName(){return this->name;}
    string getEmail(){return this->email;}
    unordered_set<string> getBorrowed(){return this->borrowed;}
};

class Student : public User {
public:
    Student(string n, string i, string e) : User(n, i, e) {}

    int getMaxBooks() const override { return 3; }

    int getBorrowDays() const override { return 14; }

    double getFinePerDay() const override { return 0.5; }

    string typeName() const override { return "Student"; }
};

class Faculty :public User {
public:
    Faculty(string n, string i, string e) : User(n, i, e) {}

    int getMaxBooks() const override { return 10; }

    int getBorrowDays() const override { return 30; }

    double getFinePerDay() const override { return 0.25; }

    string typeName() const override { return "Faculty"; }
};

class Guest :public User {
public:
    Guest(string n, string i, string e) : User(n, i, e) {}

    int getMaxBooks() const override { return 1; }

    int getBorrowDays() const override { return 7; }

    double getFinePerDay() const override { return 1.0; }

    string typeName() const override { return "Guest"; }
};

#endif //KFD_TEST_ASSIGNMENT_FOR_STUDENTS_USERS_H
