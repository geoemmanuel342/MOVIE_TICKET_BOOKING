#pragma once
#include "Seat.cpp"

enum SeatStatus { AVAILABLE, BOOKED };

// ShowSeat: status of ONE seat FOR ONE show.
// Seat A1 exists once on the Screen, but its status differs
// per Show - so status lives here, not on Seat itself.
// Must NOT know about payment or pricing.
class ShowSeat {
private:
    Seat* seat;
    SeatStatus status;

public:
    ShowSeat() : seat(nullptr), status(AVAILABLE) {}
    ShowSeat(Seat* seat) : seat(seat), status(AVAILABLE) {}

    Seat* getSeat() const { return seat; }

    bool isAvailable() const { return status == AVAILABLE; }

    void book() { status = BOOKED; }
    void release() { status = AVAILABLE; }
};
