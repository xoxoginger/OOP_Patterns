#include <iostream>
#include<string>

using namespace std;

class Cupboard
{
protected:
    Cupboard(const std::string value) : value_(value){}

    static Cupboard* c;

    string value_;

public:

    //Одиночки не должны быть клонируемыми
    Cupboard(Cupboard& other) = delete;
    //Одиночкам не должны присваиваться значения
    void operator=(const Cupboard&) = delete;

    static Cupboard* GetInstance(const std::string& value);

    string value() const {
        return value_;
    }
};

Cupboard* Cupboard::c = nullptr;

//статик методы вне класса
Cupboard* Cupboard::GetInstance(const std::string& value)
{
    if (c == nullptr) {
        c = new Cupboard(value);
    }
    return c;
}

class Person
{

public:
    Person() {}
    Cupboard* c;
    void Launch(string cName)
    {
        c = Cupboard::GetInstance(cName);
        std::cout << c->value() << "\n";
    }

};
int main()
{
    Person p = Person();
    p.Launch("Raspberry");
    // у нас не получится изменить шкаф, так как объект уже создан  
    p.c = Cupboard::GetInstance("Cranberry");
    cout << p.c->value() << endl;
     
    
}


