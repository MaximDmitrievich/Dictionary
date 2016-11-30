#include "rbtree.h"

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
    node->left = nil;
    node->right = nil;
    node->parent = parent;
    return node;
}
TRBTree::TNode *TRBTree::Minimum(TNode *node)
{
    while (node->left != nil) {
        node = node->left;
    }
    return node;
}
TRBTree::TNode *TRBTree::Successor(TNode *node)
{
    if (node->right != nil) {
        return Minimum(node->right);
    }
    TNode *parent = node->parent;
    while (parent != nil && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

TRBTree::TNode *TRBTree::Recoursesearch(char *keyword, TNode *node)
{
    if (node == nil) {
        return nil;
    } else if (strcmp(keyword, node->keyword) == 0) {
        return node;
    } else if (strcmp(keyword, node->keyword) > 0) {
        return Recoursesearch(keyword, node->right);
    } else if (strcmp(keyword, node->keyword) < 0) {
        return Recoursesearch(keyword, node->left);
    } else return nullptr;
}

void TRBTree::Recoursedestroy(TNode *node)
{
    if (node->left != nil) {
        Recoursedestroy(node->left);
    }
    if (node->right != nil) {
        Recoursedestroy(node->right);
    }
    free(node->keyword);
    free(node);
}

void TRBTree::LeftRotation(TNode *node)
{
    if (node->right != nil) {
        TNode *tmp = node->right;
        node->right = tmp->left;
        if (tmp->left != nil) {
            tmp->left->parent = node;
        }
        tmp->parent = node->parent;
        if (node->parent == nil) {
            this->root = tmp;
        } else if (node == node->parent->left) {
            node->parent->left = tmp;
        } else {
            node->parent->right = tmp;
        }
        tmp->left = node;
        node->parent = tmp;
    } else {
        return;
    }
}
void TRBTree::RightRotation(TNode *node)
{
    if (node->left != nil) {
        TNode *tmp = node->left;
        node->left = tmp->right;
        if (tmp->right != nil) {
            tmp->right->parent = node;
        }
        tmp->parent = node->parent;
        if (node->parent == nil) {
            this->root = tmp;
        } else if (node == node->parent->left) {
            node->parent->left = tmp;
        } else {
            node->parent->right = tmp;
        }
        tmp->right = node;
        node->parent = tmp;
    } else {
        return;
    }
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
    int num = NIL;
    if (node == nil) {
        num = NIL;
        file.write((char *) &num, sizeof(int));
        return;
    } else if (node->left == nil && node->right == nil) {
        num = NO_CHILDREN;
    } else {
        num = CHILDERN;
    }
    size_t length = strlen(node->keyword);
    file.write((char *) &num, sizeof(int));
    file.write((char *) &length, sizeof(size_t));
    file.write(node->keyword, length);
    file.write((char *) &node->number, sizeof(unsigned long long));
    file.write((char *) &node->color, sizeof(TColor));
    Ser(node->left, file);
    Ser(node->right, file);
}

TRBTree::TNode *TRBTree::Deser(TNode *parent, ifstream &file)
{
    int num = 0;
    file.read((char *) &num, sizeof(int));
    if (num == NIL) {
        return nil;
    }
    size_t length;
    char keywordbuf[KEY_SIZE] = { '\0' };
    unsigned long long number = 0;
    file.read((char *) &length, sizeof(size_t));
    file.read(keywordbuf, length);
    keywordbuf[length] = '\0';
    file.read((char *) &number, sizeof(unsigned long long));
    TNode *node = CreateNode(parent, keywordbuf, number);
    file.read((char *) &node->color, sizeof(TColor));
    node->left = Deser(node, file);
    node->right = Deser(node, file);
    return node;
}
TRBTree::TRBTree()
{
    this->nil = (TNode *) malloc(sizeof(TNode ));
    this->nil->parent = this->nil->left = this->nil->right = nullptr;
    this->nil->keyword = nullptr;
    this->nil->color = BLACK;
    this->nil->number = 0;
    this->root = nil;
}

void TRBTree::Insert(char *keyword, unsigned long long number)
{
    if (this->root == nil) {
        this->root = CreateNode(nil, keyword, number);
        this->root->color = BLACK;
    } else {
        TNode *current = this->root;
        TNode *parent = nullptr;
        char cmp;
        while (current != nil) {
            cmp = strcmp(keyword, current->keyword);
            if (cmp == 0) {
                cout << "Exist" << endl;
                return;
            } else if (cmp < 0) {
                parent = current;
                current = current->left;
            } else if (cmp > 0) {
                parent = current;
                current = current->right;
            }
        }
        current = nullptr;
        current = CreateNode(parent, keyword, number);
        if (cmp < 0) {
            parent->left = current;
        } else {
            parent->right = current;
        }
        current->color = RED;
        InsertFix(current);
    }
    cout << "OK" << endl;
}
void TRBTree::Search(char *keyword)
{
    if (this->root == nil) {
        cout << "ERROR: couldn't start search, because dictionary is emtpy" << endl;
        return;
    }
    TNode *out = Recoursesearch(keyword, this->root);
    if (out != nil) {
        cout << "OK: " << out->number << endl;
    } else {
        cout << "NoSuchWord" << endl;
    }
}
void TRBTree::Delete(char *keyword)
{
    TNode *node = Recoursesearch(keyword, this->root);
    if (node == nil || node == nullptr) {
        cout << "NoSuchWord" << endl;
        return;
    }
    TNode *removed = node;
    TNode *newnode = nil;
    if (node->left == nil || node->right == nil) {
        removed = node;
    } else {
        removed = Minimum(node);
    }
    if (removed->left != nil) {
        newnode = removed->left;
    } else {
        newnode = removed->right;
    }
    if (removed->parent == nil) {
        this->root = newnode;
    } else if (removed == removed->parent->left) {
        removed->parent->left = newnode;
    } else {
        removed->parent->right = newnode;
    }
    newnode->parent = removed->parent;
    if (removed != node) {
        node->number = removed->number;
        strcpy(node->keyword, removed->keyword);
    }
    if (removed->color == BLACK) {
        DeleteFix(newnode);
    }
    free(removed->keyword);
    free(removed);
    cout << "OK" << endl;
}
void TRBTree::Save(const char *path)
{
    ofstream file;
    file.open(path, ios::out | ios::binary);
    if (!file.is_open()) {
        cout << "ERROR: Couldn't create file" << endl;
        return;
    }
    Ser(this->root, file);
    file.close();
    cout << "OK" << endl;
}
void TRBTree::Load(const char *path)
{
    ifstream file;
    file.open(path, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "ERROR: Couldn't open file" << endl;
        return;
    }
    if (file.eof()) {
        file.close();
        return;
    }
    TNode *newnode = Deser(nil, file);
    if (newnode != nil || newnode != nullptr) {
        if (this->root != nil) {
            Recoursedestroy(this->root);
        }
        this->root = newnode;
    }
    file.close();
    cout << "OK" << endl;
}
TRBTree::~TRBTree()
{
    if (this->root != nil) {
        Recoursedestroy(this->root);
    }
    this->root = nullptr;
    free(this->nil);
}
