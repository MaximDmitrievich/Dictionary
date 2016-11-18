#ifndef RBTREE_H
#define RBTREE_H
#include "item.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>

using namespace std;
void ToLower(char *keyword);
class TRBTree {
private:
    TItem *root;
    void RightRotation(TItem *node);
    void LeftRotation(TItem *node);
    void DeleteFix(TItem *it);
    void SaveRec(TItem *node, FILE *out);
    TItem *LoadRec(TItem *parent, FILE *in);
public:
    TRBTree();
    TItem *Search(char *keyword);
    void Output(char *keyword);
    void Insert(unsigned long long number, char *keyword);
    unsigned long long GetNumber(TItem *it);
    void Delete(char *keyword);
    void Save(char *name);
    void Load(char *name);
    virtual ~TRBTree();
};

#endif
