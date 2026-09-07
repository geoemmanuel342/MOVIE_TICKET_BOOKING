#pragma once
#include <vector>
#include <iostream>
#include <iomanip>
#include "Movie.cpp"
#include "Screen.cpp"
#include "Showseat.cpp"
using namespace std;

// Show: one screening = a Movie on a Screen at a time.
// Owns its ShowSeats (composition). References Movie/Screen only
// (aggregation) - it must NOT modify Movie or Screen data.
class Show {
private:
    Movie* movie;
    Screen* screen;
    string startTime;
    vector<ShowSeat> showSeats;

public:
    Show(Movie* movie, Screen* screen, string startTime)
        : movie(movie), screen(screen), startTime(startTime) {
        for (Seat& s : screen->getSeats()) {
            showSeats.push_back(ShowSeat(&s));
        }
    }

    Movie* getMovie() const { return movie; }
    Screen* getScreen() const { return screen; }
    string getStartTime() const { return startTime; }
    vector<ShowSeat>& getShowSeats() { return showSeats; }

    // Returns nullptr if the seat number doesn't exist on this show
    ShowSeat* findShowSeat(const string& seatNumber) {
        for (ShowSeat& ss : showSeats) {
            if (ss.getSeat()->getSeatNumber() == seatNumber) return &ss;
        }
        return nullptr;
    }

    void displaySeatLayout() {
        cout << "  SCREEN-" << screen->getScreenNumber() << "  "
             << startTime << " | " << movie->getTitle() << "\n";

        SeatCategory categories[3] = { SILVER, GOLD, PLATINUM };
        string names[3] = { "SILVER", "GOLD", "PLATINUM" };

        for (int i = 0; i < 3; i++) {
            cout << "  " << left << setw(9) << names[i];
            bool any = false;
            for (ShowSeat& ss : showSeats) {
                if (ss.getSeat()->getCategory() == categories[i]) {
                    any = true;
                    cout << ss.getSeat()->getSeatNumber()
                         << (ss.isAvailable() ? "[ ] " : "[X] ");
                }
            }
            if (!any) cout << "(none)";
            cout << "\n";
        }
    }
};
