#include <iostream>
#include <future>
#include <thread>

int main()
{
    std::cout << "Demonstration of std::future in C++ ... \n\n";

    // Create a std::promise object which will be associated with a std::future object. This 'promise' object
    // will produce some result inside an async operation.
    std::promise<int> prom;
    
    // Create a 'future' object which will consume the result produced by a std::promise object.
    std::future<int> fut = prom.get_future();

    // Create a background thread which will perform some async operations and producer a result via std::promise object.
    std::jthread worker = std::jthread([&prom]() -> void {
        std::cout << "[Worker thread]: Starting a worker thread. " << std::endl;
        for (int i = 0; i < 5; i++) {
            // Do some work ...
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        std::cout << "[Worker thread]: Exiting the worker thread. " << std::endl;

        // Produce the result via std::promise object. The signal to std::future object will be generated once the thread 
        // is exited.
        prom.set_value_at_thread_exit(100);
    });
    

    // In the main thread, read the status of associated future object to check if it has received any signal from
    // the associated std::promise object.
    while (true) {
        std::future_status op_status = fut.wait_for(std::chrono::milliseconds(1000));
        if (op_status == std::future_status::ready) {
            // The future object has received the signal from std::promise object. The result can be consumed.
            std::cout << "[Main thread]: The background operation has been completed. The value returned is: " << fut.get() 
                      << std::endl;
            break;
        }
        
        // The value is still not set by the associated std::promise object. 
        // Do some work in the main thread ...
        std::cout << "[Main thread]: Waiting for the result from the worker thread ... " << std::endl;
    }

    return 0;
}

