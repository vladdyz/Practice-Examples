//Vlad Zolotukhin OOP345 Review

#include <iostream>
#include <thread>
#include <stdexcept> // for std::exception

void thread_function() {
    std::cout << "Inside thread function\n";
}
void the_end() {
    std::cout << "The End\n";
}
void detached_function() {
    std::cout << "Inside detached thread\n";
}

int main() {
    try {
        // Example demonstrating the use of thread() noexcept
        std::thread t1; // creates a non-joinable thread object

        // Example demonstrating the use of thread(thread&& t) noexcept
        std::thread t2(thread_function); // creates a thread object t2 with thread_function

        // Example demonstrating the use of ~thread() & bool joinable() const noexcept
        if (t1.joinable()) {
            t1.join(); // No effect since t1 is not joinable
        }
        t2.join(); // Waits for t2 to finish execution

        // Example demonstrating the use of thread& operator=(thread&& t) noexcept
        t1 = std::thread(thread_function); // moves the thread handler from temporary thread object to t1

        // Example demonstrating the use of thread::id get_id() const
        std::thread::id id = t1.get_id(); // gets the unique identifier of t1
        std::cout << "Thread ID: " << id << std::endl;

        // Example demonstrating the use of bool joinable() const noexcept
        if (t1.joinable()) {
            std::cout << "t1 is joinable\n"; //t1 can now be joined now that it's been assosciated
        }

        // Example demonstrating the use of void join()
        t1.join(); // waits for t1 to finish execution

        // Example demonstrating the use of void detach()
        std::thread t3(detached_function);
        t3.detach(); // detaches t3 from its parent, allowing it to run independently

        // Example demonstrating the use of void swap(thread& t)
        std::thread t4;
        t3.swap(t4); // swaps the state of t3 with t4

        //The End
        std::thread t5(the_end);
        t5.join();
        //The detached thread might finish and print its message after this
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return 0;
}