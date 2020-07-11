#include <iostream>
#include <ostream>
#include <vector>

/* Interface */
class Vehicle
{
public:
    virtual ~Vehicle() { }
    virtual std::ostream& print (std::ostream& os) const = 0;
};

class WaterVehicle : virtual public Vehicle
{
public:
    virtual ~WaterVehicle() {}
    WaterVehicle (float draft) : draft(draft), Vehicle() { }

    std::ostream& print (std::ostream& os) const override
    {
        os << draft;
        return os;
    }

    friend std::ostream& operator<< (std::ostream& out, const WaterVehicle& elem)
    {
        return elem.print(out);
    }

private:
    float draft;
};

class RoadVehicle : virtual public Vehicle
{
public:
    virtual ~RoadVehicle() {}
    RoadVehicle (float clearance) : clearance(clearance), Vehicle() { }

    std::ostream& print (std::ostream& os) const override
    {
        os << clearance;
        return os;
    }

    virtual float get_clearance() const
    {
        return clearance;
    }

    friend std::ostream& operator<< (std::ostream& out, const RoadVehicle& elem)
    {
        return elem.print(out);
    }

private:
    float clearance;
};

/* Wheel, Engine*/
class Wheel
{
public:
    Wheel() : diameter() { }
    Wheel(float diameter) : diameter(diameter) { }
    float get_diameter()
    {
        return diameter;
    }
private:
    float diameter;
};

class Engine
{
public:
    Engine() : power() { }
    Engine(float power) : power(power) { }
    float get_power()
    {
        return power;
    }
private:
    float power;
};

/* Bicycle, Car */
class Bicycle : public RoadVehicle
{
public:
    virtual ~Bicycle() 
    {
        delete[] wheels;
    }

    Bicycle(const Wheel& w0, const Wheel& w1, float clearance)
        : Vehicle(), RoadVehicle(clearance)
    {
        wheels = new Wheel[2];
        wheels[0] = w0;
        wheels[1] = w1;
    }

    float get_clearance() const override
    {
        return RoadVehicle::get_clearance();
    }

    std::ostream& print (std::ostream& os) const override
    {
        os << "Wheels: " << wheels[0].get_diameter() << " " << wheels[1].get_diameter();
        os << " Ride height: " << get_clearance();
        return os;
    }

    friend std::ostream& operator<< (std::ostream& out, const Bicycle& elem)
    {
        return elem.print(out);
    }

private:
    Wheel *wheels = nullptr;
};

class Car : public RoadVehicle
{
public:
    virtual ~Car()
    {
        delete[] wheels;
        delete current_engine;
    }

    Car (const Engine& engine, const Wheel& w0, const Wheel& w1, 
            const Wheel& w2, const Wheel& w3, float clearance)
        : Vehicle(), RoadVehicle(clearance)
    {
        wheels = new Wheel[4];
        wheels[0] = w0;
        wheels[1] = w1;
        wheels[2] = w2;
        wheels[3] = w3;
        current_engine = new Engine(engine);
    }
    /*
    float get_power() const override
    {
        return (*current_engine).get_power();
    }
    */
    
    float get_power()
    {
        return (*current_engine).get_power();
    }
    
    float get_clearance() const override
    {
        return RoadVehicle::get_clearance();
    }

    std::ostream& print (std::ostream& os) const override
    {
        os << "Engine: " << (*current_engine).get_power();
        os << " Wheels: " << wheels[0].get_diameter() << " " << wheels[1].get_diameter();
        os << " " << wheels[2].get_diameter() << " " << wheels[3].get_diameter();
        os << " Ride height: " << get_clearance();
        return os;
    }

    friend std::ostream& operator<< (std::ostream& out, const Car& elem)
    {
        return elem.print(out);
    }

private:
    Wheel *wheels = nullptr;
    Engine *current_engine = nullptr;
};

float getHighestPower(const std::vector<Vehicle*>& v)
{
    float ans = 0, current_power;
    Car* intermed_car;
    for (int i = 0; i < v.size(); i++)
    {
        intermed_car = dynamic_cast<Car*>(v[i]);
        if (intermed_car == nullptr)
        {
            continue;
        }
        current_power = (*intermed_car).get_power();
        ans = (current_power > ans) ? current_power : ans;
    }

    return ans;
}

int main ()
{
    /*
    Car c(Engine(150), Wheel(17), Wheel(17), Wheel(18), Wheel(18), 150);
    std::cout << c << '\n';
    Bicycle t(Wheel(20), Wheel(20), 300);
    std::cout << t << '\n';
    */

    std::vector<Vehicle*> v;
    v.push_back(new Car(Engine(150), Wheel(17), Wheel(17), Wheel(18), Wheel(18), 250));
    v.push_back(new Car(Engine(200), Wheel(19), Wheel(19), Wheel(19), Wheel(19), 130));
    v.push_back(new WaterVehicle(5000)); 

    //Car *c1 = dynamic_cast<Car*>(v[0]);
    //std::cout << *c1 << std::endl;

    std::cout << getHighestPower(v) << std::endl;
    
    for (int i = v.size(); i > 0; --i)
    {
        delete v[i - 1];
    }

    return 0;
}
