#include "redblacktree.h"
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

bool IsNIL(TItem *it)
{
    if (strcmp(it->Keyword(), "___NIL___") == 0) {
        return true;
    } else return false;
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
    if (!IsNIL(node->Left())) {
        TItem *node2 = node->Left();
        node->SetLeft(node2->Right());
        if (!IsNIL(node2->Right())) {
            TItem *tmp = node2->Right();
            tmp->SetParent(node);
        }
        node2->SetParent(node->Parent());
        TItem *tmp = node->Parent();
        if (IsNIL(node->Parent())) {
            this->root = node2;
        } else {
            if (node == (tmp->Right())) {
                tmp->SetRight(node2);
            } else {
                tmp->SetLeft(node2);
            }
        }
        node2->SetRight(node);
        node->SetParent(node2);
    }
}
void TRBTree::LeftRotation(TItem *node)
{
    if (!IsNIL(node->Left())) {
        TItem *node2 = node->Right();
        node->SetRight(node2->Left());
        if (!IsNIL(node2->Left())) {
            TItem *tmp = node2->Left();
            tmp->SetParent(node);
        }
        node2->SetParent(node->Parent());
        TItem *tmp = node->Parent();
        if (IsNIL(node->Parent())) {
            this->root = node2;
        } else {
            if (node == (tmp->Left())) {
                tmp->SetLeft(node2);
            } else {
                tmp->SetRight(node2);
            }
        }
        node2->SetLeft(node);
        node->SetParent(node2);
    }
}

void TRBTree::Insert(unsigned long long number, char *keyword)
{
    int cmp = 0;
    TItem *in = nullptr;
    if (root == nullptr) {
        root = new TItem(number, keyword);
        root->SetColor(BLACK);
        root->SetLeft(new TItem(root));
        root->SetRight(new TItem(root));
        cout << "OK" << endl;
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
                    in->SetLeft(new TItem(in));
                    in->SetRight(new TItem(in));
                    current->SetRight(in);
                    cout << "OK" << endl;
                    break;
                }
            } else {
                if (!IsNIL(current->Left())) {
                    current = current->Left();
                } else {
                    in = new TItem(number, keyword);
                    in->SetParent(current);
                    in->SetLeft(new TItem(in));
                    in->SetRight(new TItem(in));
                    current->SetLeft(in);
                    cout << "OK" << endl;
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
            } else {
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
}

void TRBTree::DeleteFix(TItem *it)
{
    while (it != this->root && it->Color() == BLACK) {

    }
}

void TRBTree::Delete(char *keyword)
{
    TItem *temp = this->Search(keyword);
    if (!IsNIL(temp)) {
        TItem *parent = temp->Parent();
        if (!IsNIL(temp->Right()) || IsNIL(temp->Left())) {
            if (!parent) {
                this->root = temp->Right();
            } else if (parent->Right() == temp) {
                parent->SetRight(temp->Right());
            } else if (parent->Left() == temp) {
                parent->SetLeft(temp->Right());
            }
        } else if (IsNIL(temp->Right()) || !IsNIL(temp->Left())) {
            if (!parent) {
                this->root = temp->Left();
            } else if (parent->Right() == temp) {
                parent->SetRight(temp->Left());
            } else if (parent->Left() == temp) {
                parent->SetLeft(temp->Left());
            }
        } else if (!IsNIL(temp->Right()) || !IsNIL(temp->Left())) {
            if (!parent) {
                this->root = temp->Right();
            } else if (parent->Right() == temp) {
                parent->SetRight(temp->Right());
            } else if (parent->Left() == temp) {
                parent->SetLeft(temp->Right());
            }
            TItem *temp2 = temp->Right();
            while (!IsNIL(temp2->Left())) {
                temp2 = temp2->Left();
                temp2->SetLeft(temp->Left());
            }
        } else {
            if (!parent) {
                this->root = nullptr;
            } else if (parent->Right() == temp) {
                parent->SetRight(new TItem(parent));
            } else if (parent->Left() == temp) {
                parent->SetLeft(new TItem(parent));
            }
        }
        delete temp;
        if (parent->Color() == BLACK) {
            this->DeleteFix(parent);
        }
        cout << "OK" << endl;
    } else return;
}

void TRBTree::SaveRec(TItem *node, FILE *file)
{
    unsigned long long num = 0;
    if (file == nullptr) {
        return;
    }
    if (IsNIL(node)) {
        fwrite("NIL", sizeof(char), strlen("NIL"), file);
        return;
    }
    num = node->Number();
    char *keyword;
    strcpy(keyword, node->Keyword());
    fwrite(&num, sizeof(int), 1, file);
    fwrite(&keyword, sizeof(char), strlen(keyword), file);
    if (node->Color() == BLACK) {
        fwrite("BLACK\0", sizeof(char), 1, file);
    } else {
        fwrite("RED\0", sizeof(char), 1, file);
    }
    if (!IsNIL(node->Left())) {
        this->SaveRec(node->Left(), file);
    }
    if (!IsNIL(node->Right())) {
        this->SaveRec(node->Right(), file);
    }
}

void TRBTree::Save(char *name)
{
    FILE *file = fopen(name, "wb");
    this->SaveRec(root, file);
    fclose(file);
}

void TRBTree::LoadRec(TItem *node, FILE *file)
{
    if (file == nullptr) {
        return;
    }
    char *keyword = (char *) calloc(sizeof(char), 257);
    if (!file->eof()) {

    }
    free(keyword);
}
void TRBTree::Load(char *name)
{
    FILE *file = fopen(name, "rb");
    this->LoadRec(root, file);
    fclose(file);
}
TRBTree::~TRBTree()
{
    if (root) {
        root->Deleterec();
        this->root = nullptr;
    }
}
