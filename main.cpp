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
    string plate_num;
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
private:
    int fee = 0;
    string description = "";
    string rule_name = "";
public:
    virtual bool check_violation(observation obs) = 0;

    void set_fee(int x) { fee = x; }
    int get_fee() { return fee; }

    void set_description(string x) { description = x; }
    string get_description() { return description; }

    void set_rule_name(string x) { rule_name = x; }
    string get_rule_name() { return rule_name; }

    virtual ~Irule() = default;
};

class truck_speed: public Irule
{
public:
    truck_speed() { set_rule_name("Truck Speed Limit"); }

    bool check_violation(observation obs) override
    {
        if (obs.car == car_type::Truck && obs.speed > 60)
        {
            set_fee(500);
            set_description("speed of " + to_string(obs.speed) + " exceeded max allowed 60");
            return true;
        }
        return false;
    }
};

class private_speed: public Irule
{
public:
    private_speed() { set_rule_name("Private Car Speed Limit"); }

    bool check_violation(observation obs) override
    {
        if (obs.car == car_type::Private && obs.speed > 80)
        {
            set_fee(300);
            set_description("speed of " + to_string(obs.speed) + " exceeded max allowed 80");
            return true;
        }
        return false;
    }
};

class seatbelt: public Irule
{
public:
    seatbelt() { set_rule_name("Seatbelt Requirement"); }

    bool check_violation(observation obs) override
    {
        if (!obs.seat_belt)
        {
            set_fee(100);
            set_description("Seatbelt not fasted ");
            return true;
        }
        return false;
    }
};

class radar
{
private:
    vector<unique_ptr<Irule>> rules;
    vector<observation> observations;

    map<string, int> plate_fines;
    map<string, int> rule_counts;

public:
    radar()
    {
        rules.push_back(make_unique<truck_speed>());
        rules.push_back(make_unique<private_speed>());
        rules.push_back(make_unique<seatbelt>());
    }

    void add_observation(observation obs)
    {
        observations.push_back(obs);
    }

    void process_observations()
    {
        for (const auto& obs : observations)
        {
            fine current_fine;
            current_fine.obs = obs;
            current_fine.amount = 0;
            bool issued_violation = false;

            for (const auto& rule : rules)
            {
                if (rule->check_violation(obs))
                {
                    issued_violation = true;
                    violation v;
                    v.plate_num = obs.plate_num;
                    v.description = rule->get_description();
                    v.fees = rule->get_fee();

                    current_fine.v.push_back(v);
                    current_fine.amount += v.fees;

                    rule_counts[rule->get_rule_name()]++;
                }
            }

            if (issued_violation)
            {
                plate_fines[obs.plate_num] += current_fine.amount;

                cout << "Traffic fine for car " << obs.plate_num << "\n";
                cout << "Total amount: " << current_fine.amount << " EGP\n";
                cout << "Violations:\n";
                for (const auto& v : current_fine.v)
                {
                    cout << v.description << ": " << v.fees << " EGP\n";
                }
                cout << "-----------------------------------\n";
            }
        }
    }

    void print_all_fines()
    {
        cout << "--- All Fines by Plate Number ---\n";
        for (const auto& [plate, amount] : plate_fines)
        {
            cout << plate << " : " << amount << " EGP\n";
        }
    }

    void print_rule_statistics()
    {
        cout << "\n--- Violated Rules Count ---\n";
        for (const auto& [rule, count] : rule_counts)
        {
            cout << rule << " : " << count << "\n";
        }
    }
};

int main()
{
    vector<observation> test_cases = {
        // 1. THE "HAPPY PATH" (Zero Violations)
        {"PRV-1001", "2026-7-24", car_type::Private, 80, true},
        {"TRK-2001", "2026-7-24", car_type::Truck, 45, true},
        {"BUS-3001", "2026-7-24", car_type::Bus, 100, true},

        // 2. SINGLE VIOLATIONS
        {"PRV-1002", "2026-7-24", car_type::Private, 95, true},
        {"TRK-2002", "2026-7-24", car_type::Truck, 65, true},
        {"PRV-1003", "2026-7-24", car_type::Private, 50, false},
        {"BUS-3002", "2026-7-24", car_type::Bus, 60, false},

        // 3. MULTIPLE VIOLATIONS
        {"PRV-1004", "2026-7-24", car_type::Private, 120, false},
        {"TRK-2003", "2026-7-24", car_type::Truck, 85, false},

        // 4. BOUNDARY / EDGE CASES
        {"TRK-2004", "2026-7-24", car_type::Truck, 60, true},
        {"PRV-1005", "2026-7-24", car_type::Private, 81, true},
        {"TRK-2003", "2026-7-24", car_type::Truck, 140, true}
    };

    radar traffic_radar;

    for (const auto& obs : test_cases)
    {
        traffic_radar.add_observation(obs);
    }

    traffic_radar.process_observations();

    traffic_radar.print_all_fines();
    traffic_radar.print_rule_statistics();

    return 0;
}