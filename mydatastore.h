#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include <string>
#include <iostream>
#include <set>
#include <map>

#include "datastore.h"
#include "product.h"
#include "user.h"

class MyDataStore : public DataStore
{
public:
    MyDataStore();
    ~MyDataStore();

    void addProduct(Product* p);
    /*
    products_ > store p
    p -> keywords() call
    loop/iterate keyword one by one
    using keywordmap to add p
    */
    void addUser(User* u);
    /*
    users_ > store user*
    username -> user* map add
    maybe.... empty one also
    */

    std::vector<Product*> search (std::vector<std::string>& terms, int type);

    void dump(std::ostream& ofile);

    bool addToCart(std::string username, Product* product); //whether username is valid or not?!
    bool viewCart(std::string username);
    bool buyCart(std::string username);

private:
    std::vector<Product*> products_;
    std::vector<User*> users_;

    std::map<std::string, std::set<Product*>> keywordMap_;
    std::map<std::string, User*> userMap_;
    std::map<std::string, std::vector<Product*>> carts_;
};

#endif