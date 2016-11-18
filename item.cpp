#include "item.h"
#include <cstdlib>
#include <iostream>
#include <cstring>

using namespace std;


TItem::TItem(TItem *parent)
{
    left = nullptr;
    right = nullptr;
    this->parent = parent;
    keyword = (char *) calloc(sizeof(char), 10);
    if (keyword == nullptr) {
        cout <<"ERROR: Couldn't create keyword" << endl;
    }
    strcpy(keyword, "___NIL___");
    number = 0;
    color = BLACK;
}

TItem::TItem(unsigned long long num, char *kwrd)
{
    left = new TItem(this);
    right = new TItem(this);
    parent = nullptr;
    keyword = (char *) calloc(sizeof(char), 257);
    if (keyword == nullptr) {
        cout << "ERROR: Couldn't create keyword" << endl;
    }
    strcpy(keyword, kwrd);
    number = num;
    color = RED;
}

TItem *TItem::Left()
{
    if (this->left != nullptr) {
        return this->left;
    } else return nullptr;
}
TItem *TItem::Right()
{
    if (this->right != nullptr) {
        return this->right;
    } else return nullptr;
}
TItem *TItem::Parent()
{
    if (this->parent != nullptr) {
        return this->parent;
    } else return nullptr;
}
TItem *TItem::Grandpa()
{
    if (this->parent != nullptr) {
        if (this->parent->parent != nullptr) {
            return this->parent->parent;
        } else return nullptr;
    } else return nullptr;
}
void TItem::SetLeft(TItem *it)
{
    if (this->left != nullptr && (strcmp(this->left->keyword, "___NIL___") == 0)) {
        delete this->left;
    }
    this->left = it;
}
void TItem::SetRight(TItem *it)
{
    if (this->right != nullptr && (strcmp(this->right->keyword, "___NIL___") == 0)) {
        delete this->right;
    }
    this->right = it;
}
void TItem::SetParent(TItem *it)
{
    this->parent = it;
}
void TItem::SetColor(TColor color)
{
    this->color = color;
}
unsigned long long TItem::Number()
{
    return this->number;
}
TItem *TItem::Min()
{
    if (strcmp(this->left->keyword, "___NIL___") == 0) {
        return this->left->Min();
    } else return this;
}
TItem *TItem::Successor()
{
    if (strcmp(this->right->keyword, "___NIL___") == 0) {
        return this->right->Min();
    }
    TItem *temp = this;
    TItem *temp2 = this->parent;
    while (temp2 != nullptr && (strcmp(temp2->keyword, "___NIL___") == 0) && temp == temp2->right) {
        temp = temp2;
        temp2 = temp2->parent;
    }
    return temp2;
}
void TItem::CopyData(TItem *right)
{
    memset(this->keyword, 0, sizeof(char));
    strcpy(this->keyword, right->keyword);
    this->number = right->number;
}
char *TItem::Keyword()
{
    return this->keyword;
}
TColor TItem::Color()
{
    return this->color;
}
TItem *TItem::Searchrec(char *keyword)
{
    if (strcmp(keyword, this->Keyword()) < 0) {
        if (this->Left()) {
            return this->left->Searchrec(keyword);
        } else return nullptr;
    } else if (strcmp(keyword, this->Keyword()) > 0) {
        if (this->Right()) {
            return this->right->Searchrec(keyword);
        } else return nullptr;
    } else return this;
}
TItem::~TItem()
{
    free(this->keyword);
    left = nullptr;
    right = nullptr;
    if (parent->left == this) {
        parent->left = new TItem(parent);
    }
    if (parent->right == this) {
        parent->right = new TItem(parent);
    }
    parent = nullptr;
    keyword = nullptr;
}
void TItem::Deleterec()
{
    if (this != nullptr) {
        if (this->left != nullptr) {
            this->left->Deleterec();
            this->left = nullptr;
        } else if (this->left != nullptr && (strcmp(this->left->keyword, "___NIL___") == 0)) {
            delete this->left;
            this->left = nullptr;
        }
        if (this->right != nullptr) {
            this->right->Deleterec();
            this->right = nullptr;
        } else if (this->right != nullptr && (strcmp(this->right->keyword, "___NIL___") == 0)) {
            delete this->right;
            this->right = nullptr;
        }
        delete this;
    }
}
