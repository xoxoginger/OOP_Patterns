#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Light
{
public:
    void CeilingOn() {
        cout << "Ceiling light is on " << endl;
    }
    void CeilingOff() {
        cout << "Ceiling light is off " << endl;
    }
    void DesktopOn() {
        cout << "Desktop light is on " << endl;
    }
    void DesktopOff() {
        cout << "Desktop light is off " << endl;
    }
};

// Базовый класс
class Command
{
public:
    virtual ~Command() {}
    virtual void execute() = 0;
protected:
    Command(Light* l) : light(l) {}
    Light* light;
};

class CeilingLightOnCommand : public Command
{
public:
    CeilingLightOnCommand(Light* l) : Command(l) {}
    void execute() override {
        light->CeilingOn();
    }
};

class CeilingLightOffCommand : public Command
{
public:
    CeilingLightOffCommand(Light* l) : Command(l) {}
    void execute() override {
        light->CeilingOff();
    }
};

class DesktopLightOnCommand : public Command
{
public:
    DesktopLightOnCommand(Light* l) : Command(l) {}
    void execute() override {
        light->DesktopOn();
    }
};

class DesktopLightOffCommand : public Command
{
public:
    DesktopLightOffCommand(Light* l) : Command(l) {}
    void execute() override {
        light->DesktopOff();
    }
};

class Remote {
private:
    Command* on_start_;

    Command* on_finish_;
public:
    ~Remote() {
        delete on_start_;
        delete on_finish_;
    }

    void SetOnStart(Command* command) {
        this->on_start_ = command;
    }
    void SetOnFinish(Command* command) {
        this->on_finish_ = command;
    }
    
     //Отправитель не зависит от классов конкретных команд и получателей.
     //Отправитель передаёт запрос получателю косвенно, выполняя команду.
    
    void DoSomethingImportant() {
        cout << "Remote: Does anybody want to turn on the light before other tasks?\n";
        if (this->on_start_) {
            this->on_start_->execute();
        }
        cout << "Remote: ...doing something really important...\n";
        cout << "Remote: Does anybody want to turn off the light after I finish?\n";
        if (this->on_finish_) {
            this->on_finish_->execute();
        }
    }
};

int main()
{
    
    Remote* remote = new Remote; //Invoker
    Light* l = new Light; //Receiver
    string choose;

    cout << "You're at home. Would you like to turn on ceiling/desktop light?" << endl;
    cout << "Press c for ceiling, d for desktop or n if you don't wanna light" << endl;
    cin >> choose;
    if (choose == "c")
    {
        remote->SetOnStart(new CeilingLightOnCommand(l));
        remote->SetOnFinish(new CeilingLightOffCommand(l));
    }
    else if (choose == "d")
    {
        remote->SetOnStart(new DesktopLightOnCommand(l));
        remote->SetOnFinish(new DesktopLightOffCommand(l));
    }

    remote->DoSomethingImportant();

    return 0;
}