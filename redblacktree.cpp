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
}
void TRBTree::LeftRotation(TItem *node)
{
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
}

void TRBTree::Insert(unsigned long long number, char *keyword)
{
    int cmp = 0;
    TItem *in = nullptr;
    if (root == nullptr) {
        root = new TItem(number, keyword);
        root->SetLeft(new TItem(root));
        root->SetRight(new TItem(root));
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
                    in->SetLeft(new TItem(in));
                    in->SetRight(new TItem(in));
                    current->SetRight(in);
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
        } else {
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
    if (temp && !IsNIL(temp)) {
        TItem *parent = temp->Parent();
        if (!IsNIL(temp->Right()) && IsNIL(temp->Left())) {
            if (!parent) {
                this->root = temp->Right();
            } else if (parent->Right() == temp) {
                parent->SetRight(temp->Right());
            } else if (parent->Left() == temp) {
                parent->SetLeft(temp->Right());
            }
            if (parent && parent->Color() == BLACK) {
                this->DeleteFix(temp);
            }
        } else if (IsNIL(temp->Right()) && !IsNIL(temp->Left())) {
            if (!parent) {
                this->root = temp->Left();
            } else if (parent->Right() == temp) {
                parent->SetRight(temp->Left());
            } else if (parent->Left() == temp) {
                parent->SetLeft(temp->Left());
            }
            if (parent && parent->Color() == BLACK) {
                this->DeleteFix(temp);
            }
        } else if (!IsNIL(temp->Right()) && !IsNIL(temp->Left())) {
            if (!parent) {
                this->root = temp->Right();
            } else if (parent->Right() == temp) {
                parent->SetLeft(temp->Right());
            } else if (parent->Left() == temp) {
                parent->SetLeft(temp->Right());
            }

            TItem *temp2 = temp->Right();
            while (!IsNIL(temp2->Left())) {
                temp2 = temp2->Left();
            }
            temp2->SetLeft(temp->Left());
            if (parent && parent->Color() == BLACK) {
                this->DeleteFix(temp2);
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
        cout << "OK" << endl;
    } else {
        cout << "NoSuchWord" << endl;
    }
}

void TRBTree::SaveRec(TItem *node, FILE *out)
{
    if (root == nullptr) {
        //fwrite("NIL", sizeof(char), 3, out);
        //fwrite("NIL", sizeof(char), 3, out);
        //fwrite("0", sizeof(char), 1, out);
        fprintf(out, "NIL");
        fprintf(out, "NIL");
        fprintf(out, "0");
        return;
    }
    if (IsNIL(node)) {
        //fwrite("NIL", sizeof(char), 3, out);
        //fwrite("NIL", sizeof(char), 3, out);
        //fwrite("0", sizeof(char), 1, out);
        fprintf(out, "NIL");
        fprintf(out, "NIL");
        fprintf(out, "0");
        return;
    }
    unsigned long long number = node->Number();
    char *keyword = node->Keyword();
    TColor color = node->Color();
    //fwrite(&number, sizeof(unsigned long long), 1, out);
    fprintf(out, "%llu", number);
    //fwrite(&keyword, sizeof(char), strlen(keyword), out);
    fprintf(out, "%s", keyword);
    //fwrite(&color, sizeof(TColor), 1, out);
    fprintf(out, "%d", color);
    //fwrite("(", sizeof(char), 1, out);
    fprintf(out, "(");
    if (node->Left()) {
        this->SaveRec(node->Left(), out);
    }
    //fwrite(",", sizeof(char), 1, out);
    fprintf(out, ",");
    if (node->Right()) {
        this->SaveRec(node->Right(), out);
    }
    //fwrite(")", sizeof(char), 1, out);
    fprintf(out, ")");
}

void TRBTree::Save(char *name)
{
    FILE *out = fopen(name, "w");
    if (out) {
        this->SaveRec(root, out);
        fclose(out);
    } else {
        cout << "ERROR: Couldn't create file" << endl;
    }
}

void TRBTree::LoadRec(TItem *node, FILE *in)
{

}
void TRBTree::Load(char *name)
{
    FILE *in = fopen(name, "rb");
    if (in) {
        this->SaveRec(root, in);
        fclose(in);
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
