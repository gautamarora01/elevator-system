#include <iostream>
#include <queue>
#include <vector>
#include <ctime>

using namespace std;

// Define constants
const int MAX_FLOORS = 10;
const int MAX_CAPACITY = 10;

// Enum for elevator state
enum class ElevatorState { IDLE, MOVING };

// Person structure
struct Person {
    int id;
    int destinationFloor;
};

// Elevator class
class Elevator {
private:
    int currentFloor;
    int capacity;
    ElevatorState state;
    vector<Person> passengers;

public:
    Elevator() : currentFloor(0), capacity(MAX_CAPACITY), state(ElevatorState::IDLE) {}

    void addPerson(Person person) {
        passengers.push_back(person);
    }

    void removePerson(int personId) {
        for (auto it = passengers.begin(); it != passengers.end(); ++it) {
            if (it->id == personId) {
                passengers.erase(it);
                break;
            }
        }
    }

    void move(int destinationFloor) {
        currentFloor = destinationFloor;
    }

    bool isFull() const {
        return passengers.size() >= capacity;
    }

    int getCurrentFloor() const {
        return currentFloor;
    }

    int getCapacity() const {
        return capacity;
    }

    ElevatorState getState() const {
        return state;
    }
};

// Elevator Controller class
class ElevatorController {
private:
    vector<Elevator> elevators;

public:
    ElevatorController(int numElevators) {
        elevators.resize(numElevators);
    }

    void requestElevator(int floor, int destinationFloor, int personId) {
        // Find nearest elevator
        int minDistance = MAX_FLOORS;
        int elevatorIndex = -1;
        for (int i = 0; i < elevators.size(); ++i) {
            int distance = abs(elevators[i].getCurrentFloor() - floor);
            if (distance < minDistance && !elevators[i].isFull()) {
                minDistance = distance;
                elevatorIndex = i;
            }
        }

        // Handle elevator request
        if (elevatorIndex != -1) {
            elevators[elevatorIndex].addPerson({personId, destinationFloor});
            elevators[elevatorIndex].move(destinationFloor);
            cout << "Elevator " << elevatorIndex + 1 << " moving to floor " << destinationFloor << endl;
        } else {
            cout << "No available elevator at the moment. Please wait." << endl;
        }
    }
};

int main() {
    srand(time(0)); // Seed for random number generation

    // Initialize elevator controller with 3 elevators
    ElevatorController controller(3);

    // Simulate elevator requests
    for (int i = 0; i < 10; ++i) {
        int floor = rand() % MAX_FLOORS + 1;
        int destinationFloor = rand() % MAX_FLOORS + 1;
        int personId = i + 1;
        cout << "Person " << personId << " requesting elevator from floor " << floor << " to floor " << destinationFloor << endl;
        controller.requestElevator(floor, destinationFloor, personId);
        cout << endl;
    }

    return 0;
}
