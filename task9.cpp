#include <iostream>
#include <string>

using namespace std;

class Vehicle {
protected:
    string* brand;
    int* year;
    double* engineVolume;
    bool* isRunning;

public:
    Vehicle(string b = "Неизвестно", int y = 2000, double v = 1.5, bool r = false) {
        cout << "[Vehicle Constructor]" << endl;
        brand = new string(b);
        year = new int(y);
        engineVolume = new double(v);
        isRunning = new bool(r);
    }

    Vehicle(const Vehicle&) = delete;
    Vehicle& operator=(const Vehicle&) = delete;

    virtual ~Vehicle() {
        cout << "[Vehicle Destructor]" << endl;
        delete brand;
        delete year;
        delete engineVolume;
        delete isRunning;
    }

    void setBrand(string b) { *brand = b; }
    void setYear(int y) { *year = y; }
    void setEngineVolume(double v) { *engineVolume = v; }
    void setIsRunning(bool r) { *isRunning = r; }

    string getBrand() { return *brand; }
    int getYear() { return *year; }
    double getEngineVolume() { return *engineVolume; }
    bool getIsRunning() { return *isRunning; }

    virtual void toggleEngine() = 0;
    virtual void info() = 0;
};

class Car : public Vehicle {
protected:
    int* doorsCount;

public:
    Car(string b = "Неизвестно", int y = 2000, double v = 1.5, bool r = false, int d = 4)
        : Vehicle(b, y, v, r) {
        cout << "[Car Constructor]" << endl;
        doorsCount = new int(d);
    }

    Car(const Car&) = delete;
    Car& operator=(const Car&) = delete;

    ~Car() override {
        cout << "[Car Destructor]" << endl;
        delete doorsCount;
    }

    void setDoorsCount(int d) { *doorsCount = d; }
    int getDoorsCount() { return *doorsCount; }

    void toggleEngine() override {
        *isRunning = !*isRunning;
        cout << "Двигатель автомобиля " << *brand << (*isRunning ? " заведён." : " заглушен.") << endl;
    }

    void info() override {
        cout << "Автомобиль " << *brand << ", год: " << *year
            << ", объём: " << *engineVolume << " л"
            << ", дверей: " << *doorsCount
            << ", заведён: " << (*isRunning ? "да" : "нет") << endl;
    }
};

class Truck : public Vehicle {
protected:
    double* payload;

public:
    Truck(string b = "Неизвестно", int y = 2000, double v = 1.5, bool r = false, double p = 5.0)
        : Vehicle(b, y, v, r) {
        cout << "[Truck Constructor]" << endl;
        payload = new double(p);
    }

    Truck(const Truck&) = delete;
    Truck& operator=(const Truck&) = delete;

    ~Truck() override {
        cout << "[Truck Destructor]" << endl;
        delete payload;
    }

    void setPayload(double p) { *payload = p; }
    double getPayload() { return *payload; }

    void toggleEngine() override {
        *isRunning = !*isRunning;
        cout << "Двигатель грузовика " << *brand << (*isRunning ? " заведён." : " заглушен.") << endl;
    }

    void info() override {
        cout << "Грузовик " << *brand << ", год: " << *year
            << ", объём: " << *engineVolume << " л"
            << ", грузоподъёмность: " << *payload << " т"
            << ", заведён: " << (*isRunning ? "да" : "нет") << endl;
    }
};

class ElectricCar : public Car {
protected:
    double* batteryCapacity;

public:
    ElectricCar(string b = "Неизвестно", int y = 2000, double v = 1.5,
        bool r = false, int d = 4, double c = 60.0)
        : Car(b, y, v, r, d) {
        cout << "[ElectricCar Constructor]" << endl;
        batteryCapacity = new double(c);
    }

    ElectricCar(const ElectricCar&) = delete;
    ElectricCar& operator=(const ElectricCar&) = delete;

    ~ElectricCar() override {
        cout << "[ElectricCar Destructor]" << endl;
        delete batteryCapacity;
    }

    void setBatteryCapacity(double c) { *batteryCapacity = c; }
    double getBatteryCapacity() { return *batteryCapacity; }

    void toggleEngine() override {
        *isRunning = !*isRunning;
        cout << "Электродвигатель " << *brand << (*isRunning ? " заведён." : " заглушен.") << endl;
    }

