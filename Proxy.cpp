#include <iostream>

using namespace std;

class BoardOfDirectors { //Совет директоров
public:
    virtual void Request() = 0;
};

class Director : public BoardOfDirectors {
public:
    void Request() override {
        cout << "Director: I'll solve your problem.\n";
    }
};

class Proxy : public BoardOfDirectors {
private:
    Director* director_;

    bool CheckAccess() {
        cout << "Proxy: Checking access of my director.\n";
        string ans;
        cout << "Proxy: Are you busy, director? y/n\n";
        cin >> ans;
        if (ans == "y")
            return false;
        else
            return true;
    }

public:
    Proxy(Director* director) : director_(new Director(*director)) {
    }

    ~Proxy() {
        delete director_;
    }
    
    void Request() override {
        if (this->CheckAccess()) {
            this->director_->Request();
        }
        else
            cout << "Proxy: Tell me about your problem. May be I can help you myself." << endl;

    }
};


int main() {
    cout << "Client: Executing the client code with a real subject:\n";
    Director* director = new Director;
    director->Request();
    cout << "\n";
    cout << "Client: Executing the same client code with a proxy:\n";
    Proxy* proxy = new Proxy(director);
    proxy->Request();

    delete director;
    delete proxy;
    return 0;
}