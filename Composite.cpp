#include <iostream>
#include <vector>

using namespace std;

// Component 
class Item
{
public:
    virtual int getCost() = 0;
    virtual void addItem(Item* p) {}
    virtual ~Item() {}
};

// Primitives
class Rose : public Item
{
public:
    virtual int getCost() {
        return 200;
    }
};

class Lily : public Item
{
public:
    virtual int getCost() {
        return 300;
    }
};

class Orchid : public Item
{
public:
    virtual int getCost() {
        return 600;
    }
};

class Tulip : public Item
{
public:
    virtual int getCost() {
        return 200;
    }
};

class Peony : public Item
{
public:
    virtual int getCost() {
        return 200;
    }
};

class Eustoma : public Item
{
public:
    virtual int getCost() {
        return 70;
    }
};

class Eucalyptus : public Item
{
public:
    virtual int getCost() {
        return 100;
    }
};

class Gypsofila : public Item
{
public:
    virtual int getCost() {
        return 50;
    }
};

class Paper : public Item
{
public:
    virtual int getCost() {
        return 250;
    }
};

class Plastic : public Item
{
public:
    virtual int getCost() {
        return 100;
    }
};

// Composite
class CompositeItem : public Item
{
public:
    int getCost() {
        int total = 0;
        for (int i = 0; i < c.size(); ++i)
            total += c[i]->getCost();
        return total;
    }
    void addItem(Item* p) {
        c.push_back(p);
    }
    ~CompositeItem() {
        for (int i = 0; i < c.size(); ++i)
            delete c[i];
    }
private:
    std::vector<Item*> c;
};


// Вспомогательная функция для создания букета
CompositeItem* createBouquet(int num, string type, string add, string pack)
{
    CompositeItem* b = new CompositeItem;
    
    for (int i = 0; i < num; i++)
    {
        if (type == "rose")
            b->addItem(new Rose);
        else if (type == "lily")
            b->addItem(new Lily);
        else if (type == "orchid")
            b->addItem(new Orchid);
        else if (type == "tulip")
            b->addItem(new Tulip);
        else if (type == "peony")
            b->addItem(new Peony);
        else if (type == "gypsofila")
            b->addItem(new Gypsofila);
        else
            cout << "These flowers are not available." << endl;
    }
    if (add == "eustoma")
        b->addItem(new Eustoma);
    else if(add == "eucalyptus")
        b->addItem(new Eucalyptus);
    else if(add == "gypsofila")
        b->addItem(new Gypsofila);

    if (pack == "paper")
        b->addItem(new Paper);
    else if (pack == "plastic")
        b->addItem(new Plastic);

    return b;
}

int main()
{
    CompositeItem* order = new CompositeItem;
    int numBouquet;
    cout << "Hello! How many bouquets you want to order? ";
    cin >> numBouquet;
    for (int i = 0; i < numBouquet; i++) 
    {
        int num;
        string type;
        string add;
        string pack;
        cout << "Which flowers do you want in your " << (i + 1)
             << " bouquet? We have rose, lily, orchid, tulip, peony, gypsofila" << endl;
        cin >> type;
        cout << "How much flowers do you want in this bouquet?" << endl;
        cin >> num;
        cout << "Do you want to add something? We have eustoma, eucalyptus and gypsofila " << endl;
        cin >> add;
        cout << "And the last one. Do you want to pack this bouquet? We have paper and plactic packaging " << endl;
        cin >> pack;
        order->addItem(createBouquet(num, type, add, pack));
    }
    cout << "Your order costs " << order->getCost() << endl;
    delete order;
    return 0;
}
