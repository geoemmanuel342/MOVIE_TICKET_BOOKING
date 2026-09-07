# MOVIE_TICKET_BOOKING
# 🎬 Movie Ticket Booking System (C++)

A small console-based movie ticket booking system for a single cinema — built as a System Design assignment (TCS-504, Semester 5) to practice OOP design before writing a single line of code.

You can browse movies, pick a show, see the live seat map, book seats, pay by UPI/Card/Cash, get a printed ticket, and cancel a booking. Nothing fancy — just a clean, modular console app that models the whole booking flow properly.

## What it does

- **List movies** currently playing
- **List shows** (screen + time) for whichever movie you pick
- **Show the live seat layout** — SILVER / GOLD / PLATINUM rows, with `[ ]` for available and `[X]` for booked
- **Book one or more seats** in a single go — if even one seat you picked is already taken, the whole booking is rejected and nothing changes
- **Price automatically** by seat category: SILVER ₹150, GOLD ₹250, PLATINUM ₹400
- **Pay by UPI, Card, or Cash** — a booking is only confirmed once payment succeeds
- **Print a ticket** with booking ID, movie, screen, time, seats, and total
- **Cancel a booking** — the seats go straight back to available

## Why it's split into so many files

This wasn't meant to be a quick script — the point of the assignment was to actually design the system first (requirement analysis → class diagram → sequence diagram) and only then write the code. So every class lives in its own file and sticks to exactly one job:

| File | What it's responsible for |
|---|---|
| `Movie.cpp` | Title, language, duration — that's it |
| `Seat.cpp` | One physical seat: number, category, price |
| `Screen.cpp` | One auditorium; builds and owns its seats |
| `Cinema.cpp` | The theatre — owns screens, movies, and shows |
| `Show.cpp` | A movie playing on a screen at a given time; owns its `ShowSeat`s |
| `Showseat.cpp` | Whether *this* seat is booked for *this* show — kept separate from `Seat` because the same physical seat A1 can be free at 6 PM and booked at 9 PM |
| `Customer.cpp` | Name and phone, nothing else |
| `Booking.cpp` | Booking ID, show, seats, amount, status — doesn't calculate price or print itself |
| `Payment.cpp` | Abstract payment contract (`pay(amount)`) |
| `PaymentMetod.cpp` | `UpiPayment`, `CardPayment`, `CashPayment` — each implements `pay()` its own way |
| `Calculation.cpp` | Turns a list of seats into a total — knows nothing about bookings or payments |
| `TicketPrint.cpp` | Formats and prints the ticket — printing only, never touches booking state |
| `Bookingservice.cpp` | The orchestrator — runs the full booking flow end to end |
| `main.cpp` | The console menu and input handling, nothing else |

The idea behind splitting it this way: if tomorrow you need to add NetBanking as a payment option, you add one new file — you never touch `BookingService` or anything else. Same story if the ticket format changes, or a new seat category gets added.

## OOP concepts in here

- **Encapsulation** — seat status and booking amount are private, only changed through methods like `book()`, `release()`, `confirm()`
- **Abstraction** — `Payment` is a pure abstract class; nothing outside it needs to know *how* a payment actually happens
- **Inheritance** — `UpiPayment`, `CardPayment`, `CashPayment` all extend `Payment`
- **Runtime polymorphism** — `BookingService` calls `payment->pay(total)` without caring which subclass it actually is
- **Compile-time polymorphism** — overloaded `Movie` and `Seat` constructors
- **Static members** — `Booking::nextId` generates unique booking IDs across every booking
- **Composition** — `Screen` owns its `Seat`s, `Show` owns its `ShowSeat`s; destroy the parent and the parts go with it
- **Aggregation** — `Show` just borrows a `Movie` (cancel a show, the movie still exists and still plays elsewhere)

## Building and running it

You just need a C++ compiler that supports C++17 (g++ works fine).

```bash
g++ main.cpp
```

No external libraries, no build system needed — it's all standard C++.

## Sample run

```
===== MOVIE TICKET BOOKING =====
1. Movies  2. Book  3. Cancel  0. Exit
Choose: 2

  [1] 3 Idiots
  [2] Interstellar
  Choose movie: 1
  [1] Screen-1  06:00 PM
  [2] Screen-2  09:00 PM
  Choose show: 1

  SCREEN-1  06:00 PM | 3 Idiots
  SILVER   A1[ ] A2[ ] A3[ ] A4[ ]
  GOLD     B1[ ] B2[ ] B3[ ]
  PLATINUM C1[ ] C2[ ]

  Seats (e.g. A1,B2): A1,B2
  Pay by: 1.UPI  2.Card  3.Cash > 1
  TOTAL Rs.400
  [UPI] Rs.400 paid successfully

  ================ TICKET ================
  Booking ID : BK1001
  Movie      : 3 Idiots
  Screen     : Screen-1  06:00 PM
  Seats      : A1, B2
  Amount     : Rs.400   Status: CONFIRMED
  =========================================
```

## Edge cases it actually handles

- Trying to book a seat that's already taken → booking rejected, nothing else changes
- A failed payment → booking stays unconfirmed, seats are never marked booked
- Cancelling a confirmed booking → its seats go back to available immediately
- Garbage input at any menu (letters instead of numbers, out-of-range choices) → a clear message instead of a crash

## What's deliberately left out

This is scoped tightly to the 8 required features — no database, no user accounts, no multi-cinema support, no seat locking for concurrent users. It's a single-process console demo built to show clean OOP design, not a production booking engine.

## Course context

Built for **TCS-504 (System Design)**, B.Tech CSE Semester 5, Assignment 1.
