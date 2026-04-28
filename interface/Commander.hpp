#ifndef COMMANDER_HPP
#define COMMANDER_HPP
#include <atomic>
#include <thread>
#include <mutex>
#include <queue>
#include <functional>
#include <windows.h>
#include <iostream>
#include <sstream>

namespace Objects {
    class Object;
}

class Commander {
public:
    Commander();
    ~Commander();
    bool isRunning();

    std::queue<std::function<void()>> g_CommandQueue;
    std::mutex g_CommandMutex;
private:
    std::thread m_Thread;
    std::atomic<bool> m_Running = true;

    void command();
};



#endif //COMMANDER_HPP
