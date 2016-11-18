#include "redblacktree.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>

using namespace std;

bool IsNIL(TItem *it)
{
    if (strcmp(it->Keyword(), "___NIL___") == 0) {
        return true;
    } else return false;
}
void ToLower(char *keyword)
{
    if (*keyword >= 'A' && *keyword <= 'Z') {
        *keyword = 'a' + (*keyword - 'A');
    }
}

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
        cout << "OK: " << out->Number() << endl;
    } else {
        cout << "NoSuchWord" << endl;
    }
}
void TRBTree::RightRotation(TItem *node)
{
    cout << "ROTATION" << endl;
    TItem *node2 = node->Left();
    node->SetLeft(node2->Right());
    if (!IsNIL(node2->Right())) {
        TItem *tmp = node2->Right();
        tmp->SetParent(node);
    }
    if (!IsNIL(node2)) {
        node2->SetParent(node->Parent());
    }
    TItem *tmp = node->Parent();
    if (!tmp) {
        if (tmp == tmp->Right()) {
            tmp->SetRight(node2);
        } else {
            tmp->SetLeft(node2);
        }
    } else {
        this->root = node2;
    }
    node2->SetRight(node);
    node->SetParent(node2);
    cout << "ROTATED-RIGHT" << endl;
}
void TRBTree::LeftRotation(TItem *node)
{
    cout << "ROTATION" << endl;
    TItem *node2 = node->Right();
    node->SetRight(node2->Left());
    if (!IsNIL(node2->Left())) {
        TItem *tmp = node2->Left();
        tmp->SetParent(node);
    }
    if (!IsNIL(node2)) {
        node2->SetParent(node->Parent());
    }
    TItem *tmp = node->Parent();
    if (tmp) {
        if (tmp == tmp->Left()) {
            tmp->SetLeft(node2);
        } else {
            tmp->SetRight(node2);
        }
    } else {
        this->root = node2;
    }
    node2->SetLeft(node);
    node->SetParent(node2);
    cout << "ROTATED-LEFT" << endl;
}

void TRBTree::Insert(unsigned long long number, char *keyword)
{
    int cmp = 0;
    TItem *in = nullptr;
    if (root == nullptr) {
        root = new TItem(number, keyword);
        root->SetColor(BLACK);
    } else {
        TItem *current = root;
        while (true) {
            cmp = strcmp(current->Keyword(), keyword);
            if (cmp == 0) {
                cout << "Exist" << endl;
                return;
            } else if (cmp < 0) {
                if (!IsNIL(current->Right())) {
                    current = current->Right();
                } else {
                    in = new TItem(number, keyword);
                    in->SetParent(current);
                    current->SetRight(in);
                    break;
                }
            } else {
                if (!IsNIL(current->Left())) {
                    current = current->Left();
                } else {
                    in = new TItem(number, keyword);
                    in->SetParent(current);
                    current->SetLeft(in);
                    break;
                }
            }
        }
        in->SetColor(RED);
        TItem *parent = in->Parent();
        TItem *grandpa = in->Grandpa();
        while ((in != this->root) && (parent->Color()) == RED) {
            if (parent == grandpa->Left()) {
                TItem *node = grandpa->Right();
                if ((node->Color()) == RED) {
                    parent->SetColor(BLACK);
                    node->SetColor(BLACK);
                    grandpa->SetColor(RED);
                    in = grandpa;
                } else {
                    if (in == parent->Right()) {
                        in = in->Parent();
                        this->LeftRotation(in);
                    }
                    parent->SetColor(BLACK);
                    grandpa->SetColor(RED);
                    this->RightRotation(grandpa);
                }
            } else if (parent == grandpa->Right()) {
                TItem *node = grandpa->Left();
                if ((node->Color()) == RED) {
                    parent->SetColor(BLACK);
                    node->SetColor(BLACK);
                    grandpa->SetColor(RED);
                    in = grandpa;
                } else {
                    if (in == parent->Left()) {
                        in = in->Parent();
                        this->RightRotation(in);
                    }
                    parent->SetColor(BLACK);
                    grandpa->SetColor(RED);
                    this->LeftRotation(grandpa);
                }
            }
        }
        root->SetColor(BLACK);
    }
    cout << "OK" << endl;
}

