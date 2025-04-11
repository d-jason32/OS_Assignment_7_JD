#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

// There are 2 philosophers
#define N 2

// Define 2 mutex locks as chopstick 1 and 2
std::mutex chopstick1;
std::mutex chopstick2;

void philosopher(int num)
{
    while (true) {
        std::cout << "Philosopher " << num + 1 << " is thinking\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        std::cout << "Philosopher " << num + 1 << " is hungry\n";

        // Lock both chopsticks so only 1 can eat
        chopstick1.lock();
        chopstick2.lock();
        std::cout << "Philosopher " << num + 1 << " picks up both chopsticks \n";

        std::cout << "Philosopher " << num + 1 << " is eating\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Eat for 1.5 seconds
        std::cout << "Philosopher " << num + 1 << " puts down chopsticks\n";

        // Put down chopsticks so other philosopher can eat
        chopstick2.unlock();
        chopstick1.unlock();
    }
}

int main()
{
    // Create array of threads for each philosopher
    std::thread threads[N];

    // Run each thread for the philosophers
    for (int i = 0; i < N; i++) {
        threads[i] = std::thread(philosopher, i);
    }

    // Join the threads at the end
    for (int i = 0; i < N; i++)
        threads[i].join();

    return 0;
}
