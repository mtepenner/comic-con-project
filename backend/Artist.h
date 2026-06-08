// Artist.h
#ifndef ARTIST_H
#define ARTIST_H

#include "Celebrity.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

// ==========================================
// Artist Subclass & Vector Structure
// ==========================================
class Artist : public Celebrity {
private:
    std::string style;
    int boothNumber;

public:
    Artist(std::string n, std::string s, int b) : Celebrity(n), style(s), boothNumber(b) {}
    
    void displayInfo() const override {} // Suppressed for UI backend
    
    std::string getSaveData() const override {
        return "ARTIST | Name: " + name + " | Style: " + style + " | Booth: " + std::to_string(boothNumber);
    }
};

class ArtistManager {
private:
    std::vector<Artist> artists;

    // --- Recursive Helper ---
    void saveHelper(size_t index, std::ofstream& outFile) const {
        if (index >= artists.size()) return; // Base Case
        outFile << artists[index].getSaveData() << std::endl;
        saveHelper(index + 1, outFile); // Recursive Call
    }

public:
    void addArtist(Artist a) { 
        artists.push_back(a); 
    }
    
    void saveToFile(std::ofstream& outFile) const { 
        saveHelper(0, outFile); 
    }
};

#endif
