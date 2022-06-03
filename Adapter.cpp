#include <iostream>
#include<string>

using namespace std;

class Target {
public:
    virtual string Request() = 0;
    virtual ~Target() {};
};

class Adaptee {
public:
    string SpecificRequest() const {
        return "Lw lv wkh Zxhvdu zlskhu";
    }
};

class Adapter : public Target {
private:
    Adaptee* adaptee_;
public:
    Adapter(Adaptee* adaptee) : adaptee_(adaptee) {}
    string Request() override {
        string decoded = this->adaptee_->SpecificRequest();
        for (int i = 0; i < decoded.size(); i++) {
            if (decoded[i] == ' ')
                continue;
            else if (decoded[i] == 'x')
                decoded[i] = 'a';
            else if (decoded[i] == 'X')
                decoded[i] = 'A';
            else if (decoded[i] == 'Y')
                decoded[i] = 'B';
            else if (decoded[i] == 'y')
                decoded[i] = 'b';
            else if (decoded[i] == 'z')
                decoded[i] = 'c';
            else if (decoded[i] == 'Z')
                decoded[i] = 'C';
            else
                decoded[i] -= 3;
        }
        return "Adapter: " + decoded;
    }
};


void ClientCode(Target* target) {
    cout << target->Request();
}

int main() {
    Adaptee* adaptee = new Adaptee;
    cout << "Bandit: I can't open the door, it's encrypted!" << endl;
    cout << "Adaptee: " << adaptee->SpecificRequest();
    cout << endl << endl;
    
    cout << "Admin: But you can work with it via the Adapter" << endl;
    Adapter* adapter = new Adapter(adaptee);
    ClientCode(adapter);
    cout << endl << endl;
    cout << "Bandit: Thanks, I won't kill you...now" << endl;
    delete adaptee;
    delete adapter;

    return 0;
}