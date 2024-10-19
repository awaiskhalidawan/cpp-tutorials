#include <iostream>
#include <future>
#include <thread>
#include <vector>

using namespace std::literals;

uint32_t doSomeWork()
{
    //std::cout << "Work started by thread id: " << std::this_thread::get_id() << std::endl;

    for (uint16_t i = 0; i < 10; i++) {
        //std::cout << "Doing work. Thread id: " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(500ms);
    }
    
    std::cout << "Work completed from thread id: " << std::this_thread::get_id() << std::endl;
    return 3;
}

int main()
{
    std::cout << "Hello World from main(). Thread Id: " << std::this_thread::get_id() << std::endl;

    std::vector<std::future<uint32_t>> res;

    // Launch 20 different async tasks.
    for (uint16_t i = 0; i < 20; i++) {
        res.push_back(std::move(std::async(std::launch::async, doSomeWork)));
    }

    while (true) {
        for (uint16_t i = 0; i < 20; i++) {
            auto future_res = res.at(i).wait_for(std::chrono::duration<double>(1000ms));
            std::cout << static_cast<int>(future_res) << std::endl;
        }
    }

    return 0;
}
