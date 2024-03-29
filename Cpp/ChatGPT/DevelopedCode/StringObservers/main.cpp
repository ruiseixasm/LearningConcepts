#include <iostream>
#include <vector>
#include <algorithm>    // Absolutelly needed for std::remove!!
#include <string>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>

// Observer interface
class Observer {
public:
    virtual void update(const std::string& message) = 0;
};

// Subject class
class Subject {
private:
    std::vector<Observer*> observers;
    bool running;

public:
    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    void detach(Observer* observer) {
        // Use std::remove stacks content without removed observer elements (without resizing)
        auto removable_tail = std::remove(observers.begin(), observers.end(), observer);

        // Erases the tail from the vector sized by the previously removed elements (resizes)
        observers.erase(removable_tail, observers.end());
    }

    void notify(const std::string& message) {
        for (Observer* observer : observers) {
            observer->update(message);
        }
    }

    void run() {
        running = true;
        while (running) {
            // Generate a random message
            std::string message = generateRandomString();

            // Notify observers
            notify(message);

            // Sleep for a random period
            std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 3000 + 1000)); // Random sleep between 1 to 4 seconds
        }
    }

    void stop() {
        running = false;
    }

private:
    std::string generateRandomString() {
        const std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        const size_t length = 10; // Length of the random string

        std::string randomString;
        for (size_t i = 0; i < length; ++i) {
            randomString.push_back(charset[rand() % charset.length()]);
        }
        return randomString;
    }
};

// Concrete observer class
class ConcreteObserver : public Observer {
public:
    void update(const std::string& message) override {
        std::cout << "Received message: " << message << std::endl;
    }
};

int main() {
    // Initialize random seed
    srand(time(nullptr));

    // Create subject
    Subject subject;

    // Create observers
    ConcreteObserver observer1;
    ConcreteObserver observer2;

    // Attach observers to subject
    subject.attach(&observer1);
    subject.attach(&observer2);

    // Run the subject in a separate thread
    std::thread subjectThread(&Subject::run, &subject);

    // Wait for user input to stop the subject
    std::cout << "Press enter to stop..." << std::endl;
    std::cin.ignore();
    
    // Stop the subject
    subject.stop();
    subjectThread.join();

    return 0;
}
