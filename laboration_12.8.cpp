#include <iostream>
using namespace std;

struct BusStop {
    string name;
    int time;

    BusStop(string name, int arrivalTime) : name(name), time(arrivalTime) {}
};

struct Elem {
    Elem* next; 
    Elem* prev;
    BusStop stop; 

    Elem(BusStop _stop) : next(nullptr), prev(nullptr), stop(_stop) {}
};


void enqueue(Elem*& first, Elem*& last, BusStop stop);
BusStop dequeue(Elem*& first, Elem*& last);
string determineDirection(Elem* first, Elem* last, string startStop, string endStop);

int main() {
    Elem* first = NULL,
        * last = NULL;

    int numStops;
    cout << "Enter the number of bus stops: ";
    cin >> numStops;

    for (int i = 0; i < numStops; ++i) {
        string stopName;
        int arrivalTime;
        cout << "Enter name of bus stop " << i + 1 << ": ";
        cin >> stopName;
        cout << "Enter arrival time at bus stop " << stopName << ": ";
        cin >> arrivalTime;
        enqueue(first, last, BusStop(stopName, arrivalTime));
    }

    string startStop, endStop;
    cout << "Enter the starting bus stop: ";
    cin >> startStop;
    cout << "Enter the destination bus stop: ";
    cin >> endStop;

    string direction = determineDirection(first, last, startStop, endStop);
    cout << "The direction of movement to reach the stop: " << direction << endl;
	return 0;
}



void enqueue(Elem*& first, Elem*& last, BusStop stop) {
    Elem* tmp = new Elem(stop);
    if (last != nullptr)
        last->next = tmp;
    tmp->prev = last;
    last = tmp;
    if (first == nullptr)
        first = tmp;
    last = tmp;
}

BusStop dequeue(Elem*& first, Elem*& last) {
    Elem* tmp = first->next;
    BusStop stop = first->stop;
    delete first;
    first = tmp;
    if (first == nullptr)
        last = nullptr;
    else
        first->prev = nullptr;
    return stop;
}


string determineDirection(Elem* first, Elem* last, string startStop, string endStop) {
    Elem* current = first;
    Elem* left = nullptr;
    Elem* right = nullptr;
    bool foundStart = false;
    bool foundEnd = false;

   
    while (current != nullptr) {
        if (current->stop.name == startStop) {
            foundStart = true;
        }
        if (current->stop.name == endStop) {
            foundEnd = true;
        }
        if (foundStart && foundEnd) {
            break;
        }
        current = current->next;
    }

    if (!foundStart) {
        return "Start station not found!";
    }
    if (!foundEnd) {
        return "End station not found!";
    }

    current = first;
    while (current != nullptr) {
        if (current->stop.name == endStop) {
            left = current;
            break;
        }
        current = current->next;
    }

    current = last;
    while (current != nullptr) {
        if (current->stop.name == endStop) {
            right = current;
            break;
        }
        current = current->prev;
    }

    int leftTime = 0;
    current = left->prev;
    while (current != nullptr && current->prev != nullptr) {
        leftTime += current->stop.time - current->prev->stop.time;
        current = current->prev;
    }

    int rightTime = 0;
    current = right->next;
    while (current != nullptr && current->next != nullptr) {
        rightTime += current->stop.time - current->prev->stop.time;
        current = current->next;
    }


    if (leftTime < rightTime) {
        return "Left";
    }
    else {
        return "Right";
    }
}
