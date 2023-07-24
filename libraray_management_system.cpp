#pragma once
#include <iostream>
#include <iomanip>
using namespace std;
class Book {
    string title;
    string author;
    string isbn;

    bool is_reserved;
    bool is_borrowed;
    string due_date;
public:
    Book() {
        title = "";
        author = "";
        isbn = "";
        is_reserved = false;
        is_borrowed = false;
        due_date = "";
    }
    bool get_is_reserved() { return is_borrowed; }
    void set_title(string t) { title = t; }
    void set_author(string a) { author = a; }
    void set_isbn(string i) { isbn = i; }

    string get_title() { return title; }
    string get_author() { return author; }
    string get_isbn() { return isbn; }

    void show_due_date() {
        cout << "Book is due on " + due_date << endl;
    }

    string get_due_date() { return due_date; }
    void set_due_date(string dat) {
        due_date = dat;
    }

    void show_res_status() {
        if (is_reserved)
            cout << "The Book is reserved" << endl;
        else cout << "The Book is not reserved" << endl;
    }

    bool book_request() {
        if (is_borrowed) {

            cout << "Can't Borrow:The Book is already Borrowd" << endl;
            cout << "Book Reserved"<<endl;
            is_reserved = true;
            
            return false;
        }
        else {
            cout << "Successful!!!!" << endl;
            is_borrowed = true;
            return true;
        }
    }

    

    void renew_info() {
        due_date = "";
        is_borrowed = false;
    }
};

class Library_Database {
private:
    int index;
    Book* books;
public:
    Library_Database() {
        index = 0;
        books = new Book[200];
    }

    bool add() {
        string title,author,isbn;

        cout << "Enter Book Title[ _ instead of spaces]:";
        cin >> title;
        cout << "Enter Book Author[ _ instead of spaces]:";
        cin >> author;

        cout << "Enter ISBN[ No Spaces ]:";
        cin >> isbn;
        bool exists = false;;
        for (int i = 0; i < index; i++)
        {
            if (books[i].get_isbn() == isbn)
            {
                cout << "Book with this ISBN exists" << endl;
                exists = true;
            }
        }
        if (!exists)
        {
            books[index].set_title(title);
            books[index].set_author(author);
            books[index++].set_isbn(isbn);
            cout << "Book Added Successfully" << endl;
        }

        return !exists;
    }

    void display() {
        cout << "Title          Author         ISBN           Status         Due Date"<<endl;
        for (int i = 0; i < index; i++)
        {
            cout << std::left << setw(15) << books[i].get_title() << setw(15) << books[i].get_author() << setw(15) << books[i].get_isbn() << setw(15) << (books[i].get_is_reserved() ? "Borrowed" : "Available") << setw(15) << books[i].get_due_date() << endl;
        }
    }

    bool update() { return 0; }

    bool delet() { return 0; }

    bool search(){
        string isbn;
        cout << "Enter Title or ISBN:";
        cin >> isbn;
        bool exists = false;;
        for (int i = 0; i < index; i++)
        {
            if (books[i].get_isbn() == isbn || books[i].get_title()==isbn)
            {
                cout << "The Book exists in the Database with status "<<(books[i].get_is_reserved()?"Borrowed":"Available") << endl;
                exists = true;
            }
        }
        if (!exists)
            cout << "The book doesnt exist in database" << endl;

        return exists;
    }


    Book* borrow_book()
    {
        string isbn;
        cout << "Enter Title or ISBN:";
        cin >> isbn;
        Book* ptr=nullptr;
        bool exists = false;;
        for (int i = 0; i < index; i++)
        {
            if (books[i].get_isbn() == isbn || books[i].get_title() == isbn)
            {
                if (books[i].book_request())
                    ptr = &books[i];
                
                exists = true;
            }
        }
        if (!exists)
            cout << "The book doesnt exist in database" << endl;

        return ptr;

    }
} l_db;

