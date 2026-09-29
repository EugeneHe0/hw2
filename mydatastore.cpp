#include "mydatastore.h"
#include "util.h"

using namespace std;

MyDataStore::MyDataStore()
{

}

MyDataStore::~MyDataStore()
{
    for(vector<Product*>::iterator it = products_.begin();it != products_.end();++it)
    {
        delete *it;
    }

    for(vector<User*>::iterator it = users_.begin();it != users_.end();++it)
    {
        delete *it;
    }
}

void MyDataStore::addProduct(Product* p)
{
    products_.push_back(p);

    set<string> keys = p->keywords();

    for(set<string>::iterator it = keys.begin();
        it != keys.end(); ++it)
    {
        keywordMap_[*it].insert(p);
    }
}


void MyDataStore::addUser(User* u)
{
    users_.push_back(u);

    string username = convToLower(u->getName());

    userMap_[username] = u;
    carts_[username] = vector<Product*>();
}

vector<Product*> MyDataStore::search(vector<string>& terms, int type)
{
    vector<Product*> result;

    if(terms.size() == 0) return result;

    set<Product*> matches;

    string firstTerm = convToLower(terms[0]);

    if(keywordMap_.find(firstTerm) != keywordMap_.end()) matches = keywordMap_[firstTerm];

    for(size_t i = 1;i < terms.size();++i)
    {
        string term = convToLower(terms[i]);

        set<Product*> current;

        if(keywordMap_.find(term) != keywordMap_.end())
        {
            current = keywordMap_[term];
        }

        if(type == 0)
        {
            matches = setIntersection(matches, current); //and
        }
        else //if type is 1
        {
            matches = setUnion(matches, current); //or
        }
    }

    for(set<Product*>::iterator it = matches.begin(); it != matches.end(); ++it)
    {
        result.push_back(*it);
    }

    return result;
}

bool MyDataStore::addToCart(string username, Product* p)
{
    username = convToLower(username);

    if(userMap_.find(username) == userMap_.end()) return false;

    carts_[username].push_back(p);

    return true;
}


bool MyDataStore::viewCart(string username)
{
    username = convToLower(username);

    if(userMap_.find(username) == userMap_.end()) return false;

    vector<Product*>& cart = carts_[username];

    for(size_t i = 0;i < cart.size();++i)
    {
        cout << "Item " << i + 1 << endl;
        cout << cart[i]->displayString() << endl;
        cout << endl;
    }

    return true;
}


bool MyDataStore::buyCart(string username)
{
    username = convToLower(username);

    if(userMap_.find(username) == userMap_.end()) return false;

    User* user = userMap_[username];

    vector<Product*>& cart = carts_[username];

    vector<Product*> remaining;

    for(size_t i = 0;i < cart.size();++i)
    {
        Product* p = cart[i];

        if(p->getQty() > 0 &&
           user->getBalance() >= p->getPrice())
        {
            p->subtractQty(1);
            user->deductAmount(p->getPrice());
        }
        else
        {
            remaining.push_back(p);
        }
    }

    cart = remaining;

    return true;
}


void MyDataStore::dump(ostream& ofile)
{
    ofile << "<products>" << endl;

    for(vector<Product*>::iterator it = products_.begin();it != products_.end();++it)
    {
        (*it)->dump(ofile);
    }

    ofile << "</products>" << endl;
    ofile << "<users>" << endl;

    for(vector<User*>::iterator it = users_.begin();it != users_.end();++it)
    {
        (*it)->dump(ofile);
    }

    ofile << "</users>" << endl;
}