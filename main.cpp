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
    vector<observation> observations = {
        // ==========================================
        // 1. THE "HAPPY PATH" (Zero Violations)
        // ==========================================

        // Private car, exact speed limit, belt fastened
        {"PRV-1001", "2026-7-24", car_type::Private, 80, true},

        // Truck, well under speed limit, belt fastened
        {"TRK-2001", "2026-7-24", car_type::Truck, 45, true},

        // Bus, high speed (no rule exists for bus speed), belt fastened
        {"BUS-3001", "2026-7-24", car_type::Bus, 100, true},


        // ==========================================
        // 2. SINGLE VIOLATIONS
        // ==========================================

        // Private car speeding only
        {"PRV-1002", "2026-7-24", car_type::Private, 95, true},

        // Truck speeding only
        {"TRK-2002", "2026-7-24", car_type::Truck, 65, true},

        // Private car, safe speed, but seatbelt unfastened
        {"PRV-1003", "2026-7-24", car_type::Private, 50, false},

        // Bus, seatbelt unfastened
        {"BUS-3002", "2026-7-24", car_type::Bus, 60, false},


        // ==========================================
        // 3. MULTIPLE VIOLATIONS
        // ==========================================

        // Private car speeding AND unfastened seatbelt (Should generate 2 fines)
        {"PRV-1004", "2026-7-24", car_type::Private, 120, false},

        // Truck speeding AND unfastened seatbelt (Should generate 2 fines)
        {"TRK-2003", "2026-7-24", car_type::Truck, 85, false},


        // ==========================================
        // 4. BOUNDARY / EDGE CASES
        // ==========================================

        // Truck exactly at the speed limit (Should NOT be a violation)
        {"TRK-2004", "2026-7-24", car_type::Truck, 60, true},

        // Private car just 1 km/h over the limit (Should be a violation)
        {"PRV-1005", "2026-7-24", car_type::Private, 81, true},

        // Truck extremely over the speed limit
        {"TRK-2005", "2026-7-24", car_type::Truck, 140, true}
    };
    return 0;
}
