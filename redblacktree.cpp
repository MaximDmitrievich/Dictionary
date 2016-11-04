#include "redblacktree.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

TRBTree::TRBTree()
{
    this->root = nullptr;
}

TItem *TRBTree::Search(char *keyword)
{
    if (root) {
        return root->Searchrec(keyword);
    } else return nullptr;
}
void TRBTree::Output(char *keyword)
{
    TItem *out = this->Search(keyword);
    if (out) {
        cout << out->Number() << endl;
    } else {
        cout << "NoSuchWord" << endl;
    }
}
void TRBTree::RightRotation(TItem *node)
{
    TItem *node2 = node->Left();
    TItem *tmp = nullptr;
    node->SetLeft(node2->Right());
    if (node2->Right()) {
        tmp = node2->Right();
        tmp->SetParent(node);
    }
    node2->SetParent(node->Parent());
    tmp = node->Parent();
    if (node->Parent()) {
        this->root = node2;
    } else if (node == tmp->Right()) {
        tmp->SetRight(node2);
    } else {
        tmp->SetLeft(node2);
    }
    node2->SetRight(node);
    node->SetParent(node2);
}
void TRBTree::LeftRotation(TItem *node)
{
    TItem *node2 = node->Right();
    TItem *tmp = nullptr;
    node->SetRight(node2->Left());
    if (node2->Left()) {
        tmp = node2->Left();
        tmp->SetParent(node);
    }
    node2->SetParent(node->Parent());
    tmp = node->Parent();
    if (node->Parent()) {
        this->root = node2;
    } else if (node == tmp->Left()) {
        tmp->SetLeft(node2);
    } else {
        tmp->SetRight(node2);
    }
    node2->SetLeft(node);
    node->SetParent(node2);
}

void TRBTree::Insert(unsigned long long number, char *keyword)
{
    int cmp = 0;
    TItem *in = new TItem(number, keyword);
    if (root == nullptr) {
        root = new TItem(number, keyword);
        root->SetColor(BLACK);
        cout << "OK" << endl;
    } else {
        TItem *current = root;
        while (true) {
            cmp = strcmp( current->Keyword(), keyword);
            if (cmp == 0) {
                delete in;
                cout << "Exist" << endl;
                return;
            } else if (cmp < 0) {
                if (current->Right()) {
                    current = current->Right();
                } else {
                    in = new TItem(number, keyword);
                    in->SetColor(RED);
                    in->SetParent(current);
                    current->SetRight(in);
                    cout << "OK" << endl;
                    break;
                }
            } else {
                if (current->Left()) {
                    current = current->Left();
                } else {
                    in = new TItem(number, keyword);
                    in->SetColor(RED);
                    in->SetParent(current);
                    current->SetLeft(in);
                    cout << "OK" << endl;
                    break;
                }
            }
        }
        TItem *parent = in->Parent();
        TItem *grandpa = in->Grandpa();
        while ((in != this->root) && (parent->Color()) == RED) {
            if (in->Parent() == grandpa->Left()) {
                TItem *node = grandpa->Right();
                if ((node->Color()) == RED) {
                    parent->SetColor(BLACK);
                    node->SetColor(BLACK);
                    grandpa->SetColor(RED);
                    in = grandpa;
                } else if (in == parent->Right()) {
                    in = in->Parent();
                    this->LeftRotation(in);
                    parent->SetColor(BLACK);
                    grandpa->SetColor(RED);
                    this->RightRotation(grandpa);
                }
            } else {
                TItem *node = grandpa->Left();
                if ((node->Color()) == RED) {
                    parent->SetColor(BLACK);
                    node->SetColor(BLACK);
                    grandpa->SetColor(RED);
                    in = grandpa;
                } else if (in == parent->Left()) {
                    in = in->Parent();
                    this->RightRotation(in);
                    parent->SetColor(BLACK);
                    grandpa->SetColor(RED);
                    this->LeftRotation(grandpa);
                }
            }
        }
        root->SetColor(BLACK);
    }
}

void TRBTree::Delete(char *keyword)
{
    TItem *temp = this->Search(keyword);
    if (temp) {
        TItem *parent = temp->Parent();
        if ((temp->Right()) && !(temp->Left())) {
            if (!parent) {
                this->root = temp->Right();
            } else if (parent->Right() == temp) {
                parent->SetRight(temp->Right());
            } else if (parent->Left() == temp) {
                parent->SetLeft(temp->Right());
            }
        } else if (!(temp->Right()) && (temp->Left())) {
            if (!parent) {
                this->root = temp->Left();
            } else if (parent->Right() == temp) {
                parent->SetRight(temp->Left());
            } else if (parent->Left() == temp) {
                parent->SetLeft(temp->Left());
            }
        } else if ((temp->Right()) && (temp->Left())) {
            if (!parent) {
                this->root = temp->Right();
            } else if (parent->Right() == temp) {
                parent->SetRight(temp->Right());
            } else if (parent->Left() == temp) {
                parent->SetLeft(temp->Right());
            }
            TItem *temp2 = temp->Right();
            while (temp2->Left()) {
                temp2 = temp2->Left();
                temp2->SetLeft(temp->Left());
            }
        } else {
            if (!parent) {
                this->root = nullptr;
            } else if (parent->Right() == temp) {
                parent->SetRight(nullptr);
            } else if (parent->Left() == temp) {
                parent->SetLeft(nullptr);
            }
        }
        delete temp;
        cout << "OK" << endl;
    } else return;
}
void TRBTree::Save(char *name)
{
    //ofstream dict;
    //dict.open(name);

}
void TRBTree::Load(char *name)
{

}
TRBTree::~TRBTree()
{
    if (root) {
        root->Deleterec();
        //delete root;
        this->root = nullptr;
    }
    this->root = nullptr;
}
