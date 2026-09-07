#pragma once
#include <iostream>
#include "Booking.cpp"
using namespace std;

// TicketPrinter: format and print a ticket - printing only.
// Must NOT modify the Booking or calculate price.
class TicketPrinter {
public:
    static void printTicket(Booking* booking) {
        cout << "\n  ================ TICKET ================\n";
        cout << "  Booking ID : BK" << booking->getBookingId() << "\n";
        cout << "  Movie      : " << booking->getShow()->getMovie()->getTitle() << "\n";
        cout << "  Screen     : Screen-" << booking->getShow()->getScreen()->getScreenNumber()
             << "  " << booking->getShow()->getStartTime() << "\n";
        cout << "  Seats      : ";
        vector<ShowSeat*>& seats = booking->getSeats();
        for (size_t i = 0; i < seats.size(); i++) {
            cout << seats[i]->getSeat()->getSeatNumber();
            if (i != seats.size() - 1) cout << ", ";
        }
        cout << "\n  Amount     : Rs." << booking->getTotalAmount()
             << "   Status: CONFIRMED\n";
        cout << "  =========================================\n";
    }
};
