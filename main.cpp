#include "rbtree.h"

using namespace std;

void ToLower(char *keyword)
{
    if (*keyword >= 'A' && *keyword <= 'Z') {
        *keyword = 'a' + (*keyword - 'A');
    }
}

int main(int argv, char **argc)
{
    char *keyword = (char *) calloc(sizeof(char), KEY_SIZE);
    if (keyword == nullptr) {
        cout << "ERROR: Couldn't create variable keyword" << endl;
    }
    char *type = (char *) calloc(sizeof(char), TYPE_SIZE);
    if (type == nullptr) {
        cout << "ERROR: Couldn't create variable type" << endl;
    }
    char *name = (char *) calloc(sizeof(char), NAME_SIZE);
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
            dict->Insert(keyword, number);
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
            dict->Search(keyword);
        }
    }
    free(keyword);
    free(type);
    free(name);
    delete dict;
    return 0;
}
