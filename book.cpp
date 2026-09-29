#include <sstream>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const string name, double price, int qty, const string isbn, const string author) :Product("book", name, price, qty), isbn_(isbn), author_(author) //what happen to isbn and author?!
{

}

set<string> Book::keywords() const
{
    set<string> keys = parseStringToWords(name_);
    set<string> authorKeys = parseStringToWords(author_);

    keys = setUnion(keys, authorKeys);

    keys.insert(isbn_); //isbn is not devided just use it

    return keys;
}

string Book::displayString() const
{
    stringstream ss;

    ss << name_ << "\n";
    ss << "Author: " << author_ << " ISBN: " << isbn_ << "\n";
    ss << price_ << " " << qty_ << " left.";

    return ss.str();
}

void Book::dump(ostream& os) const
{
    Product::dump(os);
    os << isbn_ << endl;
    os << author_ << endl;
}