#pragma once
#include <vector>
#include "Movie.cpp"
#include "Screen.cpp"
#include "Show.cpp"
using namespace std;

// Cinema: the theatre - owns its Screens (composition).
// Must NOT contain booking/payment logic.
class Cinema {
private:
    string name;
    vector<Screen> screens;
    vector<Movie> movies;
    vector<Show> shows;

public:
    Cinema(string name) : name(name) {}

    void addScreen(Screen screen) { screens.push_back(screen); }
    void addMovie(Movie movie) { movies.push_back(movie); }
    void addShow(Show show) { shows.push_back(show); }

    vector<Movie>& listMovies() { return movies; }
    vector<Show>& getShows() { return shows; }
    vector<Screen>& getScreens() { return screens; }

    // Shows belonging to one movie (used by FR2)
    vector<Show*> getShowsForMovie(Movie* movie) {
        vector<Show*> result;
        for (Show& s : shows) {
            if (s.getMovie() == movie) result.push_back(&s);
        }
        return result;
    }
};
