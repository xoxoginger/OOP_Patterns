#include<iostream>
#include<string>
#include <algorithm>
#include<vector>

using namespace std;


class Strategy
{
public:
    virtual ~Strategy() {}
    virtual string move()  = 0;
};

class Transport //контекст
{
private:
    Strategy* strategy_;
public:
    Transport(Strategy* strategy = nullptr) : strategy_(strategy)
    {
    }
    ~Transport()
    {
        delete this->strategy_;
    }
    
    void set_strategy(Strategy* strategy)
    {
        delete this->strategy_;
        this->strategy_ = strategy;
    }
    
    void action() 
    {
        cout << "Transport: Performing actions using the strategy\n";
        string result = this->strategy_->move();
        cout << result << "\n";
    }
};

class Taxi : public Strategy
{
public:
    string move()  override
    {
        return "Client: Moving by taxi...So expensive...";
    }
};
class Bus : public Strategy
{
    string move()  override
    {
        return "Client: Moving by bus...So long...";;
    }
};

int main()
{
    Transport* t = new Transport(new Taxi);
    cout << "Client: I have only 1.5 hours! Strategy is set to go by taxi.\n";
    t->action();
    cout << "\n";
    cout << "Client: Taxi is too expensive for me - high demand. Strategy is set to go by bus.\n";
    t->set_strategy(new Bus);
    t->action();
    delete t;
    return 0;
}


