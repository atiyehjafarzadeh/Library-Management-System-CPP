#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

// ------------ start helper functions ------------ //

int stringToInteger(string str) {
    int result;
    istringstream convert(str);
    if (!(convert >> result))
        throw "Can not convert";

    return result;
}

string numberToString(int num) {
    ostringstream os;
    os << num;
    return os.str();
}

// ------------ end helper functions ------------ //

struct Member {
    std::string first_name;
    std::string last_name;
    std::string code_melli;
    std::string mobile;
    int capacity;
};
struct Book {
    std::string book_name;
    std::string writer_name;
    std::string author_name;
    std::string book_code;
    int first_count;
    int available_count;
};

bool check_code_melli(const string& code_melli, const vector<Member>& members) {
    for (const auto& member : members) {
        if (member.code_melli == code_melli) {
            return true;
        }
    }
    return false;
}

bool check_book_code(string book_code, const vector<Book>& books) {
    for (const auto& book : books) {
        if (book.book_code == book_code) {
            return true;
        }
    }
    return false;
}

bool borrow_book(const string& code_melli, const string& book_code, vector<Member>& members, vector<Book>& books) {
    auto book_itr = find_if(books.begin(), books.end(), [&book_code](const Book& b) { return b.book_code == book_code; });
    if (book_itr == books.end()) {
        cout << "KETABI BA IN CODE NIST!" << endl;
        return false;
    }

    auto member_itr = find_if(members.begin(), members.end(), [&code_melli](const Member& m) { return m.code_melli == code_melli; });
    if (member_itr == members.end()) {
        cout << "OZVI BA IN CODE MELLI NIST!" << endl;
        return false;
    }

    if (book_itr->available_count == 0) {
        cout << "KETAB DAR HAL HAZER MOJOD NIST!" << endl;
        return false;
    }

    if (member_itr->capacity == 0) {
        cout << "ZARFIAT AMANAT KETAB BARAYE IN FARD POR SHDOE!" << endl;
        return false;
    }

    book_itr->available_count--;
    member_itr->capacity--;

    cout << "KETAB BA MOAFAGHIAT BE OZV AMANAT DADE SHOD." << endl;

    return true;
}

bool return_book(const string& code_melli, const string& book_code, vector<Member>& members, vector<Book>& books) {
    auto member_itr = find_if(members.begin(), members.end(), [&code_melli](const Member& m) { return m.code_melli == code_melli; });
    if (member_itr == members.end()) {
        cout << "OZVI BA IN CODE MELLI MOJOD NIST!" << endl;
        return false;
    }

    auto book_itr = find_if(books.begin(), books.end(), [&book_code](const Book& b) { return b.book_code == book_code; });
    if (book_itr == books.end()) {
        cout << "KETABI BA IN COD MOJOD NIST!" << endl;
        return false;
    }

    book_itr->available_count++;
    member_itr->capacity++;

    cout << "KETAB BA MOAFAGHIAT PAS GEREFTE SHOD." << endl;

    return true;
}

void add_member(vector<Member>& members) {
    Member new_member;
    cout << "name: ";
    cin >> new_member.first_name;
    cout << "last_name: ";
    cin >> new_member.last_name;
    cout << "code_melli: ";
    cin >> new_member.code_melli;
    cout << "mobile: ";
    cin >> new_member.mobile;

    new_member.capacity = 3;

    if (check_code_melli(new_member.code_melli, members)) {
        cout << endl << "CODE MELLIU TEKRARIST!" << endl << endl;
    } else {
        members.push_back(new_member);
        cout << endl << "OZVE JADID EZAFE SHOD." << endl << endl;
    }
}

