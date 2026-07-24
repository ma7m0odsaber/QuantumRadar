#include <bits/stdc++.h>

using namespace std;

class Irule
{
public:
    virtual ~Irule() = default;
    virtual bool check_rule() = 0;
};

class truck_speed: public Irule
{
public:
    bool check_rule() override
    {

    }
};

struct observation
{
    string plate_num;
    string date;
    string car_type;
    int speed;
    bool seat_belt;
};

int main()
{

}