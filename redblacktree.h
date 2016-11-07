#ifndef RBTREE_H
#define RBTREE_H
#include "item.h"
#include <cstdio>
#include <cstdlib>

class TRBTree {
private:
    TItem *root;
    void RightRotation(TItem *node);
    void LeftRotation(TItem *node);
    void DeleteFix(TItem *it);
    void SaveRec(TItem *node, FILE *file);
    void LoadRec(TItem *node, FILE *file);
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
