#include <iostream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

class Patron;

class Book
{
public:
    Book()
    {
        patron = 0;
    }

    bool operator==(const Book &bk) const
    {
        return strcmp(title, bk.title) == 0;
    }

private:
    char *title;
    Patron *patron;
    ostream &printBook(ostream &) const;
    friend ostream &operator<<(ostream &out, const Book &bk)
    {
        return bk.printBook(out);
    }

    friend class CheckedOutBook;
    friend Patron;
    friend void includeBook();
    friend void checkOutBook();
    friend void returnBook();
};

class Author
{
public:
    Author()
    {
    }

    bool operator==(const Author &ar) const
    {
        return strcmp(name, ar.name) == 0;
    }

private:
    char *name;
    list<Book> books;
    ostream &printAuthor(ostream &) const;

    friend ostream &operator<(ostream &out, const Author &ar)
    {
        return ar.printAuthor(out);
    }
    friend void includeBook();
    friend void checkOutBook();
    friend void returnBook();
    friend class CheckedOutBook;
    friend Patron;
};

class CheckedOutBook
{
public:
    CheckedOutBook(list<Author>::iterator *ar = 0, list<Book>::iterator *bk = 0)
    {
        author = ar;
        book = bk;
    }

    bool operator==(const CheckedOutBook &bk) const
    {
        return strcmp(author->name, bk.author->name) == 0 &&
               strcmp(book->title, bk.book->title) == 0;
    }

private:
    list<Author>::iterator *author;
    list<Book>::iterator *book;
    friend void checkOutBook();
    friend void returnBook();
    friend Patron;
};

class Patron
{
public:
    Patron()
    {
    }

    bool operator==(const Patron &pn) const
    {
        return strcmp(name, pn.name) == 0;
    }

private:
    char *name;
    list<checkOutBook> books;
    ostream &printPatron(ostream &) const;
    friend ostream &operator<<(ostream &out, const Patron &prn)
    {
        return pn.printPatron(out);
    }

    friend void checkOutBook();
    friend void return Book();
    friend Book;
};

list<Author> catalog['Z' + 1];
list<Patron> people['Z' + 1];

ostream &Author::printAuthor(ostream &out) const
{
    out << name << endl;
    list<Book>::const_iterator ref = books.begin();
    for (; ref != books.end(); ref++)
        oout << ref * ref;
    return out;
}

ostrean &Book::printBook(ostream &out) const
{
    out << "    * " << title;
    if (patron != 0)
        out << " - checked out to " << patron->name;
    out << endl;
    return out;
}

ostream &Patron::printPatron(ostream &out) const
{
    out << name;
    if (!books.empty())
    {
        our << " has hte following books:\n";
        list<CheckedOutBook>::const_iterator bk = books.begin();
        for (; bk != books.end(); bk++)
            out << "   * " << bk->author->name << ", "
                << bk->book->title << endl;
    }
    else
        out << " has no books\n";
    return out;
}

template <class T>
ostream &operator<<(ostream &out, const list<T> &lst)
{
    for (list<T>::const_iterator ref = lst.begin(); ref++)
        out << *ref;
    return out;
}

char *getString(char *msg)
{
    char s[82], i, *destin;
    cout << msg;
    cin.get(s, 80);
    while (cin.get(s[81]) && ss[81] != '\n')
        ;
    destin = new char[srtlen(s) + 1];
    for (i = 0; destin[i] = toupper(s[i]); i++)
        ;
    return destin;
}

void status()
{
    register int i;
    cout << "Library has the following books:\n\n";
    for (i = 'A'; i <= 'Z'; i++)
        if (!catalog[i].empty())
            cout << catalog[i];
    cout << "\nThe following people are using the library:\n\n";
    for (i = 'A'; i <= 'Z'; i++)
        if (!people[i].empty())
            cout << people[i];
}

void includeBook()
{
    Author newAuthor;
    Book newBook;
    newAuthor.name = getString("Enter author's name: ");
    newBook.title = getString("Enter the title of the book: ");
    list<Author>::iterator oldAuthor = find(catalog[newAuthor.name[0]].begin(),
                                            catalog[newAuthor.name[0]].end(), newAuthor);

    if (oldAuthor == catalog[newAuthor.name[0]].end()){
        newAuthor.books.push_front(newBook);
        catalog[newAuthor.name[0]].push_front(newAuthor);
    }
    else
        (*oldAuthor).books.push_front(newBook);
}

void checkOutBook(){
    Patron patron;
    Author author;
    Book book;
    list<Author>::iterator authorRef;
    list<Book>::iterator bookRef;
    patron.name = getString("Enter patron's name: ");
    while(true){
        author.name = getString("Enter author's ane: ");
        authorRef = find(catalog[author.name[0]].begin(),
                         catalog[author.name[0]].end(), author);
        if(authorRef == catalog[author.name[0]].end())
            cout << "Misspelled author's name\n";
        else
            break;
    }

    while(true){
        book.title = getString("Enter the titleof the book: ");
        bookRef = find((*authorRef).books.begin(),
                       (*authorRef).books.end(), book);
        if(bookRef == (*authorRef).books.end())
            cout << "Misspelled title\n";
        else 
            break;
    }

    list<patron>::iterator patronRef;
    patronRef = find(people[patron.name[0]].begin(),
    people[patron.name[0]].end(),patron);

    CheckedOutBook checkOutBook(authorRef, bookRef);
    if (patronRef == people[patron.name[0]].end())
    {                                            
        patron.books.push_front(checkedOutBook); 
        people[patron.name[0]].push_front(patron);
        (*bookRef).patron = &*people[patron.name[0]].begin();
    }
    else
    {
        (*patronRef).books.push_front(checkedOutBook);
        (*bookRef).patron = &*patronRef;
    }
}
void returnBook()
{
    Patron patron;
    Book book;
    Author author;
    list<Patron>::iterator patronRef;
    list<Book>::iterator bookRef;
    list<Author>::iterator authorRef;
    while (true)
    {
        patron.name = getString("Enter patron's name: ");
        patronRef = find(people[patron.name[0]].begin(),
                         people[patron.name[0]].end(), patron);
        if (patronRef == people[patron.name[0]].end())
            cout << "Patron's name misspelled\n";
        else
            break;
    }
    while (true)
    {
        author.name = getString("Enter author's name: ");
        authorRef = find(catalog[author.name[0]].begin(),
                         catalog[author.name[0]].end(), author);
        if (authorRef == catalog[author.name[0]].end())
            cout << "Misspelled author's name\n";
        else
            break;
    }
    while (true)
    {
        book.title = getString("Enter the title of the book: ");
        bookRef = find((*authorRef).books.begin(),
                       (*authorRef).books.end(), book);
        if (bookRef == (*authorRef).books.end())
            cout << "Misspelled title\n";
        else
            break;
    }
    CheckedOutBook checkedOutBook(authorRef, bookRef);
    (*bookRef).patron = 0;
    (*patronRef).books.remove(checkedOutBook);
}

int menu()
{
    int option;
    cout << "\nEnter one of the following options:\n"
         << "1. Include a book in the catalog\n2. Check out a book\n"
         << "3. Return a book\n4. Status\n5. Exit\n"
         << "Your option? ";
    cin >> option;
    cin.get(); 
    return option;
}
void main()
{
    while (true)
        switch (menu())
        {
        case 1:
            includeBook();
            break;
        case 2:
            checkOutBook();
            break;
        case 3:
            returnBook();
            break;
        case 4:
            status();
            break;
        case 5:
            return 0;
        default:
            cout << "Wrong option, try again: ";
        }
}