void add_book(vector<Book>& books) {
    Book new_book;
    cout << "book_name: ";
    cin >> new_book.book_name;
    cout << "writer_name: ";
    cin >> new_book.writer_name;
    cout << "author_name: ";
    cin >> new_book.author_name;
    cout << "book_code: ";
    cin >> new_book.book_code;
    cout << "first_count: ";
    cin >> new_book.first_count;

    new_book.available_count = new_book.first_count;

    if (check_book_code(new_book.book_code, books)) {
        cout << endl << "CODE KETAB TEKRARI!" << endl << endl;
    } else {
        books.push_back(new_book);
        cout << endl << "KETAB JADID EZAFE SHOD." << endl << endl;
    }
}

void borrow_book_menu(vector<Member>& members, vector<Book>& books) {
    string code_melli, book_code;
    cout << "CODE MELI OZV RA VARED KONID: ";
    cin >> code_melli;
    cout << "CODE KETAB RO VARED KONID: ";
    cin >> book_code;
    borrow_book(code_melli, book_code, members, books);
}

void return_book_menu(vector<Member>& members, vector<Book>& books) {
    string code_melli, book_code;
    cout << "CODE MELI OZV RA VARED KONID: ";
    cin >> code_melli;
    cout << "CODE KETAB RO VARED KONID: ";
    cin >> book_code;
    return_book(code_melli, book_code, members, books);
}

void show_menu() {
    cout << "1 - ozve jadid" << endl;
    cout << "2 - ketabe jadid" << endl;
    cout << "3 - amanat dadan" << endl;
    cout << "4 - baz pas giri amanat" << endl;
    cout << "0 - exit" << endl << endl;
}

void save_members(const vector<Member>& members) {
    ofstream file("members.txt");
    if (file.is_open()) {
        for (const auto& member : members) {
            file << member.first_name << ',' << member.last_name << ',' << member.code_melli << ',' << member.mobile << ',' << member.capacity << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file!" << endl;
    }
}

void save_books(const vector<Book>& books) {
    ofstream file("books.txt");
    if (file.is_open()) {
        for (const auto& book : books) {
            file << book.book_name << ',' << book.writer_name << ',' << book.author_name << ',' << book.book_code << ',' << book.first_count << ',' << book.available_count << endl;
        }
        file.close();
    } else {
        cout << "Unable to open file!" << endl;
    }
}

void load_members(vector<Member>& members) {
    ifstream file("members.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            Member member;
            getline(ss, member.first_name, ',');
            getline(ss, member.last_name, ',');
            getline(ss, member.code_melli, ',');
            getline(ss, member.mobile, ',');
            string capacity_str;
            getline(ss, capacity_str, ',');
            member.capacity = stoi(capacity_str);
            members.push_back(member);
        }
        file.close();
    } else {
        cout << "Unable to open file!" << endl;
    }
}

void load_books(vector<Book>& books) {
    ifstream file("books.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            Book book;
            getline(ss, book.book_name, ',');
            getline(ss, book.writer_name, ',');
            getline(ss, book.author_name, ',');
            getline(ss, book.book_code, ',');
            string first_count_str, available_count_str;
            getline(ss, first_count_str, ',');
            book.first_count = stoi(first_count_str);
            getline(ss, available_count_str, ',');
            book.available_count = stoi(available_count_str);
            books.push_back(book);
        }
        file.close();
    } else {
        cout << "Unable to open file!" << endl;
    }
}

int main() {
    vector<Member> members;
    vector<Book> books;
    load_members(members);
    load_books(books);
    show_menu();

    int task;
    do {
        cout << "LOTFAN YEK GOZINE RO ENTEKHAB KONID: ";
        cin >> task;
        cout << endl;

        switch (task) {
        case 1:
            add_member(members);
            save_members(members);
            show_menu();
            break;
        case 2:
            add_book(books);
            save_books(books);
            show_menu();
            break;
        case 3:
            borrow_book_menu(members, books);
            save_members(members);
            save_books(books);
            show_menu();
            break;
        case 4:
            return_book_menu(members, books);
            save_members(members);
            save_books(books);
            show_menu();
            break;
        }
    } while (task != 0);

    return 0;
}
