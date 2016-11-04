#ifndef ITEM_H
#define ITEM_H

enum TColor { RED, BLACK };

class TItem {
private:
    TItem *left;
    TItem *right;
    TItem *parent;
    char *keyword;
    unsigned long long number;
    enum TColor color;
public:
    TItem(unsigned long long num, char *kwrd);
    TItem *Left();
    TItem *Right();
    TItem *Parent();
    TItem *Grandpa();
    TItem *Uncle();
    void SetLeft(TItem *it);
    void SetRight(TItem *it);
    void SetParent(TItem *it);
    void SetColor(TColor color);
    unsigned long long Number();
    char *Keyword();
    TColor Color();
    TItem *Searchrec(char *keyword);
    virtual ~TItem();
    void Deleterec();
};

#endif
