#include <iostream>
#include <vector>
#include <sstream>
#include "Cinema.cpp"
#include "Bookingservice.cpp"
using namespace std;

// Splits "A1,B2" into {"A1","B2"}
vector<string> splitSeats(const string& input) {
    vector<string> result;
    stringstream ss(input);
    string item;
    while (getline(ss, item, ',')) result.push_back(item);
    return result;
}

int main() {
    // --- demo data setup ---
    Cinema cinema("Downtown Cinema");
    cinema.addMovie(Movie("3 Idiots", "Hindi", 170));
    cinema.addMovie(Movie("Interstellar", "English", 169));

    Screen screen1(1);
    Screen screen2(2);
    cinema.addScreen(screen1);
    cinema.addScreen(screen2);

    cinema.addShow(Show(&cinema.listMovies()[0], &cinema.getScreens()[0], "06:00 PM"));
    cinema.addShow(Show(&cinema.listMovies()[0], &cinema.getScreens()[1], "09:00 PM"));

    BookingService bookingService;
    Customer customer("Raghav", "9999999999");   // one demo customer
    vector<Booking*> myBookings;

    // --- menu loop ---
    int choice = -1;
    while (choice != 0) {
        cout << "\n===== MOVIE TICKET BOOKING =====\n";
        cout << "1. Movies  2. Book  3. Cancel  0. Exit\nChoose: ";

        if (!(cin >> choice)) {   // edge case 4: invalid menu input, no crash
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  Invalid input\n";
            continue;
        }

        if (choice == 1) {   // FR1
            vector<Movie>& movies = cinema.listMovies();
            if (movies.empty()) {
                cout << "  No movies currently playing\n";
                continue;
            }
            for (size_t i = 0; i < movies.size(); i++) {
                cout << "  [" << i + 1 << "] " << movies[i].getTitle()
                     << "  " << movies[i].getLanguage()
                     << "  " << movies[i].getDuration() << " min\n";
            }
        }
        else if (choice == 2) {   // Book -> walks through FR2, FR3, FR4/5/6/7
            vector<Movie>& movies = cinema.listMovies();
            for (size_t i = 0; i < movies.size(); i++)
                cout << "  [" << i + 1 << "] " << movies[i].getTitle() << "\n";
            cout << "  Choose movie: ";
            int m; cin >> m;
            if (m < 1 || m > (int)movies.size()) { cout << "  Invalid choice\n"; continue; }

            vector<Show*> shows = cinema.getShowsForMovie(&movies[m - 1]);
            if (shows.empty()) { cout << "  Coming soon\n"; continue; }   // FR2

            for (size_t i = 0; i < shows.size(); i++)
                cout << "  [" << i + 1 << "] Screen-" << shows[i]->getScreen()->getScreenNumber()
                     << "  " << shows[i]->getStartTime() << "\n";
            cout << "  Choose show: ";
            int sIdx; cin >> sIdx;
            if (sIdx < 1 || sIdx > (int)shows.size()) { cout << "  Invalid choice\n"; continue; }

            Show* show = shows[sIdx - 1];
            show->displaySeatLayout();   // FR3

            cin.ignore();
            cout << "  Seats (e.g. A1,B2): ";
            string seatInput;
            getline(cin, seatInput);
            vector<string> seatNums = splitSeats(seatInput);

            cout << "  Pay by: 1.UPI  2.Card  3.Cash > ";
            int payChoice; cin >> payChoice;

            Booking* b = bookingService.bookTicket(show, seatNums, &customer, payChoice);
            if (b != nullptr && b->getStatus() == CONFIRMED) myBookings.push_back(b);
        }
        else if (choice == 3) {   // FR8
            if (myBookings.empty()) { cout << "  No bookings to cancel\n"; continue; }
            cout << "  Your bookings: ";
            for (Booking* b : myBookings)
                if (b->getStatus() == CONFIRMED) cout << "BK" << b->getBookingId() << " ";
            cout << "\n  Enter booking id to cancel: BK";
            int id; cin >> id;

            Booking* target = nullptr;
            for (Booking* b : myBookings) if (b->getBookingId() == id) target = b;
            bookingService.cancelBooking(target);
        }
        else if (choice != 0) {
            cout << "  Invalid choice\n";   // edge case 4
        }
    }

    cout << "  Goodbye!\n";
    return 0;
}
