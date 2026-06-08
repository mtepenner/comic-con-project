// Actor.h
#ifndef ACTOR_H
#define ACTOR_H

#include "Celebrity.h"
#include <string>
#include <fstream>
#include <iostream>

// ==========================================
// Actor Subclass & Doubly Linked List Structure
// ==========================================
class Actor : public Celebrity {
private:
    std::string notableRole;

public:
    Actor(std::string n, std::string r) : Celebrity(n), notableRole(r) {}
    
    void displayInfo() const override {} // Suppressed for UI backend
    
    std::string getSaveData() const override {
        return "ACTOR | Name: " + name + " | Role: " + notableRole;
    }
};

struct ActorNode {
    Actor data;
    ActorNode* next;
    ActorNode* prev;
    ActorNode(Actor a) : data(a), next(nullptr), prev(nullptr) {}
};

class ActorSchedule {
private:
    ActorNode* head;
    ActorNode* tail;

    // --- Recursive Helpers ---
    void destroyNodes(ActorNode* current) {
        if (current == nullptr) return; // Base Case
        ActorNode* nextNode = current->next;
        delete current;
        destroyNodes(nextNode); // Recursive Call
    }

    void saveHelper(ActorNode* current, std::ofstream& outFile) const {
        if (current == nullptr) return; // Base Case
        outFile << current->data.getSaveData() << std::endl;
        saveHelper(current->next, outFile); // Recursive Call
    }

public:
    ActorSchedule() : head(nullptr), tail(nullptr) {}
    
    ~ActorSchedule() { 
        destroyNodes(head); 
    }

    void addActor(Actor a) {
        ActorNode* newNode = new ActorNode(a);
        if (head == nullptr) { 
            head = tail = newNode; 
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void saveToFile(std::ofstream& outFile) const { 
        saveHelper(head, outFile); 
    }
};

#endif
