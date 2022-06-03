#include<iostream>
#include<string>

using namespace std;
/**
 * ���������� ������������� ��������� ��� ���� ������� ����������. �� �� ������
 * ��������������� ���������� ����������. �� �������� ��� ���������� ����� ����
 * ���������� �������. ��� �������, ��������� ���������� ������������� ������
 * ����������� ��������, � �� ����� ��� ���������� ���������� �������� �����
 * �������� ������, ���������� �� ���� ����������.
 */

class Device {
public:
    virtual ~Device() {}
    virtual string TurnOnOff(bool OnOff) = 0;
    bool OnOff = false;
};

/**
 * ������ ���������� ���������� ������������� ����������� ��������� � ���������
 * ��������� ���������� � �������������� API ���� ���������.
 */
class switchCeilingLight : public Device {
public:
    string TurnOnOff(bool OnOff) override {
        if (OnOff)
            return "switchCeilingLight: The light is off.\n";
        else 
            return "switchCeilingLight: The light is on.\n";
    }
};
class switchDesktopLight : public Device {
public:
    string TurnOnOff(bool OnOff) override {
        if (OnOff)
            return "switchDesktopLight: The light is off.\n";
        else
            return "switchDesktopLight: The light is on.\n";
    }
};

/**
 * ���������� ������������� ��������� ��� ������������ ����� ���� ��������
 * �������. ��� �������� ������ �� ������ �� �������� ���������� � ����������
 * ��� ��� ��������� ������.
 */

class Switch {
    /**
     * @var Device
     */
protected:
    Device* device_;
    
public:
    Switch(Device* device) : device_(device) {
    }

    virtual ~Switch() {
    }

    virtual string Operation(bool OnOff) const {
        return "Switch: Base operation with:\n" +
            this->device_->TurnOnOff(OnOff);
    }
};
/**
 * ����� ��������� ���������� ��� ��������� ������� ����������.
 */
class ExtendedSwitch : public Switch {
public:
    ExtendedSwitch(Device* device) : Switch(device) {
    }
    string Operation(bool OnOff) const override {
        return "ExtendedSwitch: Extended operation with:\n" +
            this->device_->TurnOnOff(OnOff);
    }
};

/**
 * �� ����������� ����� �������������, ����� ������ ���������� ����������� �
 * ����������� �������� ����������, ���������� ��� ������ �������� ������ ��
 * ������ ����������. ����� �������, ���������� ��� ����� ������������ �����
 * ���������� ���������� � ����������.
 */
void ClientCode(const Switch& switchOnOff, bool OnOff) {
    // ...
    cout << switchOnOff.Operation(OnOff);
    // ...
}
/**
 * ���������� ��� ������ �������� � ����� �������������� ������������������
 * ����������� ���������� � ����������.
 */

int main() {
    bool OnOff = false; //Off
    string ans;
    cout << "It's 8:00 pm. You came home. Light is off. Do you wanna turn on Ceiling Light? y/n" << endl;
    cin >> ans;
    if (ans == "n")
        OnOff = true;
    Device* device = new switchCeilingLight;
    Switch* switchOnOff = new Switch(device);
    ClientCode(*switchOnOff, OnOff);
    cout << endl;
    delete device;
    delete switchOnOff;
    OnOff = false;
    cout << "Your laptop is on. Are you working now? Light is off. Do you wanna turn on Desktop Light? y/n" << endl;
    cin >> ans;
    if (ans == "n")
        OnOff = true;
    device = new switchDesktopLight;
    switchOnOff = new ExtendedSwitch(device);
    ClientCode(*switchOnOff, OnOff);

    delete device;
    delete switchOnOff;

    return 0;
}