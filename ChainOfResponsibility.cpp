#include <iostream>
#include<vector>

using namespace std;

class Handler {
public:
    virtual Handler* SetNext(Handler* handler) = 0;
    virtual string Handle(string request) = 0;
};
/**
 * Поведение цепочки по умолчанию может быть реализовано внутри базового класса
 * обработчика.
 */
class AbstractHandler : public Handler {
private:
    Handler* next_handler_;

public:
    AbstractHandler() : next_handler_(NULL) {
    }
    Handler* SetNext(Handler* handler) override {
        this->next_handler_ = handler;
        return handler;
    }
    string Handle(string request) override {
        if (this->next_handler_) {
            return this->next_handler_->Handle(request);
        }

        return {};
    }
};


class JuliHandler : public AbstractHandler {
public:
    string Handle(string request) override {
        if (request == "Math") {
            return "Juli: I'll take the " + request + ".\n\n";
        }
        else {
            cout << "Juli: No, this is not my task." << endl;
            return AbstractHandler::Handle(request);
        }
    }
};
class OlegHandler : public AbstractHandler {
public:
    string Handle(string request) override {
        if (request == "Graphs") {
            return "Oleg: I'll take the " + request + ".\n\n";
        }
        else {
            cout << "Oleg: No, this is not my task." << endl;
            return AbstractHandler::Handle(request);
        }
    }
};
class AlexHandler : public AbstractHandler {
public:
    string Handle(string request) override {
        if (request == "Greedy") {
            return "Alex: I'll take the " + request + ".\n\n";
        }
        else {
            cout << "Alex: No, this is not my task." << endl;
            return AbstractHandler::Handle(request);
        }
    }
};


void ClientCode(Handler& handler) {
    vector<string> tasks = { "Greedy", "Фывафывапролпрол", "Graphs", "Math"};
    for (string& t : tasks) {
        cout << "Who'll take the " << t << " one?\n";
        string result = handler.Handle(t);
        if (!result.empty()) {
            cout << "  " << result;
        }
        else {
            cout << "  " << t << " was left unsolved.\n\n";
        }
    }
}

int main() {
    JuliHandler* Juli = new JuliHandler;
    OlegHandler* Oleg = new OlegHandler;
    AlexHandler* Alex = new AlexHandler;
    Juli->SetNext(Oleg)->SetNext(Alex);

    //можно отправлять запрос любому обработчику в цепочке, не только первому
    cout << "Chain: Juli -> Oleg  -> Alex\n\n";
    ClientCode(*Juli);
    cout << "\n";
    cout << "Another chain: Oleg -> Alex\n\n";
    ClientCode(*Oleg);

    delete Juli;
    delete Oleg;
    delete Alex;

    return 0;
}