#include "bits/stdc++.h"
#include "library.h"
using namespace std;

string readNonEmpty(const string& prompt){
    string s;
    while(true){
        cout<<prompt;
        if(!getline(cin,s)) return string();
        auto pos = s.find_first_not_of(" \t\r\n");
        if(pos==string::npos) { cout<<"Empty input\n"; continue; }
        auto end = s.find_last_not_of(" \t\r\n");
        return s.substr(pos, end-pos+1);
    }
}


int readInt(const string &prompt, int minv, int maxv) {
    string s;


    while (true) {
        cout << prompt;
        if (!getline(cin, s)) return minv;
        try {
            int v = stoi(s);

            if (v < minv || v > maxv) {
                cout << "Out of range\n";

                continue;
            }
            return v;
        }
        catch (...) { cout << "Invalid number\n"; }
    }
}

int main() {
    Library lib;
    while (true) {
        cout << "\n1.Add book 2.Remove book 3.Register user 4.Borrow 5.Return 6.Search 7.Overdue 8.List books/users 0.Exit\n";
        int c = readInt("Choice: ", 0, 8);
        if (c == 0) break;
        if (c == 1) {
            string t = readNonEmpty("Title: "), a = readNonEmpty("Author: "), i = readNonEmpty("ISBN: ");
            if (lib.addBook(t, a, i)) cout << "Added\n"; else cout << "Failed\n";
        } else if (c == 2) {
            string i = readNonEmpty("ISBN: ");
            cout << (lib.removeBook(i) ? "Removed\n" : "Cant remove!\n");
        } else if (c == 3) {
            string n = readNonEmpty("Name: "), id = readNonEmpty("UserID: "), e = readNonEmpty("Email: ");
            cout << "Type (student/faculty/guest): ";
            string type;
            getline(cin, type);
            if (type.empty()) type = "student";
            cout << (lib.registerUser(n, id, e, type) ? "Registered\n" : "Failed \n");
        } else if (c == 4) {
            string uid = readNonEmpty("UserID: "), isbn = readNonEmpty("ISBN: ");
            cout << (lib.borrowBook(uid, isbn) ? "Borrowed\n" : "Cannot borrow\n");
        } else if (c == 5) {
            string uid = readNonEmpty("UserID: "), isbn = readNonEmpty("ISBN: ");
            cout << (lib.returnBook(uid, isbn) ? "Returned\n" : "Cannot return\n");
        } else if (c == 6) {
            string q = readNonEmpty("Query: ");
            auto res = lib.search(q);
            if (res.empty()) cout << "No matches\n";
            else
                for (auto &b: res)
                    cout << b.isbn << " |X| " << b.title << " |X| " << b.author << " |X| " << (b.available ? "+" : "-")
                         << "\n";
        } else if (c == 7) {
            auto list = lib.overdu();
            if (list.empty()) cout << "No overdu\n";
            else
                for (auto &r: list) {
                    auto days = daysBetween(r.borrowDate, Clock::now());
                    cout << r.userId << " |X| " << r.isbn << " |X| days since borrow: " << days << "\n";
                }
        } else if (c == 8) {
            lib.listBooks();
            lib.listUsers();
        }
    }
    return 0;
}
