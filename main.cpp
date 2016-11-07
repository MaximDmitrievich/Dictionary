#include <iostream>
#include <cstdlib>
#include <cstring>
#include "item.h"
#include "redblacktree.h"

using namespace std;

int main()
{
    char *keyword = (char *) calloc(sizeof(char), 257);
    char *type = (char *) calloc(sizeof(char), 4);
    char *name = (char *) calloc(sizeof(char), 30);
    unsigned long long number = 0;
    TRBTree *dict = new TRBTree();
    char action;
    while (cin >> action) {
        if (action == '+') {
            cin >> keyword;
            cin >> number;
            dict->Insert(number, keyword);
            memset(keyword, 0, sizeof(char));
        } else if (action == '-') {
            cin >> keyword;
            dict->Delete(keyword);
            memset(keyword, 0, sizeof(char));
        } else if (action == '!') {
            cin >> type;
            if (strcmp(type, "Save")) {
                cin >> name;
                dict->Save(name);
                memset(name, 0, sizeof(char));
            } else if (strcmp(type, "Load")) {

                memset(name, 0, sizeof(char));
            }
        } else {
            ungetc(action, stdin);
            cin >> keyword;
            dict->Output(keyword);
        }
    }
    free(type);
    free(name);
    delete dict;
    return 0;
}
