#ifndef VKCLIENT_THREADS_H
#define VKCLIENT_THREADS_H

#include <thread>
#include <future>
#include <chrono>
#include <vector>
#include <ctime>
#include "client.hpp"
class Vk_Thread
{
public:
    Vk_Thread(std::vector<Document>);

    auto print_thread(int id) -> void;

    auto launch_threads(int n)->bool;

    auto user_input()->bool;

    ~Vk_Thread();
private:
    int counter = 0;
    std::recursive_mutex m;
    //std::mutex m;
    bool flag;
    std::vector<Document> lst;
    std::vector<std::thread> vk_vec;

};
#endif //VKCLIENT_THREADS_H
