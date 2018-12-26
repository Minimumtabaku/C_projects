//#include <thread>
//#include <iostream>
//#include <mutex>
//#include <atomic>
//#include <vector>
//#include "atomic_counter.hpp"
//
//int main() {
//    using namespace std::chrono_literals;
//    std::mutex guard;
//    int counter = 0;
//
//    auto thread_func = [&counter, &guard]() {
//        for (int i = 0; i < 10000000; ++i) {
////            guard.lock();
//            std::unique_lock<std::mutex> m(guard);
//            counter++;
//            counter--;
////            guard.unlock();
//        }
//    };
//
//    std::thread t1(thread_func);
//    std::thread t2(thread_func);
//    t1.join();
//    t2.join();
//
//    std::cout << counter << '\n';
//
    
    //2.
    //std::mutex guard;
//    std::atomic<int> counter(0);
//
//    auto thread_func = [&counter]() {
//        for (int i = 0; i < 10000000; ++i) {
//            //            guard.lock();
//
//            counter++;
//            counter--;
//            //            guard.unlock();
//        }
//    };
//
//    std::thread t1(thread_func);
//    std::thread t2(thread_func);
//    t1.join();
//    t2.join();
//
//    std::cout << counter << '\n';
    
//    //3.
//
//    atomic_counter counter;
//
//    auto thread_func = [&counter] () {
//        while (counter.value() < 100) {
//            std::this_thread::sleep_for(10ms);
//            counter.increment();
//        }
//    };
//
//    std::vector<std::thread> threads;
//    for (int i = 0; i < 4; ++i) {
//        threads.emplace_back(thread_func);
//    }
//    for (auto& thread : threads) {
//        thread.join();
//    }
//
//    std::cout << counter.value() << '\n';
    
#include <queue>
#include <mutex>
#include <thread>
#include <iostream>
#include <chrono>
#include <condition_variable>
    
    template <typename T>
    class blocking_queue {
    public:
        void add(T const& e) {
            std::unique_lock<std::mutex> lg(mutex);
            queue.push(e);
            //notify
            cv.notify_one();
        }
        
        T take() {
            std::unique_lock<std::mutex> lg(mutex);
          
            //wait
            cv.wait(lg, [this](){ return !queue.empty(); });
            auto out = std::move(queue.front()); queue.pop();
            return out;
        }
        
    private:
        std::queue<T> queue;
        std::mutex mutex;
        std::condition_variable cv;
    };
    
    int main() {
        using namespace std::chrono_literals;
        blocking_queue<int> queue;
        auto producer = [] (blocking_queue<int>& queue) {
            for (int i = 0; i < 100; ++i) {
                queue.add(i);
                std::this_thread::sleep_for(100ms);
            }
        };
        
        auto consumer = [] (blocking_queue<int>& queue) {
            while (true) {
                auto elem = queue.take();
                std::cout << elem << '\n';
            }
        };
        
        std::thread t1(producer, std::ref(queue));
        std::thread t2(consumer, std::ref(queue));
        
        t1.join();
        t2.join();
    }
    

