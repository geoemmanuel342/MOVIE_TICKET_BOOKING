#pragma once
#include <string>
using namespace std;

// Customer: name and phone only. Associated with Booking,
// owns nothing and is owned by nothing.
class Customer {
private:
    string name;
    string phone;

public:
    Customer(string name, string phone) : name(name), phone(phone) {}

    string getName() const { return name; }
    string getPhone() const { return phone; }
};
