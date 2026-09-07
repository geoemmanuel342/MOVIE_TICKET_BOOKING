#pragma once
#include <string>
using namespace std;

// Movie: knows its own title/language/duration only.
// Must NOT know about Shows, Screens, or pricing.
class Movie {
private:
    string title;
    string language;
    int durationMins;

public:
    // Overloaded constructors -> compile-time polymorphism
    Movie() : title("Unknown"), language("Unknown"), durationMins(0) {}
    Movie(string title, string language, int durationMins) {
        this->title = title;
        this->language = language;
        this->durationMins = durationMins;
    }

    string getTitle() const { return title; }
    string getLanguage() const { return language; }
    int getDuration() const { return durationMins; }
};