class Librarean {
private:
    string name;
    int id;
    string password;
public:
    Librarean() { 
        name = "";
        id = 0;
        password = "";
    }
    void set_name(string nm) { name = nm; }
    void set_id(int i) { id = i; }
    void set_password(string pwd) { password = pwd; }

    string get_name() { return name; }
    int get_id() { return id; }
    string get_password() { return password; }

    bool verify_librarean(int i, string pwd) {
        return i == id && pwd == password;
    }

    void librarean_portal() {
        while (1)
        {
            int choice;
            cout << "--------------------------LIBRAREAN PORTAL-------------------------" << endl;
            cout << "1. Add a Book" << endl;
            cout << "2. Search a book" << endl;
            cout << "3. Display all Books" << endl;
            cout << "4. Logout" << endl;
            cin >> choice;
            if (choice == 1) {
                l_db.add();
            }
            else if (choice == 2) {
                l_db.search();
            }
            else if (choice == 3)
            {
                l_db.display();
            }
            else return;
        }

        
    }
};

class Account {
private:
    Book** books_borrowed;
    int no_borrowed_books;
    int no_lost_books;
    int no_reserved_books;
    float fine_amount;
    
public:
    Account() { books_borrowed = new Book*[100]; 
    no_borrowed_books = 0;
    no_lost_books = 0;
    no_reserved_books = 0;
    fine_amount = 0;
    }
    void set_n_borrowed(int n) { no_borrowed_books = n; }
    void set_n_lost(int n) { no_lost_books = n; }
    void set_n_reserved(int n) { no_reserved_books = n; }
    void borrow(Book* book) {
        if(book!=nullptr)
        books_borrowed[no_borrowed_books++] = book;
    }


    void display() {
        cout << "Title          Author         ISBN           Status         Due Date" << endl;
        for (int i = 0; i < no_borrowed_books; i++)
        {
            cout << std::left << setw(15) << books_borrowed[i]->get_title() << setw(15) << books_borrowed[i]->get_author() << setw(15) << books_borrowed[i]->get_isbn() << setw(15) << (books_borrowed[i]->get_is_reserved() ? "Borrowed" : "Available") << setw(15) << books_borrowed[i]->get_due_date() << endl;
        }
    }

    void calculate_fine() {
        cout << "Fine Amount is :" << fine_amount << endl;
    }

    int get_n_borrowed() {
        return no_borrowed_books;
    }
    int get_n_lost() {
        return no_lost_books;
    }
    int get_n_reserved() {
        return no_reserved_books;
    }
    bool return_book(string isbn) {
        for (int i = 0; i < no_borrowed_books; i++)
        {
            if(isbn==books_borrowed[i]->get_isbn())
            {
                books_borrowed[i]->renew_info();
                for (int ind = i; ind < no_borrowed_books; ind++)
                {
                    books_borrowed[ind] = books_borrowed[ind + 1];
                }
                no_borrowed_books --;
                return true;
            }
        }
        cout << "Invalid ISBN" << endl;
        return false;
    }
    bool report_loss() 
    {
        display();
        cout << "Enter ISBN of the book for which do you want to report lost:";
       
        string isbn;
        cin >> isbn;
        for (int i = 0; i < no_borrowed_books; i++)
        {
            if (isbn == books_borrowed[i]->get_isbn())
            {
                no_lost_books++;
                for (int ind = i; ind < no_borrowed_books; ind++)
                {
                    books_borrowed[ind] = books_borrowed[ind + 1];
                }
                no_borrowed_books--;
                fine_amount += 2000;
                return true;
            }
        }
        cout << "Invalid ISBN" << endl;
        return false;
    }
};
class User {
    Account acc;
    string name;
    int id;
public:
    User() {
        name = "";
        id = 0;
        
    }
    bool verify(string n, int i)
    {
        return n == name && i == id;
    }

    int get_id() { return id; }
    string get_name(){ return name; }

