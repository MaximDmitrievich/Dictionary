#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include "item.h"
#include "redblacktree.h"

using namespace std;



int main()
{
    char *keyword = (char *) calloc(sizeof(char), 257);
    if (keyword == nullptr) {
        cout << "ERROR: Couldn't create variable keyword" << endl;
    }
    char *type = (char *) calloc(sizeof(char), 5);
    if (type == nullptr) {
        cout << "ERROR: Couldn't create variable type" << endl;
    }
    char *name = (char *) calloc(sizeof(char), 30);
    if (name == nullptr) {
        cout << "ERROR: Couldn't create variable name" << endl;
    }
    unsigned long long number = 0;
    TRBTree *dict = new TRBTree();
    if (dict == nullptr) {
        cout << "ERROR: Couldn't create dictionary" << endl;
    }
    char action;
    while (cin >> action) {
        if (action == '+') {
            cin >> keyword;
            ToLower(keyword);
            cin >> number;
            dict->Insert(number, keyword);
            memset(keyword, 0, sizeof(char));
        } else if (action == '-') {
            cin >> keyword;
            ToLower(keyword);
            dict->Delete(keyword);
            memset(keyword, 0, sizeof(char));
        } else if (action == '!') {
            cin >> type;
            if (strcmp(type, "Save")) {
                cin >> name;
                dict->Save(name);
                memset(name, 0, sizeof(char));
            } else if (strcmp(type, "Load")) {
                cin >> name;
                delete dict;
                dict = new TRBTree();
                dict->Load(name);
                memset(name, 0, sizeof(char));
            }
        } else {
            ungetc(action, stdin);
            cin >> keyword;
            ToLower(keyword);
            dict->Output(keyword);
        }
    }
    free(type);
    free(name);
    delete dict;
    return 0;
}