void TRBTree::DeleteFix(TItem *it)
{
    TItem *temp = it->Parent();
    TItem *temp2 = nullptr;
    TItem *temp21 = nullptr;
    TItem *temp22 = nullptr;
    while (it != this->root && it->Color() == BLACK) {
        if (it == (temp->Left())) {
            temp2 = temp->Right();
            if (temp2->Color() == RED) {
                temp2->SetColor(BLACK);
                temp->SetColor(RED);
                this->LeftRotation(temp);
                temp2 = temp->Right();
            }
            temp21 = temp2->Left();
            temp22 = temp2->Right();
            if (temp21->Color() == BLACK && temp22->Color() == BLACK) {
                temp2->SetColor(RED);
                it = it->Parent();
            } else {
                if (temp22->Color() == BLACK) {
                    temp21->SetColor(BLACK);
                    temp2->SetColor(RED);
                    this->RightRotation(temp2);
                    temp2 = temp->Right();
                }
                temp2->SetColor(temp->Color());
                temp->SetColor(BLACK);
                temp22->SetColor(BLACK);
                this->LeftRotation(temp);
                it = this->root;
            }
        } else if (it == (temp->Right())) {
            temp2 = temp->Left();
            if (temp2->Color() == RED) {
                temp2->SetColor(BLACK);
                temp->SetColor(RED);
                this->RightRotation(temp);
                temp2 = temp->Left();
            }
            temp21 = temp2->Right();
            temp22 = temp2->Left();
            if (temp21->Color() == BLACK && temp22->Color() == BLACK) {
                temp2->SetColor(RED);
                it = it->Parent();
            } else {
                if (temp22->Color() == BLACK) {
                    temp21->SetColor(BLACK);
                    temp2->SetColor(RED);
                    this->LeftRotation(temp2);
                    temp2 = temp->Left();
                }
                temp2->SetColor(temp->Color());
                temp->SetColor(BLACK);
                temp22->SetColor(BLACK);
                this->RightRotation(temp);
                it = root;
            }
        }
    }
    it->SetColor(BLACK);
}

void TRBTree::Delete(char *keyword)
{
    TItem *temp = this->Search(keyword);
    TItem *temp2 = nullptr;
    TItem *temp3 = nullptr;
    if (temp && !IsNIL(temp)) {
        if (IsNIL(temp->Left()) && IsNIL(temp->Right())) {
            temp2 = temp;
        } else {
            temp2 = temp->Successor();
        }
        if (!IsNIL(temp2->Left())) {
            temp3 = temp2->Left();
        } else if (!IsNIL(temp2->Right())) {
            temp3 = temp2->Right();
        }
        TItem *parent = temp2->Parent();
        temp3->SetParent(parent);
        if (IsNIL(temp2->Parent())) {
            this->root = temp3;
        } else {
            if (temp2 == parent->Left()) {
                parent->SetLeft(temp3);
            } else if (temp2 == parent->Right()) {
                parent->SetRight(temp3);
            }
        }
        if (temp2 != temp) {
            temp->CopyData(temp2);
        }
        if (temp2->Color() == BLACK) {
            this->DeleteFix(temp2);
        }
        delete temp2;
        cout << "OK" << endl;
    } else {
        cout << "NoSuchWord" << endl;
    }
}

void TRBTree::SaveRec(TItem *node, FILE *out)
{
    char nod = 0;
    if (node == nullptr) {
        nod = 0;
        fprintf(out, "%c\n", nod);
        return;
    } else if (!IsNIL(node->Left()) && !IsNIL(node->Right())) {
        nod = 1;
        fprintf(out, "%c\n", nod);
    } else {
        nod = 2;
        fprintf(out, "%c\n", nod);
        return;
    }
    unsigned long long number = node->Number();
    char *keyword = node->Keyword();
    TColor color = node->Color();
    fprintf(out, "%llu\n", number);
    fprintf(out, "%s\n", keyword);
    fprintf(out, "%d\n", color);
    if (node->Left()) {
        this->SaveRec(node->Left(), out);
    }
    if (node->Right()) {
        this->SaveRec(node->Right(), out);
    }
}

void TRBTree::Save(char *name)
{
    FILE *out = fopen(name, "w");
    if (out) {
        this->SaveRec(root, out);
        fclose(out);
        cout << "OK" << endl;
    } else {
        cout << "ERROR: Couldn't create file" << endl;
    }
}

TItem *TRBTree::LoadRec(TItem *parent, FILE *in)
{
    char nod;
    unsigned long long num = 0;
    char *keyword = (char *) calloc(sizeof(char), 257);
    TColor color;
    fscanf(in, "%c", &nod);
    if (nod == 1) {
        fscanf(in, "%llu", &num);
        fscanf(in, "%s", keyword);
        fscanf(in, "%d", (int*)&color);
        TItem *item = new TItem(num, keyword);
        item->SetColor(color);
        item->SetLeft(this->LoadRec(item, in));
        item->SetRight(this->LoadRec(item, in));
        return item;
    } else if (nod == 0) {
        TItem *nil = new TItem(parent);
        return nil;
    } else {
        return nullptr;
    }
}
void TRBTree::Load(char *name)
{
    FILE *in = fopen(name, "r");
    if (in) {
        root = this->LoadRec(root, in);
        fclose(in);
        cout << "OK" << endl;
    } else {
        cout << "ERROR: Couldn't create file" << endl;
    }
}
TRBTree::~TRBTree()
{
    if (root) {
        root->Deleterec();
        this->root = nullptr;
    }
}
