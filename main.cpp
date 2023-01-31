#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;

map<string,int> ted; // the number of books a user has rented


class Student {

    public:
        string username;
        string password;
        string first_name;
        string last_name;
        string birth_date;

    public:
        // constructor
        Student(string u, string p, string fn, string ln, string bd) :
            username(u), password(p), first_name(fn), last_name(ln), birth_date(bd) {}
        // member functions
        bool check_password(string u, string p);
        bool check_registered(string u);
        void add_student();
        void remove_student(string u);
};

Student stu("","","","","");

pair<string, string> get_first_two_words(string input) {
    string first, second;
    first = second = "";
    int i = 0;
    for(; i < input.size(); i++) {
        if(input[i] != ' ') {
            first += input[i];
        } else {
            i++;
            break;
        }
    }
    for(; i < input.size(); i++) {
        if(input[i] != ' ') {
            second += input[i];
        } else {
            break;
        }
    }
    return make_pair(first, second);
}

bool Student::check_password(string u, string p) {
    ifstream student_file("students.txt");
    string line;
    while (getline(student_file, line)) {
        pair<string,string> x = get_first_two_words(line);
        string file_username, file_password;
        file_username = x.first;
        file_password = x.second;
        if (file_username == u && file_password == p) {
            student_file.close();
            return true;
        }
    }
    student_file.close();
    return false;
}

bool Student::check_registered(string u) {
    ifstream student_file("students.txt");
    string line;
    while (getline(student_file, line)) {
        pair<string,string> x = get_first_two_words(line);
        string file_username, file_password;
        file_password = x.second;
        file_username = x.first;
        if (file_username == u) {
            student_file.close();
            return true;
        }
    }
    student_file.close();
    return false;
}

void Student::add_student() {
    string u, p, fn, ln, bd;
    cout << "write user and pass and first name and last name and birthdate in a line" << endl;
    cin >> u >> p >> fn >> ln >> bd;

    if (check_registered(u)) {
        cout << "Error: username already taken." << endl;
        return;
    }
    if(u=="null")
    {
    	cout<<"Error: invalid user name"<<endl;
    	return;
	}

    ofstream student_file("students.txt", ios::app);
    student_file << u << " " << p << " " << fn << " " << ln << " " << bd << endl;
    student_file.close();
    cout << "Student added successfully." << endl;
}


void Student::remove_student(string u) {
    ifstream student_file("students.txt");
    ofstream temp_file("temp.txt");
    string line;
    bool found = false;
    while (getline(student_file, line)) {
        istringstream iss(line);
        string file_username, file_password, file_first_name, file_last_name, file_birth_date;
        if (!(iss >> file_username >> file_password >> file_first_name >> file_last_name >> file_birth_date)) { continue; }
        if (file_username != u) {
            temp_file << file_username << " " << file_password << " " << file_first_name << " " << file_last_name << " " << file_birth_date << endl;
        }
        else {
            found = true;
        }
    }
    student_file.close();
    temp_file.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    if (found) {
        cout << "Student removed successfully." << endl;
    }
    else {
        cout << "Error: student not found." << endl;
    }
}



// Book Class starts from here
class Book {
public:
    string title;
    string shelf_number;
    string authors;
    string edition;
    string publisher;
    string published_year;
    string ISBN;
    string length;
    string subjects;
    bool is_rented;
    string whose_rented;

    Book() {}

    Book(string t, string sn, string a, string e, string p, string py, string i, string l, string s, bool ir, string whr) :
    title(t), shelf_number(sn), authors(a), edition(e), publisher(p), published_year(py), ISBN(i), length(l), subjects(s), is_rented(ir), whose_rented(whr) {}

    void search_books(string criteria, string keyword) {
        ifstream book_file("books.txt");
        string line;
        vector<Book> found_books;
        while (getline(book_file, line)) {
            istringstream iss(line);
            string file_title, file_shelf_number, file_authors, file_edition, file_publisher, file_published_year, file_ISBN, file_length, file_subjects, file_is_rented, who_rent;
            if (!(iss >> file_title >> file_shelf_number >> file_authors >> file_edition >> file_publisher >> file_published_year >> file_ISBN >> file_length >> file_subjects >> file_is_rented >> who_rent)) { continue; }
            if (criteria == "publisher" && file_publisher == keyword) {
                found_books.push_back(Book(file_title, file_shelf_number, file_authors, file_edition, file_publisher, file_published_year, file_ISBN, file_length, file_subjects, (file_is_rented == "1"), who_rent));
            }
            else if (criteria == "published_year" && file_published_year == keyword) {
                found_books.push_back(Book(file_title, file_shelf_number, file_authors, file_edition, file_publisher, file_published_year, file_ISBN, file_length, file_subjects, (file_is_rented == "1"), who_rent));
            }
            else if (criteria == "title" && file_title == keyword) {
                found_books.push_back(Book(file_title, file_shelf_number, file_authors, file_edition, file_publisher, file_published_year, file_ISBN, file_length, file_subjects, (file_is_rented == "1"), who_rent));
            }
            else if (criteria == "authors" && file_authors == keyword) {
                found_books.push_back(Book(file_title, file_shelf_number, file_authors, file_edition, file_publisher, file_published_year, file_ISBN, file_length, file_subjects, (file_is_rented == "1"), who_rent));
            }
        }
        if (found_books.size() == 0) {
            cout << "No books found for the given criteria" << endl;
        }
        else {
            cout << "Found books:" << endl;
            for (auto b : found_books) {
                cout << "Title: " << b.title << endl;
                cout << "Shelf number: " << b.shelf_number << endl;
                cout << "Authors: " << b.authors << endl;
                cout << "Edition: " << b.edition << endl;
                cout << "Publisher: " << b.publisher << endl;
                cout << "Published Year: " << b.published_year << endl;
                cout << "ISBN: " << b.ISBN << endl;
                cout << "Rented: " << b.is_rented << endl;
            }
        }
        book_file.close();
    }


