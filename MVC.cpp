#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <regex> 
#include <fstream>

using namespace std;

class Observer
{
public:
    virtual void update() = 0;
};

class Observable
{
public:
    void addObserver(Observer* observer)
    {
        _observers.push_back(observer);
    }
    void notifyUpdate()
    {
        for (auto& observer : _observers)
            observer->update();
    }
private:
    std::vector<Observer*> _observers;
};
//2
class TemperatureModel : public Observable
{
public:
    float getF()
    {
        return _temperatureF;
    }

    float getC()
    {
        return (_temperatureF - 32.0) * 5.0 / 9.0;
    }

    string getCity()
    {
        return _city;
    }

    void getForecast()
    {
        setC(-50 + (rand() % (50 - (-50) + 1)));
    }

    void setF(float tempF)
    {
        _temperatureF = tempF;
    }

    void setC(float tempC)
    {
        _temperatureF = tempC * 9.0 / 5.0 + 32.0;
    }

    void setCity(string city)
    {
        this->_city = city;
        getForecast();
        notifyUpdate();
    }

private:
    float _temperatureF;
    string _city = "";
};


//View
//«подписывает» себя на изменения модели вызовом метода addObserver
class ConsoleView : public Observer
{
public:
    ConsoleView(TemperatureModel* model)
    {
        _model = model;
        _model->addObserver(this);
    }
    virtual void update()
    {
        cout << "Temperature in the city: ";
        printf("%s %dF %dC",
            _model->getCity().c_str(),
            (int)_model->getF(),
            (int)_model->getC()
        );
        cout << "\n\n";
        cout << "Input other city (MSK, SPB, KZN): ";
    }
private:
    TemperatureModel* _model;
};


//Класс Controller, так же как и ConsoleView, 
//получает ссылку на модель в конструкторе. 
//Метод start() сбрасывает модель в первоначальное состояние 
class Controller
{
public:
    Controller(TemperatureModel* model)
    {
        _model = model;
    }
    void start()
    {
        _model->setCity("MSK");
        string city;
        do
        {
            cin >> city;
            _model->setCity(city);
        } while (city == "MSK" || city == "SPB" || city == "KZN");
    }
private:
    TemperatureModel* _model;
};


int main()
{
    TemperatureModel model;
    ConsoleView view(&model);
    Controller controller(&model);
    controller.start();
    return 0;
}
