#pragma once
#include <vector>
#include "Showseat.cpp"
using namespace std;

// Calculation: turns a list of seats into a total amount.
// Holds no state, knows nothing about Booking or Payment.
class Calculation {
public:
    static double calculate(vector<ShowSeat*>& seats) {
        double total = 0.0;
        for (ShowSeat* ss : seats) {
            total += ss->getSeat()->getPrice();
        }
        return total;
    }
};