    void rent_book(string username, string password,string ISBN) {
        if(stu.check_password(username,password) == false){
            cout << "Error: username or password is wrong" << endl;
            return;
        }
        if(ted[username] >= 2){
            cout << "Error: user has rented too many books" << endl;
            return;
        }
        vector<Book> books;
        ifstream book_file("books.txt");
        string line;
        while (getline(book_file, line)) {
            istringstream iss(line);
            string file_title, file_shelf_number, file_authors, file_edition, file_publisher, file_published_year, file_ISBN, file_length, file_subjects, file_is_rented, who_rent;
            if (!(iss >> file_title >> file_shelf_number >> file_authors >> file_edition >> file_publisher >> file_published_year >> file_ISBN >> file_length >> file_subjects >> file_is_rented >> who_rent)) { continue; }
            if (file_ISBN == ISBN) {
                if (file_is_rented == "1") {
                    cout << "Error: Book is already rented" << endl;
                    book_file.close();
                    return;
                }
                else {
                    books.push_back(Book(file_title, file_shelf_number, file_authors, file_edition, file_publisher, file_published_year, file_ISBN, file_length, file_subjects, true, username));
                    cout << "Book rented successfully" << endl;
                    ted[username]++;
                }
            }
            else {
                books.push_back(Book(file_title, file_shelf_number, file_authors, file_edition, file_publisher, file_published_year, file_ISBN, file_length, file_subjects, (file_is_rented == "1"), who_rent));
            }
        }
        book_file.close();
        ofstream updated_book_file("temp.txt");
        for (auto b : books) {
            updated_book_file << b.title << ' ' << b.shelf_number << ' ' << b.authors << ' ' << b.edition << ' ' << b.publisher << ' ' << b.published_year << ' ' << b.ISBN << ' ' << b.length << ' ' << b.subjects << ' ' << b.is_rented << ' ' << b.whose_rented << endl;
        }
        updated_book_file.close();
        remove("books.txt");
        rename("temp.txt", "books.txt");
    }

    void take_back_book(string username, string password,string ISBN) {
        if(stu.check_password(username,password) == false){
            cout << "Error: username or password is wrong" << endl;
            return;
        }
        vector<Book> books;
        ifstream book_file("books.txt");
        string line;
        while (getline(book_file, line)) {
            istringstream iss(line);
            string file_title, file_shelf_number, file_authors, file_edition, file_publisher, file_published_year, file_ISBN, file_length, file_subjects, file_is_rented, who_rent;
            if (!(iss >> file_title >> file_shelf_number >> file_authors >> file_edition >> file_publisher >> file_published_year >> file_ISBN >> file_length >> file_subjects >> file_is_rented >> who_rent)) { continue; }
            if (file_ISBN == ISBN) {
                if (file_is_rented == "0") {
                    cout << "Error: Book is not rented" << endl;
                    return;
                }
                else {
                	if (who_rent == username){              	
	                    books.push_back(Book(file_title, file_shelf_number, file_authors, file_edition, file_publisher, file_published_year, file_ISBN, file_length, file_subjects, false, "null"));
	                    cout << "Book has taken back successfully" << endl;
	                    ted[username]--;
                	}
                	else {
                		cout << "Error: You cannot take this book back" << endl;
                		return;
					}
                }
            }
            else {
                books.push_back(Book(file_title, file_shelf_number, file_authors, file_edition, file_publisher, file_published_year, file_ISBN, file_length, file_subjects, (file_is_rented == "1"), who_rent));
            }
        }
        book_file.close();
        ofstream updated_book_file("temp.txt");
        for (auto b : books) {
            updated_book_file << b.title << ' ' << b.shelf_number << ' ' << b.authors << ' ' << b.edition << ' ' << b.publisher << ' ' << b.published_year << ' ' << b.ISBN << ' ' << b.length << ' ' << b.subjects << ' ' << b.is_rented << ' ' << b.whose_rented << endl;
        }
        updated_book_file.close();
        remove("books.txt");
        rename("temp.txt", "books.txt");
    }
} bookk;

int main(){
    system("cls");
    cout << "Az in Dastorat mitonin estefade konin:\n1.Add Student\n2.Remove Student\n3.Rent Book\n4.Give Back Book\n5.Search for Books\n6.Clear Screen and Start again" << endl;
    while(true){
        string now;
        cin >> now;
        if(now == "1"){
            stu.add_student();
        }else if(now == "2"){
            cout << "Enter The Student's username you want to remove:" << endl;
            string u;
            cin >> u;
            stu.remove_student(u);
        }else if(now == "3"){
            cout << "Enter The Student's Username And Password of yourself and the ISBN of the book you want to rent:" << endl;
            string x,y,z;
            cin >> x >> y >> z;
            bookk.rent_book(x,y,z);
        }else if(now == "4"){
            cout << "Enter Username And Password of yourself and the ISBN of the book you want to give back:" << endl;
            string x,y,z;
            cin >> x >> y >> z;
            bookk.take_back_book(x,y,z);
        }else if(now == "5"){
            cout << "Enter the Criteria(title,authors,publisher,published_year) and keyword you want to search:" << endl;
            string x,y;
            cin >> x >> y;
            bookk.search_books(x,y);
        }else if(now == "6"){
            system("cls");
            cout << "Az in Dastorat mitonin estefade konin:\n1.Add Student\n2.Remove Student\n3.Rent Book\n4.Give Back Book\n5.Search for Books\n6.Clear Screen and Start again" << endl;
        }
    }

    return 0;
}