    void set_id(int i) { id = i; }
    void set_name(string n) { name = n; }
    
    void user_panel() {
        while(1){
        cout << "----------------------------USER  PORTAL---------------------------" << endl;
        cout << "1. Check Reserved Books" << endl;
        cout << "2. Check Lost Books" << endl;
        cout << "3. Check Borrowed Books" << endl;
        cout << "4. Check all Books" << endl;
        cout << "5. Search a book" << endl;
        cout << "6. Borrow a book" << endl;
        cout << "7. Return a book" << endl;
        cout << "8. Report Lost Book" << endl;
        cout << "9. Calculate Fine" << endl;
        cout << "10. Logout" << endl;
        cout << "Your choice:";
        int choice;
        cin >> choice;
        if (choice == 1) cout << "Reserved Books are : " << acc.get_n_reserved() << endl;
        else if (choice == 2) cout << "Lost Books are : " << acc.get_n_lost() << endl;
        else if (choice == 3) {
            acc.display();
            cout << "Borrowed Books are : " << acc.get_n_borrowed() << endl;
        }
        else if (choice == 4) l_db.display();
        else if (choice == 5) l_db.search();
        else if (choice == 6)
        {
            acc.borrow(l_db.borrow_book());
        }
        else if (choice == 7)
        {
            acc.display();
            cout << "Enter ISBN of book you want to return:";
            string isbn;
            cin >> isbn;
            acc.return_book(isbn);

        }
        else if (choice == 8) acc.report_loss();
        else if (choice == 9) acc.calculate_fine();
        else if (choice == 10) return;
    }

        cout << "Enter your choice:";
    }
};

class Staff :public User {
    string dept;
    string designation;
public:
    Staff() {
        dept = "";
        designation = "";
    }
    Staff(string n, int i, string de, string des) {
        set_name(n);
        set_id(i);
        dept = de;
        designation = des;
    }
    string get_dept() { return dept; }
    string get_designation() { return designation; }

    void set_dept(string d) { dept = d; }
    void set_designation(string d) { designation = d; }
};



class Student :public User {
    string batch;
    string designation;
public:
    Student(string n, int i, string de, string des) {
        set_name(n);
        set_id(i);
        batch = de;
        designation = des;
    }
    Student() {
        batch = "";
        designation = "";
    }
    string get_batch() { return batch; }
    string get_designation() { return designation; }

    void set_batch(string d) { batch = d; }
    void set_designation(string d) { designation = d; }
};

class Library_Management_System {
private:
    int usertype;
    string username;
    string password;
    bool logged_in;
    Librarean* librareans;
    int lib_index;

    User** users;
    int user_index;


public:

    int get_user_type() {
        return usertype;

    }
    string get_user_name() {
        return username;
    }
    string get_password() {
        return password;
    }

    void set_user_type(int ust) {
        usertype = ust;
    }
    void set_user_name(string usn) {
        username = usn;
    }
    void set_password(string usp) {
        password = usp;
    }

    Library_Management_System() {
        usertype = 1;
        username = "";
        password = "";
        logged_in = false;
        librareans = new Librarean[20];
        lib_index = 0;
        librareans[lib_index].set_name("JohnSmith");
        librareans[lib_index].set_id(1);
        librareans[lib_index++].set_password("123");

        users = new User * [100];
        user_index = 0;
    }

    bool login() {
        string usrnm, pswd;
        cout << "Enter Username:";
        cin >> usrnm;
        cout << "Enter Password:";
        cin >> pswd;
        if (usrnm == username && pswd == password)
        {
            logged_in = true;
        }
        return usrnm == username && pswd == password;
    }
   

