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
    strcpy(keyword, "___NIL___");
    number = 0;
    color = BLACK;
}

TItem::TItem(unsigned long long num, char *kwrd)
{
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    keyword = (char *) calloc(sizeof(char), 257);
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
TItem *TItem::Uncle()
{
    if (this->Grandpa()) {
        TItem *tmp = this->Grandpa();
        if (this->Parent() == tmp->Left()) {
            return tmp->right;
        } else return tmp->left;
    } else return nullptr;
}
void TItem::SetLeft(TItem *it)
{
    this->left = it;
}
void TItem::SetRight(TItem *it)
{
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
    parent = nullptr;
}
void TItem::Deleterec()
{
    if (this != nullptr) {
        if (this->left != nullptr) {
            this->left->Deleterec();
        }
        if (this->right != nullptr) {
            this->right->Deleterec();
        }
        delete this;
    }
}
