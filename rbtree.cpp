#include "rbtree.h"

TRBTree::TNode *TRBTree::CreateNode(TNode *parent, char *keyword, unsigned long long number)
{
    TNode *node = (TNode *) malloc(sizeof(TNode));
    if (node == nullptr) {
        cout << "ERROR: couldn't malloc a lot of memory for new node\n";
        exit(EXIT_SUCCESS);
    }
    node->number = number;
    node->keyword = keyword;
    node->color = RED;
    node->left = &nil;
    node->right = &nil;
    node->parent = parent;
    return node;
}
TRBTree::TNode *TRBTree::Minimum(TNode *node)
{
    while (node->left != &nil) {
        node = node->left;
    }
    return node;
}
TRBTree::TNode *TRBTree::Successor(TNode *node)
{
    if (node->right != &nil) {
        return Minimum(node->right);
    }
    TNode *parent = node->parent;
    while (parent != &nil && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

TRBTree::TNode *TRBTree::Recoursesearch(char *keyword, TNode *node)
{
    if (node == &nil) {
        return &nil;
    }
    char cmp = strcasecmp(keyword, node->keyword);
    if (cmp == 0) {
        return node;
    } else if (cmp > 0) {
        return Recoursesearch(keyword, node->right);
    } else if (cmp < 0) {
        return Recoursesearch(keyword, node->left);
    } else return nullptr;
}

void TRBTree::Recoursedestroy(TNode *node)
{
    if (node->left != &nil) {
        Recoursedestroy(node->left);
    }
    if (node->right != &nil) {
        Recoursedestroy(node->right);
    }
    free(node->keyword);
    TNode *tmp = node;
    free(tmp);
    node = &nil;
}

void TRBTree::LeftRotation(TNode *node)
{
TNode *tmp = node->right;
node->right = tmp->left;
if (tmp->left != &nil) {
    tmp->left->parent = node;
    }
    tmp->parent = node->parent;
    if (node->parent == &nil) {
        this->root = tmp;
    } else if (node == node->parent->left) {
        node->parent->left = tmp;
    } else {
        node->parent->right = tmp;
    }
    tmp->left = node;
    node->parent = tmp;
}
void TRBTree::RightRotation(TNode *node)
{
    TNode *tmp = node->left;
    node->left = tmp->right;
    if (tmp->right != &nil) {
        tmp->right->parent = node;
    }
    tmp->parent = node->parent;
    if (node->parent == &nil) {
        this->root = tmp;
    } else if (node == node->parent->left) {
        node->parent->left = tmp;
    } else {
        node->parent->right = tmp;
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
        } else {
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
    char num = NIL;
    if (node == &nil) {
        num = NIL;
        file.write((char *) &num, sizeof(num));
        return;
    } else if (node->left == &nil && node->right == &nil) {
        num = NO_CHILDREN;
    } else {
        num = CHILDERN;
    }
    size_t length = strlen(node->keyword);
    file.write((char *) &num, sizeof(num));
    file.write((char *) &length, sizeof(length));
    file.write(node->keyword, length);
    file.write((char *) &node->number, sizeof(node->number));
    file.write((char *) &node->color, sizeof(node->color));
    Ser(node->left, file);
    Ser(node->right, file);
}

TRBTree::TNode *TRBTree::Deser(TNode *parent, ifstream &file)
{
    char num = 0;
    file.read((char *) &num, sizeof(char));
    if (num == NIL) {
        return &nil;
    }
    size_t length;
    unsigned long long number = 0;
    file.read((char *) &length, sizeof(length));
    char *keywordbuf = (char *) calloc(sizeof(char), length + 1);
    file.read(keywordbuf, length);
    keywordbuf[length] = '\0';
    file.read((char *) &number, sizeof(unsigned long long));
    TNode *node = CreateNode(parent, keywordbuf, number);
    file.read((char *) &node->color, sizeof(TColor));
    node->parent = node->left = node->right = &nil;
    node->left = Deser(node, file);
    node->right = Deser(node, file);
    node->left->parent = node->right->parent = node;
    return node;
}
TRBTree::TRBTree()
{
    this->nil.parent = this->nil.left = this->nil.right = nullptr;
    this->nil.keyword = nullptr;
    this->nil.color = BLACK;
    this->nil.number = 0;
    this->root = &nil;
}

void TRBTree::Insert(char *keyword, unsigned long long number)
{
    TNode *parent = &nil;
    TNode *current = this->root;
    char cmp;
    while (current != &nil) {
        cmp = strcasecmp(keyword, current->keyword);
        parent = current;
        if (cmp < 0) {
            current = current->left;
        } else if (cmp > 0) {
            current = current->right;
        } else {
            cout << "Exist\n";
            return;
        }
    }
    TNode *newnode = CreateNode(parent, keyword, number);
    if (parent == &nil) {
        this->root = newnode;
    } else if (cmp < 0) {
        parent->left = newnode;
    } else {
        parent->right = newnode;
    }
    InsertFix(newnode);
    cout << "OK\n";
}
void TRBTree::Search(char *keyword)
{
    TNode *out = this->root;
    char cmp;
    while (out != &nil) {
        if ((cmp = strcasecmp(keyword, out->keyword)) == 0) {
            break;
        } else if (cmp < 0) {
            out = out->left;
        } else {
            out = out->right;
        }
    }
    if (out != &nil) {
        cout << "OK: " << out->number << "\n";
    } else {
        cout << "NoSuchWord\n";
    }
}
void TRBTree::Delete(char *keyword)
{
    TNode *node = this->root;
    char cmp;
    while (node != &nil) {
        if ((cmp = strcasecmp(keyword, node->keyword)) == 0) {
            break;
        } else if (cmp < 0) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    if (node == &nil || node == nullptr) {
        cout << "NoSuchWord\n";
        return;
    }
    TNode *removed = node;
    TNode *newnode = nullptr;
    if (node->left == &nil || node->right == &nil) {
        removed = node;
    } else {
        removed = Minimum(node->right);
    }
    if (removed->left != &nil) {
        newnode = removed->left;
    } else {
        newnode = removed->right;
    }
    if (removed->parent == &nil) {
        this->root = newnode;
    } else if (removed == removed->parent->left) {
        removed->parent->left = newnode;
    } else {
        removed->parent->right = newnode;
    }
    newnode->parent = removed->parent;
    if (removed != node) {
        node->number = removed->number;
        char *tmp_word = node->keyword;
        node->keyword = removed->keyword;
        removed->keyword = tmp_word;
    }
    if (removed->color == BLACK) {
        DeleteFix(newnode);
    }
    free(removed->keyword);
    free(removed);
    cout << "OK\n";
}
void TRBTree::Save(const char *path)
{
    ofstream file;
    file.open(path, ios::out | ios::binary);
    if (!file.is_open()) {
        cout << "ERROR: Couldn't create file\n";
        return;
    }
    Ser(this->root, file);
    file.close();
    cout << "OK\n";
}
void TRBTree::Load(const char *path)
{
    ifstream file;
    file.open(path, ios::in | ios::binary);
    if (!file.is_open()) {
        cout << "ERROR: Couldn't open file\n";
        return;
    }
    if (file.eof()) {
        file.close();
        return;
    }
    if (this->root != &nil) {
        Recoursedestroy(this->root);
    }
    this->root = Deser(&nil, file);
    file.close();
    cout << "OK\n";
}
TRBTree::~TRBTree()
{
    if (this->root != &nil) {
        Recoursedestroy(this->root);
    }
    this->root = nullptr;
}
