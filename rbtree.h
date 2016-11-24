#ifndef RBTREE_H
#define RBTREE_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <cstring>

using namespace std;


const int KEY_SIZE = 257;
const int NIL_SIZE = 8;
const int TYPE_SIZE = 5;
const int NAME_SIZE = 30;

enum TColor {RED, BLACK};

class TRBTree {
private:
    struct TNode {
        char *keyword;
        unsigned long long number;
        TColor color;
        TNode *left;
        TNode *right;
        TNode *parent;
    };
    TNode *root;

    bool IsNIL(TNode *node);
    TNode *CreateNIL(TNode *parent);
    TNode *CreateNode(TNode *parent, char *keyword, unsigned long long number);
    TNode *Minimum(TNode *node);
    TNode *Successor(TNode *node);

    TNode *Recoursesearch(char *keyword, TNode *node);
    void Recoursedestroy(TNode *node);

    void LeftRotation(TNode *node);
    void RightRotation(TNode *node);

    void InsertFix(TNode *node);

    void DeleteFix(TNode *node);

    void Ser(TNode *node, ofstream &file);
    TNode *Deser(ifstream &file);

public:
    TRBTree();
    void Insert(char *keyword, unsigned long long number);
    void Search(char *keyword);
    void Delete(char *keyword);
    void Save(const char *path);
    void Load(const char *path);
    ~TRBTree();
};

#endif
