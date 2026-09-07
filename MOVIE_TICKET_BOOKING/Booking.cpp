#pragma once
#include <string>
#include <vector>
#include "Show.cpp"
#include "Showseat.cpp"
#include "Customer.cpp"
using namespace std;

enum BookingStatus { PENDING, CONFIRMED, FAILED, CANCELLED };

// Booking: booking id, which show, which seats, total amount, status.
// Must NOT calculate its own price (PriceCalculator's job) and
// must NOT print itself (TicketPrinter's job).
class Booking {
private:
    static int nextId;   // static member -> shared across all Bookings

    int bookingId;
    Show* show;
    Customer* customer;
    vector<ShowSeat*> seats;
    double totalAmount;
    BookingStatus status;

public:
    Booking(Show* show, Customer* customer, vector<ShowSeat*> seats, double totalAmount) {
        this->bookingId = nextId++;   // 'this' distinguishes member from param
        this->show = show;
        this->customer = customer;
        this->seats = seats;
        this->totalAmount = totalAmount;
        this->status = PENDING;
    }

    int getBookingId() const { return bookingId; }
    Show* getShow() const { return show; }
    Customer* getCustomer() const { return customer; }
    vector<ShowSeat*>& getSeats() { return seats; }
    double getTotalAmount() const { return totalAmount; }
    BookingStatus getStatus() const { return status; }

    void confirm() { status = CONFIRMED; }
    void fail() { status = FAILED; }
    void cancel() { status = CANCELLED; }
};

int Booking::nextId = 1001;   // definition of the static member