    void info() override {
        cout << "Электромобиль " << *brand << ", год: " << *year
            << ", дверей: " << *doorsCount
            << ", батарея: " << *batteryCapacity << " кВт·ч"
            << ", заведён: " << (*isRunning ? "да" : "нет") << endl;
    }
};

// Новый класс: автопарк, поле типа родительского класса Vehicle*
class Fleet {
private:
    string* fleetName;
    Vehicle* mainVehicle;

public:
    Fleet(const Fleet&) = delete;
    Fleet& operator=(const Fleet&) = delete;

    Fleet() {
        cout << "[Fleet Constructor]" << endl;
        mainVehicle = new Car();
        fleetName = new string("Без названия");
    }

    Fleet(string name, int type) {
        cout << "[Fleet Constructor]" << endl;
        if (type == 2)
            mainVehicle = new Car("Kia", 2021, 1.6, false, 4);
        else if (type == 3)
            mainVehicle = new Truck("MAN", 2019, 15.0, false, 30.0);
        else
            mainVehicle = new ElectricCar("Nissan Leaf", 2022, 0.0, false, 5, 40.0);
        fleetName = new string(name);
    }

    ~Fleet() {
        cout << "[Fleet Destructor]" << endl;
        delete mainVehicle;
        delete fleetName;
    }

    string getFleetName() { return *fleetName; }

    void showMainVehicle() {
        cout << "Главное ТС автопарка: ";
        mainVehicle->info();
    }

    void toggleMainVehicleEngine() {
        mainVehicle->toggleEngine();
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Car* c = new Car("BMW", 2022, 3.0, false, 5);
    c->info();
    c->toggleEngine();
    delete c;

    Truck* t = new Truck("Volvo", 2018, 12.0, false, 25.0);
    t->info();
    t->toggleEngine();
    delete t;

    ElectricCar* e = new ElectricCar("Tesla", 2023, 0.0, false, 4, 120.0);
    e->info();
    e->toggleEngine();
    delete e;

    Vehicle* fleet[3];
    fleet[0] = new Car("Kia", 2021, 1.6, false, 4);
    fleet[1] = new Truck("MAN", 2019, 15.0, false, 30.0);
    fleet[2] = new ElectricCar("Nissan Leaf", 2022, 0.0, false, 5, 40.0);

    for (int i = 0; i < 3; i++) {
        fleet[i]->info();
        fleet[i]->toggleEngine();
    }

    for (int i = 0; i < 3; i++) {
        delete fleet[i];
    }

    int choice;
    cout << "Выберите тип транспортного средства (2-Car, 3-Truck, 4-ElectricCar): ";
    cin >> choice;

    Vehicle* userObj = nullptr;

    if (choice == 2) {
        userObj = new Car("UserCar", 2022, 3.0, false, 5);
    }
    else if (choice == 3) {
        userObj = new Truck("UserTruck", 2018, 12.0, false, 25.0);
    }
    else if (choice == 4) {
        userObj = new ElectricCar("UserElectric", 2023, 0.0, false, 4, 120.0);
    }
    else {
        cout << "Неверный выбор. Создан Car по умолчанию." << endl;
        userObj = new Car();
    }

    userObj->info();
    userObj->toggleEngine();

    delete userObj;

    Car staticCar("StaticCar", 2020, 2.5, false, 4);
    Truck staticTruck("StaticTruck", 2015, 10.0, false, 20.0);
    ElectricCar staticElectric("StaticElectric", 2024, 0.0, false, 4, 100.0);

    staticCar.info();
    staticCar.toggleEngine();

    staticTruck.info();
    staticTruck.toggleEngine();

    staticElectric.info();
    staticElectric.toggleEngine();

    cout << endl;
    cout << "=== Демонстрация класса Fleet ===" << endl;

    Fleet fleet1;
    cout << "Название: " << fleet1.getFleetName() << endl;
    fleet1.showMainVehicle();
    fleet1.toggleMainVehicleEngine();

    cout << endl;

    Fleet fleet2("Городской парк", 3);
    cout << "Название: " << fleet2.getFleetName() << endl;
    fleet2.showMainVehicle();
    fleet2.toggleMainVehicleEngine();

    cout << endl;
    cout << "Выход из main — деструкторы:" << endl;
    return 0;
}
