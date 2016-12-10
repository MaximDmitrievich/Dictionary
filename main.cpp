#include "rbtree.h"
#include <map>

using namespace std;

void ToLower(char *keyword)
{
    while (*keyword) {
        if (*keyword >= 'A' && *keyword <= 'Z') {
            *keyword = 'a' + (*keyword - 'A');
        }
        keyword++;
    }
}

int main(int argv, char **argc)
{
    char *keyword = nullptr;
    char type[TYPE_SIZE] = { '\0' };
    char name[NAME_SIZE] = { '\0' };
    unsigned long long number = 0;
    TRBTree *dict = new TRBTree();
    if (dict == nullptr) {
        cout << "ERROR: Couldn't create dictionary\n";
        exit(EXIT_SUCCESS);
    }
    char action;
    while (cin >> action) {
        if (action == '+') {
            keyword = nullptr;
            keyword = (char *) calloc(sizeof(char), KEY_SIZE);
            if (keyword == nullptr) {
                cout << "ERROR: Couldn't create variable keyword\n";
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
            ToLower(buf);
            dict->Search(buf);
        }
    }
    delete dict;
    return 0;
}
