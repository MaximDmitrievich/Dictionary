#include "rbtree.h"
#include <map>

using namespace std;

int main(int argv, char **argc)
{
    char *keyword = nullptr;
    char type[TYPE_SIZE] = { '\0' };
    char name[NAME_SIZE] = { '\0' };
    char buf[KEY_SIZE] = { '\0' };
    unsigned long long number = 0;
    TRBTree *dict = new TRBTree();
    if (dict == nullptr) {
        cout << "ERROR: Couldn't create dictionary\n";
        exit(EXIT_SUCCESS);
    }
    char action;
    while (cin >> action) {
        if (action == '+') {
            keyword = (char *) calloc(sizeof(char), KEY_SIZE);
            if (keyword == nullptr) {
                cout << "ERROR: Couldn't create variable keyword\n";
                continue;
            }
            cin >> keyword;
            keyword[KEY_SIZE - 1] = '\0';
            cin >> number;
            dict->Insert(keyword, number);
            keyword = nullptr;
        } else if (action == '-') {
            memset(buf, '\0', sizeof(char));
            cin >> buf;
            buf[KEY_SIZE - 1] = '\0';
            dict->Delete(buf);
        } else if (action == '!') {
            cin >> type;
            if (strcmp(type, "Save") == 0) {
                cin >> name;
                dict->Save(name);
            } else if (strcmp(type, "Load") == 0) {
                cin >> name;
                dict->Load(name);
            }
        } else {
            ungetc(action, stdin);
            memset(buf, '\0', sizeof(char));
            cin >> buf;
            buf[KEY_SIZE - 1] = '\0';
            dict->Search(buf);
        }
    }
    delete dict;
    return 0;
}
