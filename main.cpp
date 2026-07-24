#include <bits/stdc++.h>

using namespace std;

enum class car_type
{
    Private,
    Truck,
    Bus
};

struct observation
{
    string plate_num;
    string date;
    car_type car;
    int speed;
    bool seat_belt;
};

class Irule
{
public:
    virtual ~Irule() = default;
    virtual bool check_violation(observation obs) = 0;
};

class truck_speed: public Irule
{
public:
    bool check_violation(observation obs) override
    {
        if (obs.car == car_type::Truck && obs.speed > 60)
            return true;
        return false;
    }
};

class private_speed: public Irule
{
public:
    bool check_violation(observation obs) override
    {
        if (obs.car == car_type::Private && obs.speed > 80)
            return true;
        return false;
    }
};

class seatbelt: public Irule
{
public:
    bool check_violation(observation obs) override
    {
        if (!obs.seat_belt)
            return true;
        return false;
    }
};

int main()
{

}