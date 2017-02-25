#include "rbtree.h"

using namespace std;

int main(int argv, char **argc)
{
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
            cin >> buf;
            cin >> number;
            dict->Insert(buf, number);
        } else if (action == '-') {
            cin >> buf;
            dict->Delete(buf);
        } else if (action == '!') {
            cin >> type;
            if (type[0] == 'S') {
                cin >> name;
                dict->Save(name);
            } else if (type[0] == 'L') {
                cin >> name;
                dict->Load(name);
            }
        } else {
            ungetc(action, stdin);
            cin >> buf;
            buf[KEY_SIZE - 1] = '\0';
            dict->Search(buf);
        }
    }
    delete dict;
    return 0;
}
