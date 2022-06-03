#include <iostream>
#include <list>
#include <string>
#include<clocale>

using namespace std;

class IObserver {
public:
    virtual ~IObserver() {};
    virtual void Update(const string& message_from_stream) = 0;
};

class IStream { //Subject
public:
    virtual ~IStream() {};
    virtual void Attach(IObserver* observer) = 0;
    virtual void Detach(IObserver* observer) = 0;
    virtual void Notify() = 0;
};


class Stream : public IStream {
private:
    list<IObserver*> list_observer_;
    string message_;

public:
    virtual ~Stream() {}

    void Attach(IObserver* observer) override {
        list_observer_.push_back(observer);
    }
    void Detach(IObserver* observer) override {
        list_observer_.remove(observer);
    }
    void Notify() override {
        list<IObserver*>::iterator iterator = list_observer_.begin();
        HowManyObserver();
        while (iterator != list_observer_.end()) {
            (*iterator)->Update(message_);
            ++iterator;
        }
    }

    void CreateMessage(string message = "Empty") {
        this->message_ = message;
        Notify();
    }
    void HowManyObserver() {
        cout << "There are " << list_observer_.size() << " observers in the list.\n";
    }
};

class Observer : public IObserver {
private:
    string message_from_stream_;
    Stream& stream_;
    static int static_number_;
    int number_;

public:
    Observer(Stream& stream) : stream_(stream) {
        this->stream_.Attach(this);
        cout << "A new Observer attached: Hi, I'm the Observer \"" << ++Observer::static_number_ << "\".\n";
        this->number_ = Observer::static_number_;
    }
    virtual ~Observer() {}

    void Update(const string& message_from_stream) override {
        message_from_stream_ = message_from_stream;
        PrintInfo();
    }
    void RemoveMeFromTheList() {
        stream_.Detach(this);
        cout << "Observer \"" << number_ << "\" removed from the list.\n";
    }
    void PrintInfo() {
        cout << "Observer \"" << this->number_ << "\": a new message is available --> " << this->message_from_stream_ << "\n";
    }
};

int Observer::static_number_ = 0;

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    Stream* stream = new Stream; //стрим
    Observer* observer1 = new Observer(*stream);
    Observer* observer2 = new Observer(*stream);
    Observer* observer3 = new Observer(*stream);
    Observer* observer4;
    Observer* observer5;
    cout << endl << endl;
    stream->CreateMessage("Сап, двач");
    observer3->RemoveMeFromTheList();
    cout << endl << endl;
    stream->CreateMessage("Я Елена Малышева, и я расскажу вам, почему жить - здорово");
    observer4 = new Observer(*stream);
    cout << endl << endl;
    observer2->RemoveMeFromTheList();
    observer5 = new Observer(*stream);
    cout << endl << endl;
    stream->CreateMessage("Хаю-хай, с вами Ивангай");
    observer5->RemoveMeFromTheList();
    observer4->RemoveMeFromTheList();
    observer1->RemoveMeFromTheList();

    delete observer5;
    delete observer4;
    delete observer3;
    delete observer2;
    delete observer1;
    delete stream;
    return 0;
}