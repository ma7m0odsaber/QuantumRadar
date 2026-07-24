#include <bits/stdc++.h>

using namespace std;

struct rule
{
    string name;
    string car_type;
    int speed;
    bool seat_belt;
    int fees;
};

struct observation
{
    string plate_num;
    string date;
    string car_type;
    int speed;
    bool seat_belt;
};

struct violation
{
    string description;
    int fees;
};

struct fine
{
    vector<violation> v;
    observation obs;
    int amount;
};

int main()
{

}