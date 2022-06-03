#include <iostream>
#include <string>

using namespace std;

class Colleague;
class Mediator { //lead
public:
    virtual void Notify(Colleague* sender, string event) = 0;
};


class Colleague { 
protected:
    Mediator* mediator_;

public:
    Colleague(Mediator* mediator = NULL) : mediator_(mediator) {
    }
    void set_mediator(Mediator* mediator) {
        this->mediator_ = mediator;
    }
};

class FrontDev : public Colleague {
public:
    void DoNFFront() {
        cout << "Front dev made feature.\n";
        this->mediator_->Notify(this, "nf");
    }
    void DoOFFront() {
        cout << "Front dev finalized feature.\n";
        this->mediator_->Notify(this, "of");
    }
};

class BackDev : public Colleague {
public:
    void DoNFBack() {
        cout << "Back dev made feature.\n";
        this->mediator_->Notify(this, "nf");
    }
    void DoOFBack() {
        cout << "Back dev finalized feature.\n";
        this->mediator_->Notify(this, "of");
    }
};

class Tester : public Colleague {
public:
    void DoBugsBack() {
        cout << "Tester found bugs in backend.\n";
        this->mediator_->Notify(this, "bb");
    }
    void DoBugsFront() {
        cout << "Tester found bugs in frontend.\n";
        this->mediator_->Notify(this, "bf");
    }
};

class Designer : public Colleague {
public:
    void DoSmth1() {
        cout << "Designer made a scheme.\n";
        this->mediator_->Notify(this, "s");
    }
    void DoSmth2() {
        cout << "Designer painted the most red colour of button.\n";
        this->mediator_->Notify(this, "b");
    }
};

class Analytics : public Colleague {
public:
    void DoSmth1() {
        cout << "Analytics does something...\n";
        this->mediator_->Notify(this, "smth1");
    }
    void DoSmth2() {
        cout << "Analytics does something again...\n";
        this->mediator_->Notify(this, "smth2");
    }
};

class ConcreteMediator : public Mediator {
private:
    FrontDev* frontDev_;
    BackDev* backDev_;
    Tester* tester_;
    Designer* designer_;
    Analytics* analytics_;

public:
    ConcreteMediator(Tester* t, Designer* d, BackDev* b, FrontDev* f, Analytics* a) 
                    : tester_(t), designer_(d), backDev_(b), frontDev_(f), analytics_(a) {
        this->backDev_->set_mediator(this);
        this->frontDev_->set_mediator(this);
        this->tester_->set_mediator(this);
        this->designer_->set_mediator(this);
        this->analytics_->set_mediator(this);
    }
    void Notify(Colleague* sender, string event) override {
        if (event == "bf") {
            cout << "Mediator(Lead) reacts on bugs in front and triggers on front dev:\n";
            cout << "Front dev: OMG, again... \n";
            this->frontDev_->DoOFFront();
        }
        if (event == "b") {
            cout << "Mediator(Lead) reacts on new feature in design and triggers on front dev:\n";
            cout << "Front dev: OMG... \n";
            this->frontDev_->DoNFFront();
        }
    }
};

int main() {
    Tester* t = new Tester;
    Designer* d = new Designer;
    BackDev* b = new BackDev;
    FrontDev* f = new FrontDev;
    Analytics* a = new Analytics;

    ConcreteMediator* lead = new ConcreteMediator(t, d, b, f, a);
    cout << "Client: I wanna this button to be red, not blue" << endl;
    cout << "Lead: OK, we'll do this. Designer, come here." << endl;
    d->DoSmth2();
    cout << "\nClient: now smth is wrong with my application, it doesn't work correctly. Can you find and fix bugs?" << endl;
    cout << "Tester: my time has come..." << endl;
    t->DoBugsFront();
    cout << endl;

    delete t;
    delete d;
    delete b;
    delete f;
    delete a;
    delete lead;
    return 0;
}
