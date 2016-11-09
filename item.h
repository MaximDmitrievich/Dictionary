#ifndef ITEM_H
#define ITEM_H

enum TColor { BLACK, RED };

class TItem {
private:
    TItem *left;
    TItem *right;
    TItem *parent;
    char *keyword;
    unsigned long long number;
    enum TColor color;
public:
    TItem(TItem *parent);
    TItem(unsigned long long num, char *kwrd);
    bool IsNIL(TItem *it);
    TItem *Left();
    TItem *Right();
    TItem *Parent();
    TItem *Grandpa();
    void SetLeft(TItem *it);
    void SetRight(TItem *it);
    void SetParent(TItem *it);
    void SetColor(TColor color);
    unsigned long long Number();
    char *Keyword();
    void FromItemToItem(TItem *right);
    TColor Color();
    TItem *Searchrec(char *keyword);
    virtual ~TItem();
    void Deleterec();
};


#endif
