#include <iostream>
#include <windows.h>

using namespace std;

//state class 
class LightState
{
public:
    virtual void Handle() = 0;
};

class RedLight : public LightState
{
public:
    static RedLight* GetInstance()
    {
        static RedLight redL;
        return &redL;
    }
    virtual void Handle()
    {
        cout << "Red is glowing for 1 sec" << endl;
    }


};

class YellowLight :public LightState
{
public:
    static YellowLight* GetInstance()
    {
        static YellowLight yellowL;
        return &yellowL;
    }

    void Handle()
    {
        cout << "Yellow is glowing for 1 sec" << endl;
    }
};

class GreenLight : public LightState
{
public:
    static GreenLight* GetInstance()
    {
        static GreenLight greenL;
        return &greenL;
    }


    void Handle()
    {
        cout << "Green is glowing for 1 sec" << endl;
    }

};

class Controller //светофор
{
    LightState* lState;
public:
    Controller()
    {
        lState = nullptr;
    }
    void run()
    {
        int i = 0;
        int l = 1;
        int j = 0;
        while (i < 3)
        {

            lState = RedLight::GetInstance();
            lState->Handle();
            Sleep(1000);
            system("CLS");
            for (j; j < l; j++)
            {
                cout << endl;
            }
            l++;
            j = 0;
            lState = YellowLight::GetInstance();
            lState->Handle();
            Sleep(1000);
            system("CLS");
            for (j; j < l; j++)
            {
                cout << endl;
            }
            l++;
            j = 0;
            lState = GreenLight::GetInstance();
            lState->Handle();
            Sleep(1000);
            system("CLS");
            for (j; j < l; j++)
            {
                cout << endl;
            }
            l++;
            j = 0;
            i++;
            
        }
        cout << "Party is over..." << endl;

    }

};


int main()
{
    cout << "Disco dance!" << endl;
    Sleep(2000);
    system("CLS");
    Controller c;
    c.run();
    return 0;
}

