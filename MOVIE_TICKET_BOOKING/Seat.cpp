#pragma once
#include <string>
using namespace std;

// Constants instead of magic numbers
const double SILVER_PRICE = 150.0;
const double GOLD_PRICE = 250.0;
const double PLATINUM_PRICE = 400.0;

enum SeatCategory { SILVER, GOLD, PLATINUM };

// Seat: one physical seat - number + category only.
// Must NOT hold booking status (that belongs to ShowSeat).
class Seat {
private:
    string seatNumber;
    SeatCategory category;

public:
    Seat() : seatNumber(""), category(SILVER) {}
    Seat(string seatNumber, SeatCategory category) {
        this->seatNumber = seatNumber;
        this->category = category;
    }

    string getSeatNumber() const { return seatNumber; }
    SeatCategory getCategory() const { return category; }

    double getPrice() const {
        switch (category) {
            case SILVER:   return SILVER_PRICE;
            case GOLD:     return GOLD_PRICE;
            case PLATINUM: return PLATINUM_PRICE;
        }
        return 0.0;
    }

    string getCategoryName() const {
        switch (category) {
            case SILVER:   return "SILVER";
            case GOLD:     return "GOLD";
            case PLATINUM: return "PLATINUM";
        }
        return "UNKNOWN";
    }
};
