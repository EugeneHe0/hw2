#include <sstream>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const string name, double price, int qty, const string genre, const string rating) :Product("movie", name, price, qty), genre_(genre), rating_(rating)
{

}

set<string> Movie::keywords() const
{
    set<string> keys = parseStringToWords(name_);
    keys.insert(convToLower(genre_));

    return keys;
}

string Movie::displayString() const
{
    stringstream ss;

    ss << name_ << "\n";
    ss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
    ss << price_ << " " << qty_ << " left.";

    return ss.str();
}

void Movie::dump(ostream& os) const
{
    Product::dump(os);
    os << genre_ << endl;
    os << rating_ << endl;
}