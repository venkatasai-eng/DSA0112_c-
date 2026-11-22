#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;
class Vehicle {
    string reg;
    bool rented = false;
protected:
    double daily;
public:
    Vehicle(string r, double d) : reg(r), daily(d) {}
    virtual ~Vehicle() = default;
    const string& registration() const { return reg; }
    bool available() const { return !rented; }
    bool rent() { if (rented) return false; rented = true; return true; }
    bool returnVehicle() { if (!rented) return false; rented = false; return true; }
    virtual double charge(int days, double usage) const = 0;
    virtual string kind() const = 0;
};
class Bicycle : public Vehicle {
public:
    Bicycle(string r, double d) : Vehicle(r,d) {}
    double charge(int days, double) const override { return days * daily; }
    string kind() const override { return "Bicycle"; }
};
class MotorVehicle : public Vehicle {
protected:
    double fuelLevel;
    string serviceDue;
public:
    MotorVehicle(string r,double d,double f,string sd)
      : Vehicle(r,d),fuelLevel(f),serviceDue(sd) {}
};
class TwoWheeler : public MotorVehicle {
public:
    TwoWheeler(string r,double d,double f,string sd)
      : MotorVehicle(r,d,f,sd) {}
    double charge(int days,double litres) const override {
        return days*daily + litres*105;
    }
    string kind() const override { return "TwoWheeler"; }
};
class Car : public MotorVehicle {
protected: int seats;
public:
    Car(string r,double d,double f,string sd,int s)
      : MotorVehicle(r,d,f,sd), seats(s) {}
    double charge(int days,double litres) const override {
        return days*daily + litres*105;
    }
    string kind() const override { return "Car"; }
};
class ElectricCar : public Car {
    double batteryKWh;
public:
    ElectricCar(string r,double d,string sd,int s,double kWh)
      : Car(r,d,100,sd,s), batteryKWh(kWh) {}
    double charge(int days,double kWhUsed) const override {
        if (kWhUsed > batteryKWh) throw invalid_argument("Usage exceeds battery");
        return days*daily + kWhUsed*8;
    }
    string kind() const override { return "ElectricCar"; }
};
class ElectricBus : public MotorVehicle {
    int capacity;
public:
    ElectricBus(string r,double d,string sd,int c)
      : MotorVehicle(r,d,100,sd), capacity(c) {}
    double charge(int days,double kWhUsed) const override {
        return days*daily + kWhUsed*9;
    }
    string kind() const override { return "ElectricBus"; }
};
int main() {
    vector<unique_ptr<Vehicle>> fleet;
    fleet.push_back(make_unique<Bicycle>("B01",100));
    fleet.push_back(make_unique<TwoWheeler>("T01",300,80,"2027-02-01"));
    fleet.push_back(make_unique<Car>("C01",800,60,"2027-03-01",5));
    fleet.push_back(make_unique<ElectricCar>("E01",1000,"2027-04-01",5,60));
    fleet.push_back(make_unique<ElectricBus>("EB01",2000,"2027-05-01",30));
    double usage[] = {0,2,3,10,20};
    for (size_t i=0;i<fleet.size();++i) {
        Vehicle& v = *fleet[i];
        if (v.rent()) cout << "Rented " << v.kind() << ' ' << v.registration() << '\n';
        double cost = v.charge(2,usage[i]) + 150; // 1 late day
        if (v.returnVehicle()) cout << "Returned " << v.kind()
            << ": Rs " << cost << '\n';
    }
}
