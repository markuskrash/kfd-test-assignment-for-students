#ifndef KFD_TEST_ASSIGNMENT_FOR_STUDENTS_LIBRARY_H
#define KFD_TEST_ASSIGNMENT_FOR_STUDENTS_LIBRARY_H
#include "bits/stdc++.h"
#include "book.h"
#include "users.h"
using namespace std;
using Clock = chrono::system_clock;

static long daysBetween(const Clock::time_point &a, const Clock::time_point &b) {
    return chrono::duration_cast<chrono::hours>(b - a).count() / 24;
}
struct BorrowRecord {
    string userId;
    string isbn;
    Clock::time_point borrowDate;
    bool returned = false;
    Clock::time_point returnDate;

    BorrowRecord(string u, string i) : userId(u), isbn(i), borrowDate(Clock::now()), returned(false) {}
};




class Library {
private:
    unordered_map<string, Book> books;
    unordered_map<string, shared_ptr<User>> users;
    vector<BorrowRecord> history;


    static string lower(string s) {
        for (char &c: s) c = tolower((unsigned char) c);
        return s;
    }

public:
    bool addBook(const string &title, const string &author, const string &isbn) {
        if (isbn.empty()) return false;
        auto it = books.find(isbn);

        if (it != books.end()) {
            it->second.title = title;
            it->second.author = author;
            it->second.available = true;
        } else books.emplace(isbn, Book(title, author, isbn));


        return true;
    }

    bool removeBook(const string &isbn) {
        auto it = books.find(isbn);

        if (it == books.end()) return false;

        if (!it->second.available) return false;
        books.erase(it);
        return true;
    }

    void findBook(string isbn) {return;}

    vector<Book> search(const string &q) {
        string s = lower(q);
        vector<Book> out;


        for (auto &kv: books) {
            string t = lower(kv.second.title), a = lower(kv.second.author), i = lower(kv.second.isbn);
            if (t.find(s) != string::npos || a.find(s) != string::npos || i.find(s) != string::npos)
                out.push_back(kv.second);
        }

        return out;
    }

    bool registerUser(const string &name, const string &uid, const string &email, const string &type) {
        if (uid.empty() || users.count(uid)) return false;
        string t = lower(type);

        if (t == "student") users[uid] = make_shared<Student>(name, uid, email);
        else if (t == "faculty") users[uid] = make_shared<Faculty>(name, uid, email);

        else if (t == "guest") users[uid] = make_shared<Guest>(name, uid, email);
        else return false;

        return true;

    }

    shared_ptr<User> findUser(const string &uid) {
        auto it = users.find(uid);


        return it == users.end() ? nullptr : it->second;
    }

    bool borrowBook(const string &uid, const string &isbn) {
        auto u = findUser(uid);

        auto bookit = books.find(isbn);

        if (!u || bookit == books.end()) return false;
        if (!bookit->second.available) return false;

        if (!u->take(isbn)) return false;

        bookit->second.available = false;
        history.emplace_back(uid, isbn);

        return true;
    }

    bool returnBook(const string &uid, const string &isbn) {
        auto u = findUser(uid);
        auto bookit = books.find(isbn);

        if (!u || bookit == books.end()) return false;
        if (!u->has(isbn)) return false;

        u->giveBack(isbn);
        bookit->second.available = true;

        for (auto it = history.rbegin(); it != history.rend(); ++it) {
            if (!it->returned && it->userId == uid && it->isbn == isbn) {
                it->returned = true;
                it->returnDate = Clock::now();
                return true;
            }
        }
        return true;
    }

    vector<BorrowRecord> overdu() const {
        vector<BorrowRecord> out;
        auto now = Clock::now();
        for (const auto &r: history) {
            if (r.returned) continue;

            auto userid = users.find(r.userId);
            if (userid == users.end()) continue;

            int allowed = userid->second->getBorrowDays();
            long days = daysBetween(r.borrowDate, now);
            if (days > allowed) out.push_back(r);

        }
        return out;
    }

    void listBooks() const {
        if (books.empty()) {
            cout << "No books(\n";

            return;
        }
        for (auto &kv: books)
            cout << kv.second.isbn << " |X| " << kv.second.title << " |X| " << kv.second.author << " |X| " << (kv.second.available ? "+" : "-") << "\n";
    }

    void listUsers() const {
        if (users.empty()) {
            cout << "No users\n";

            return;
        }
        for (auto &kv: users)
            cout << kv.second->getId() << " |X| " << kv.second->getName() << " |X| " << kv.second->typeName() << " |X| borrowed:"
                 << kv.second->getBorrowed().size() << "\n";
    }
};

#endif //KFD_TEST_ASSIGNMENT_FOR_STUDENTS_LIBRARY_H
