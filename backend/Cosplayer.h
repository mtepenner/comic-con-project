// Cosplayer.h
#ifndef COSPLAYER_H
#define COSPLAYER_H

#include "Celebrity.h"
#include <string>
#include <fstream>
#include <iostream>

// ==========================================
// Cosplayer Subclass & Circular Linked List Structure
// ==========================================
class Cosplayer : public Celebrity {
private:
    std::string character;

public:
    Cosplayer(std::string n, std::string c) : Celebrity(n), character(c) {}
    
    void displayInfo() const override {} // Suppressed for UI backend
    
    std::string getSaveData() const override {
        return "COSPLAYER | Name: " + name + " | Character: " + character;
    }
};

struct CosplayerNode {
    Cosplayer data;
    CosplayerNode* next;
    CosplayerNode(Cosplayer c) : data(c), next(nullptr) {}
};

class CosplayerParade {
private:
    CosplayerNode* head;

    // --- Recursive Helpers ---
    void destroyNodes(CosplayerNode* current) {
        if (current == head) return; // Base Case
        CosplayerNode* nextNode = current->next;
        delete current;
        destroyNodes(nextNode); // Recursive Call
    }

    CosplayerNode* findTail(CosplayerNode* current) {
        if (current->next == head) return current; // Base Case
        return findTail(current->next); // Recursive Call
    }

    void saveHelper(CosplayerNode* current, std::ofstream& outFile) const {
        outFile << current->data.getSaveData() << std::endl;
        if (current->next == head) return; // Base Case
        saveHelper(current->next, outFile); // Recursive Call
    }

public:
    CosplayerParade() : head(nullptr) {}
    
    ~CosplayerParade() {
        if (head == nullptr) return;
        destroyNodes(head->next);
        delete head;
    }

    void addCosplayer(Cosplayer c) {
        CosplayerNode* newNode = new CosplayerNode(c);
        if (head == nullptr) {
            head = newNode;
            newNode->next = head; 
        } else {
            CosplayerNode* tail = findTail(head);
            tail->next = newNode;
            newNode->next = head;
        }
    }

    void saveToFile(std::ofstream& outFile) const {
        if (head == nullptr) return;
        saveHelper(head, outFile);
    }
};

#endif
