#include "rbtree.h"

bool TRBTree::IsNIL(TNode *node)
{
    return strcmp(node->keyword, "__NIL__") == 0 ? true : false;
}
TRBTree::TNode *TRBTree::CreateNIL(TNode *parent)
{
    TNode *node = (TNode *) malloc(sizeof(TNode));
    if (node == nullptr) {
        cout << "ERROR: couldn't malloc a lot of memory for new node" << endl;
        return nullptr;
    }
    node->keyword = (char *) calloc(sizeof(char), NIL_SIZE);
    if (node->keyword == nullptr) {
        cout << "ERROR: couldn't calloc a lot of memory for keyword in new node" << endl;
        free(node);
        return nullptr;
    }
    strcpy(node->keyword, "__NIL__");
    node->number = 0;
    node->color = BLACK;
    node->left = nullptr;
    node->right = nullptr;
    node->parent = parent;
    return node;
}
TRBTree::TNode *TRBTree::CreateNode(TNode *parent, char *keyword, unsigned long long number)
{
    TNode *node = (TNode *) malloc(sizeof(TNode));
    if (node == nullptr) {
        cout << "ERROR: couldn't malloc a lot of memory for new node" << endl;
        return nullptr;
    }
    node->number = number;
    node->keyword = (char *) calloc(sizeof(char), KEY_SIZE);
    if (node->keyword == nullptr) {
        cout << "ERROR: couldn't calloc a lot of memory for keyword in new node" << endl;
        free(node);
        return nullptr;
    }
    strcpy(node->keyword, keyword);
    node->color = RED;
    node->left = CreateNIL(node);
    node->right = CreateNIL(node);
    node->parent = parent;
    return node;
}
TRBTree::TNode *TRBTree::Minimum(TNode *node)
{
    while (!IsNIL(node->left)) {
        node = node->left;
    }
    return node;
}
TRBTree::TNode *TRBTree::Successor(TNode *node)
{
    if (!IsNIL(node->right)) {
        return Minimum(node->right);
    }
    TNode *parent = node->parent;
    while (!IsNIL(parent)) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

TRBTree::TNode *TRBTree::Recoursesearch(char *keyword, TNode *node)
{
    if (node == nullptr) {
        return nullptr;
    } else if (strcmp(keyword, node->keyword) == 0 || IsNIL(node)) {
        return node;
    } else if (strcmp(keyword, node->keyword) > 0) {
        return Recoursesearch(keyword, node->right);
    } else if (strcmp(keyword, node->keyword) < 0) {
        return Recoursesearch(keyword, node->left);
    } else {
        return nullptr;
    }
}

void TRBTree::Recoursedestroy(TNode *node)
{
    if (node->left != nullptr) {
        Recoursedestroy(node->left);
    }
    if (node->right != nullptr) {
        Recoursedestroy(node->right);
    }
    free(node->keyword);
    free(node);
}

void TRBTree::LeftRotation(TNode *node)
{
    TNode *tmp = node->right;
    node->right = tmp->left;
    if (!IsNIL(tmp->left)) {
        tmp->left->parent = node;
    }
    tmp->parent = node->parent;
    if (node->parent == nullptr) {
        this->root = tmp;
    } else {
        if (node == node->parent->left) {
            node->parent->left = tmp;
        } else if (node == node->parent->right) {
            node->parent->right = tmp;
        }
    }
    tmp->left = node;
    node->parent = tmp;
}
void TRBTree::RightRotation(TNode *node)
{
    TNode *tmp = node->left;
    node->left = tmp->right;
    if (!IsNIL(tmp->right)) {
        tmp->right->parent = node;
    }
    tmp->parent = node->parent;
    if (node->parent == nullptr) {
        this->root = tmp;
    } else {
        if (node == node->parent->right) {
            node->parent->right = tmp;
        } else if (node == node->parent->left) {
            node->parent->right = tmp;
        }
    }
    tmp->right = node;
    node->parent = tmp;
}

void TRBTree::InsertFix(TNode *node)
{
    while (node != this->root && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            TNode *tmp = node->parent->parent->right;
            if (tmp->color == RED) {
                node->parent->color = BLACK;
                tmp->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    LeftRotation(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                RightRotation(node->parent->parent);
            }
        } else if (node->parent == node->parent->parent->right) {
            TNode *tmp = node->parent->parent->left;
            if (tmp->color == RED) {
                node->parent->color = BLACK;
                tmp->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    RightRotation(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                LeftRotation(node->parent->parent);
            }
        }
    }
    this->root->color = BLACK;
}

void TRBTree::DeleteFix(TNode *node)
{
    while (node != this->root && node->color == BLACK) {
        if (node == node->parent->left) {
            TNode *temp = node->parent->right;
            if (temp->color == RED) {
                temp->color = BLACK;
                node->parent->color = RED;
                LeftRotation(node->parent);
                temp = node->parent->right;
            }
            if (temp->left->color == BLACK && temp->right->color == BLACK) {
                temp->color = RED;
                node = node->parent;
            } else {
                if (temp->right->color == BLACK) {
                    temp->left->color = BLACK;
                    temp->color = RED;
                    RightRotation(temp);
                    temp = node->parent->right;
                }
                temp->color = node->parent->color;
                temp->right->color = node->parent->color = BLACK;
                LeftRotation(node->parent);
                node = this->root;
            }
        } else {
            TNode *temp = node->parent->left;
            if (temp->color == RED) {
                temp->color = BLACK;
                node->parent->color = RED;
                RightRotation(node->parent);
                temp = node->parent->left;
            }
            if (temp->right->color == BLACK && temp->left->color == BLACK) {
                temp->color = RED;
                node = node->parent;
            } else {
                if (temp->left->color == BLACK) {
                    temp->right->color = BLACK;
                    temp->color = RED;
                    LeftRotation(temp);
                    temp = node->parent->left;
                }
                temp->color = node->parent->color;
                temp->left->color = node->parent->color = BLACK;
                RightRotation(node->parent);
                node = this->root;
            }
        }
    }
    node->color = BLACK;
}

void TRBTree::Ser(TNode *node, ofstream &file)
{
    if (file != nullptr) {

    }
}

TRBTree::TNode *TRBTree::Deser(ifstream &file)
{
    return nullptr;
}
TRBTree::TRBTree()
{
    this->root = nullptr;
}

void TRBTree::Insert(char *keyword, unsigned long long number)
{
    if (this->root == nullptr) {
        this->root = CreateNode(nullptr, keyword, number);
        this->root->color = BLACK;
    } else {
        TNode *current = this->root;
        while (!IsNIL(current)) {
            if (strcmp(keyword, current->keyword) == 0) {
                cout << "Exist" << endl;
            } else if (strcmp(keyword, current->keyword) < 0) {
                current = current->left;
            } else if (strcmp(keyword, current->keyword) > 0) {
                current = current->right;
            }
        }
        current->number = number;
        current->keyword = (char *) realloc(current->keyword, sizeof(char) * KEY_SIZE);
        memset(current->keyword, 0, sizeof(char));
        strcpy(current->keyword, keyword);
        current->left = CreateNIL(current);
        current->right = CreateNIL(current);
        InsertFix(current);
    }
    cout << "OK" << endl;
}
void TRBTree::Search(char *keyword)
{
    if (this->root == nullptr) {
        cout << "ERROR: couldn't start search, because the root of the tree is nullptr" << endl;
        return;
    }
    TNode *out = Recoursesearch(keyword, this->root);
    if (out != nullptr && !IsNIL(out)) {
        cout << "OK: " << out->number << endl;
    } else {
        cout << "NoSuchWord" << endl;
    }
}
void TRBTree::Delete(char *keyword)
{
    TNode *deleting = Recoursesearch(keyword, this->root);
    if (deleting == nullptr) {
        cout << "NoSuchWord" << endl;
        return;
    }
    TNode *next = deleting;
    TNode *temp = nullptr;
    if (IsNIL(deleting->left) || IsNIL(deleting->right)) {
        next = deleting;
    } else {
        next = Minimum(deleting->right);
    }
    if (!IsNIL(next->left)) {
        temp = next->left;
    } else if (!IsNIL(next->right)) {
        temp = next->right;
    }
    if (next->parent == nullptr) {
        this->root = temp;
    } else if (next == next->parent->left) {
        next->parent->left = temp;
    } else {
        next->parent->right = temp;
    }
    temp->parent = next->parent;
    if (deleting != next) {
        deleting->number = next->number;
        memset(deleting->keyword, 0, sizeof(char));
        strcpy(deleting->keyword, next->keyword);
    }
    if (next->color == BLACK) {
        DeleteFix(temp);
    }
    free(next->keyword);
    free(next->left->keyword);
    free(next->right->keyword);
    free(next->left);
    free(next->right);
    free(next);
    cout << "OK" << endl;
}
void TRBTree::Save(const char *path)
{
    cout << "OK" << endl;
}
void TRBTree::Load(const char *path)
{
    cout << "OK" << endl;
}
TRBTree::~TRBTree()
{
    if (this->root != nullptr) {
        Recoursedestroy(this->root);
    }
    this->root = nullptr;
}