    bool logout() {
        logged_in = false;
        return true;
    }
    void add_librarean() {
        string nm, pwd;
        int id;
        cout << "Enter Name[without spaces]:";
        cin >> nm;

        cout << "Enter ID[Number]:";
        cin >> id;

        cout << "Enter Password[without spaces]:";
        cin >> pwd;
        bool exists = false;
        for (int i = 0; i < lib_index; i++) {
            if (librareans[i].get_id() == id)
            {
                cout << "Librarean with such Id already exists\n";
                exists = true;
            }
        }

        if (!exists) {
            librareans[lib_index].set_name(nm);
            librareans[lib_index].set_id(id);
            librareans[lib_index++].set_password(pwd);
        }


    }
    void verify_librarean(){
        string  pwd;
        int id;

        cout << "Enter ID[Number]:";
        cin >> id;

        cout << "Enter Password[without spaces]:";
        cin >> pwd;
        bool exists = false;
        for (int i = 0; i < lib_index; i++) {
            if (librareans[i].verify_librarean(id, pwd))
            {
                exists = true;
                librareans[i].librarean_portal();
            }
        }

        if (!exists) {
            cout << "Librarean with such credentials doesn't exists" << endl;
        }


    }
    void admin_portal() {
        while (1)
        {
            cout << "----------------------------ADMIN PORTAL---------------------------" << endl;
            cout << "1. Add a Librarean" << endl;
            cout << "2. Logout" << endl;
            cout << "Enter your choice:";
            int choice;
            cin >> choice;
            if (choice == 1)
                add_librarean();
            else if (choice == 2)
                return;
            else cout << "Invalid Choice" << endl;
        }

    }

    bool register_user() {
        string name, d, desig;
        string type;
        int id;
        cout << "Enter User Type [staff or student]:";
        cin >> type;
        if (type != "staff" && type != "student") {
            cout << "Invalid Type" << endl;
            return false;
        }
        else if (type == "staff")
        {
            cout << "Enter Name:";
            cin >> name;
            cout << "Enter id:";
            cin >> id;
            cout << "Enter Department:";
            cin >> d;
            cout << "Enter Designationn:";
            cin >> desig;

            for (int i = 0; i < user_index; i++)
            {
                if (id == users[i]->get_id())
                {
                    cout << "User Already Exists" << endl;
                }
            }

            users[user_index++] = new Staff(name, id, d, desig);


        }
        else {

            cout << "Enter Name:";
            cin >> name;
            cout << "Enter id:";
            cin >> id;
            cout << "Enter Batch:";
            cin >> d;
            cout << "Enter Designationn:";
            cin >> desig;

            for (int i = 0; i < user_index; i++)
            {
                if (id == users[i]->get_id())
                {
                    cout << "User Already Exists" << endl;
                }
            }

            users[user_index++] = new Staff(name, id, d, desig);
        }
        

    }

    bool login_user() {
        bool exists;
        string name;
        int id;
        cout << "Enter Name:";
        cin >> name;
        cout << "Enter ID:";
        cin >> id;
        bool login = false;
        for (int i = 0; i < user_index; i++)
        {
            if (users[i]->verify(name,id))
            {
                login = true;
                users[i]->user_panel();
            }
        }
        if (!login)
            cout << "User Not Exists" << endl;

        return login;
    }

};


int main()
{
    Library_Management_System lms;
    lms.set_user_name("alpha_123");
    lms.set_password("alpha_123");
    while (1)
    {
        int choice;
        cout << "---------------------Library Management System---------------------" << endl;
        cout << "1. Login as admin" << endl;
        cout << "2. Login as Librarian" << endl;
        cout << "3. Register User" << endl;
        cout << "4. Login as User" << endl;
        cout << "Enter your choice:";

        cin >> choice;

        if (choice == 1)
        {
            if (lms.login())
            {
                cout << "Login Successfull" << endl;
                lms.admin_portal();
            }
        }
        else if(choice==2){
            lms.verify_librarean();
        }
        else if(choice==3){
            lms.register_user();
        }
        else if(choice==4){
            lms.login_user();
        }
    }
    return 0;
}