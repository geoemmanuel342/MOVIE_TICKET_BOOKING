#pragma once
#include <iostream>
#include <vector>
#include "Show.cpp"
#include "Showseat.cpp"
#include "Customer.cpp"
#include "Booking.cpp"
#include "Payment.cpp"
#include "PaymentMetod.cpp"
#include "Calculation.cpp"
#include "TicketPrint.cpp"
using namespace std;

// BookingService: the orchestrator - runs the booking flow end to end.
// Must NOT contain menu/console-reading logic (that's main's job).
// Open/Closed: adding a new Payment type needs no change here.
class BookingService {
public:
    // Returns nullptr if booking was rejected (FR4) - caller checks for that.
    Booking* bookTicket(Show* show, vector<string>& seatNumbers,
                         Customer* customer, int paymentChoice) {

        if (seatNumbers.empty()) {
            cout << "  No seat selected\n";   // FR5 edge case
            return nullptr;
        }

        vector<ShowSeat*> chosen;
        for (string& num : seatNumbers) {
            ShowSeat* ss = show->findShowSeat(num);
            if (ss == nullptr) {
                cout << "  Invalid seat number: " << num << "\n";   // edge case 4
                return nullptr;
            }
            if (!ss->isAvailable()) {
                cout << "  Seat " << num << " is already booked. Booking rejected.\n";
                return nullptr;   // FR4: reject whole booking, nothing changes
            }
            chosen.push_back(ss);
        }

        double total = Calculation::calculate(chosen);   // FR5
        Booking* booking = new Booking(show, customer, chosen, total);   // <<create>>

        cout << "  TOTAL Rs." << total << "\n";
        cout << "  Pay by: 1.UPI  2.Card  3.Cash > ";

        Payment* payment;   // FR6: exactly one method per booking
        if (paymentChoice == 1) payment = new UpiPayment();
        else if (paymentChoice == 2) payment = new CardPayment();
        else payment = new CashPayment();

        bool success = payment->pay(total);   // runtime polymorphism

        if (success) {
            for (ShowSeat* ss : chosen) ss->book();   // seats marked booked only now
            booking->confirm();
            TicketPrinter::printTicket(booking);   // FR7
        } else {
            booking->fail();   // FR6: seats were never marked booked, so nothing to release
            cout << "  Payment failed. Booking not confirmed.\n";
        }

        delete payment;
        return booking;
    }

    // FR8: cancel a booking - its seats become AVAILABLE again
    void cancelBooking(Booking* booking) {
        if (booking == nullptr) {
            cout << "  No such booking\n";
            return;
        }
        if (booking->getStatus() != CONFIRMED) {
            cout << "  Only a confirmed booking can be cancelled\n";
            return;
        }
        for (ShowSeat* ss : booking->getSeats()) ss->release();
        booking->cancel();
        cout << "  Booking BK" << booking->getBookingId() << " cancelled. Seats released.\n";
    }
};
