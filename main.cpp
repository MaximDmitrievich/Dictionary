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
    char *keyword = nullptr;
    char *type = (char *) calloc(sizeof(char), TYPE_SIZE);
    if (type == nullptr) {
        cout << "ERROR: Couldn't create variable type" << endl;
        exit(EXIT_SUCCESS);
    }
    char *name = (char *) calloc(sizeof(char), NAME_SIZE);
    if (name == nullptr) {
        cout << "ERROR: Couldn't create variable name" << endl;
        free(type);
        exit(EXIT_SUCCESS);
    }
    unsigned long long number = 0;
    TRBTree *dict = new TRBTree();
    if (dict == nullptr) {
        cout << "ERROR: Couldn't create dictionary" << endl;
        free(type);
        free(name);
        exit(EXIT_SUCCESS);
    }
    char action;
    while (cin >> action) {
        if (action == '+') {
            keyword = nullptr;
            keyword = (char *) calloc(sizeof(char), KEY_SIZE);
            if (keyword == nullptr) {
                cout << "ERROR: Couldn't create variable keyword" << endl;
                continue;
            }
            cin >> keyword;
            ToLower(keyword);
            cin >> number;
            dict->Insert(keyword, number);
        } else if (action == '-') {
            char buf[KEY_SIZE] = { '\0' };
            cin >> buf;
            ToLower(buf);
            dict->Delete(buf);
        } else if (action == '!') {
            cin >> type;
            if (strcmp(type, "Save") == 0) {
                cin >> name;
                dict->Save(name);
                memset(name, 0, sizeof(char));
            } else if (strcmp(type, "Load") == 0) {
                cin >> name;
                dict->Load(name);
                memset(name, 0, sizeof(char));
            }
        } else {
            ungetc(action, stdin);
            char buf[KEY_SIZE] = { '\0' };
            cin >> buf;
            buf[KEY_SIZE] = '\0';
            ToLower(buf);
            dict->Search(buf);
        }
    }
    free(type);
    free(name);
    delete dict;
    return 0;
}
