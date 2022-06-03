#include <iostream>
#include<string>
#include<vector>

using namespace std;

class Pizza {
public:
    std::vector<std::string> parts_;
    void ListParts() {
        std::cout << "Pizza parts: ";
        for (size_t i = 0; i < parts_.size(); i++) {
            if (parts_[i] == parts_.back()) {
                std::cout << parts_[i];
            }
            else {
                std::cout << parts_[i] << ", ";
            }
        }
        std::cout << "\n\n";
    }
};


class Builder {
public:
    virtual ~Builder() {}
    virtual void Cheese() = 0;
    virtual void Sauce() = 0;
    virtual void Meat() = 0;
    virtual void Peperoni() = 0;
    virtual void Pineapple() = 0;
    virtual void Ham() = 0;
    virtual void Pepper() = 0;
    virtual void Onion() = 0;
};

class PizzaBuilder : public Builder {
private:

    Pizza* product; //создаем пустую пиццу

public:

    PizzaBuilder() {
        this->Reset();
    }

    ~PizzaBuilder() {
        delete product;
    }

    void Reset() {
        this->product = new Pizza();
    }

    void Cheese()override {
        this->product->parts_.push_back("Cheese");
    }

    void Sauce()override {
        this->product->parts_.push_back("Sauce");
    }

    void Meat()override {
        this->product->parts_.push_back("Meat");
    }

    void Peperoni()override {
        this->product->parts_.push_back("Peperoni");
    }

    void Pineapple()override {
        this->product->parts_.push_back("Pineapple");
    }

    void Ham()override {
        this->product->parts_.push_back("Ham");
    }

    void Pepper()override {
        this->product->parts_.push_back("Pepper");
    }

    void Onion()override {
        this->product->parts_.push_back("Onion");
    }

    Pizza* GetProduct() {
        Pizza* result = this->product;
        this->Reset();
        return result;
    }
};


class Director {
private:
    Builder* builder;
   

public:

    void set_builder(Builder* builder) {
        this->builder = builder;
    }

    void StandartPizza() {
        this->builder->Cheese();
        this->builder->Sauce();
    }

    void FullPizza() {
        this->builder->Cheese();
        this->builder->Sauce();
        this->builder->Meat();
        this->builder->Peperoni();
        this->builder->Pineapple();
        this->builder->Ham();
        this->builder->Pepper();
        this->builder->Onion();
    }

    void MeatPizza() {
        this->builder->Cheese();
        this->builder->Sauce();
        this->builder->Meat();
        this->builder->Peperoni();
        this->builder->Ham();
    }
};
 
void ClientCode(Director& director)
{
    PizzaBuilder* builder = new PizzaBuilder();
    director.set_builder(builder);
    std::cout << "Standard basic product:\n";
    director.StandartPizza();

    Pizza* p = builder->GetProduct();
    p->ListParts();
    delete p;

    std::cout << "Standard full featured product:\n";
    director.FullPizza();

    p = builder->GetProduct();
    p->ListParts();
    delete p;

    std::cout << "Custom product:\n";
    builder->Ham();
    builder->Pineapple();
    p = builder->GetProduct();
    p->ListParts();
    delete p;

    delete builder;
}

int main() {
    Director* director = new Director();
    ClientCode(*director);
    delete director;
    return 0;
}

