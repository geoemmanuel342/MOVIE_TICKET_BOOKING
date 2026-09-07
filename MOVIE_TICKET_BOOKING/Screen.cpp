#pragma once
#include <vector>
#include "Seat.cpp"
using namespace std;

// Screen: an auditorium; owns its Seats (composition - seats
// don't exist without a screen). Must NOT know about Movies/Shows.
class Screen {
private:
    int screenNumber;
    vector<Seat> seats;

public:
    Screen(int screenNumber) : screenNumber(screenNumber) {
        // Build a fixed layout: A-row SILVER, B-row GOLD, C-row PLATINUM
        seats.push_back(Seat("A1", SILVER));
        seats.push_back(Seat("A2", SILVER));
        seats.push_back(Seat("A3", SILVER));
        seats.push_back(Seat("A4", SILVER));
        seats.push_back(Seat("B1", GOLD));
        seats.push_back(Seat("B2", GOLD));
        seats.push_back(Seat("B3", GOLD));
        seats.push_back(Seat("C1", PLATINUM));
        seats.push_back(Seat("C2", PLATINUM));
    }

    int getScreenNumber() const { return screenNumber; }
    vector<Seat>& getSeats() { return seats; }
};
