#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include "vk/client.hpp"
#include "vk/threads.hpp"
//#include "sources/client.cpp"

std::recursive_mutex m;

std::vector<Document> lst;

//auto print_thread() -> void
//{
//    //std::lock_guard<std::recursive_mutex> lk(m);
//    m.lock();
//    if (lst.size() > 0)
//    {
//
//        std::cout << "Pop[" << std::this_thread::get_id() << "] " ;
//        lst.front().print_doc();
//        std::cout<<std::endl;
//        lst.pop_front();
//    }
//    m.unlock();
//    // unlock mutex
//    std::this_thread::sleep_for(std::chrono::milliseconds(400));
//
//}


int main()
{
    std::cout<<std::endl;
    std::cout<<std::thread::hardware_concurrency()<<std::endl;
    std::cout<<std::endl;
    Client client ("7d10cec10d0b87df392c5aa0d1b13456591c6d0b1fa3b0a9ef2ed232360efc52b131b620b96d37a3c2c96&"); //старый "просроченный" токен
    if (client.check_connection())
    {
        std::cout<<std::endl<<"Удалось подключиться"<<std::endl;
        lst = client.get_docs();
        Vk_Thread th(lst);
        if (th.user_input())
        {
            std::cout << "all_threads_end" << std::endl;
        }
        else
        {
            std::cout << "error";
        }

    }
    else
        std::cout<<std::endl<<"Не удалось подключиться"<<std::endl;
    //std::cout<<"Список документов:"<<std::endl;
    //client.print_docs();

    return 0;
}


//std::recursive_mutex m;
//std::vector<int> vec;
//
//void push()
//{
//    for (int i = 0; i != 100; ++i)
//    {
//        //std::this_thread::sleep_for(std::chrono::milliseconds(500));
//        vec.push_back(i);
//        std::cout << i << " ";
//    }
//    std::cout << std::endl;
//}
//
//void pop()
//{
//    for (int i = 0; i != 50; ++i)
//    {
//        {
//            std::lock_guard<std::recursive_mutex> lk(m);
//            if (vec.size() > 0)
//            {
//                int val = vec.back();
//                vec.pop_back();
//                std::cout << "Pop[" << std::this_thread::get_id() << "] " << val << std::endl;
//            }
//        } // unlock mutex
//        std::this_thread::sleep_for(std::chrono::milliseconds(400));
//    }
//}
//
//int main()
//{
//    //create two threads
//    //std::thread push_(push);
//    push();
//    std::thread thread_pop_a(pop);
//    std::thread thread_pop_b(pop);
//    //if (push_.joinable())
//    //    push_.join();
//    if (thread_pop_a.joinable())
//        thread_pop_a.join();
//    if (thread_pop_b.joinable())
//        thread_pop_b.join();
//
//    return 0;
//}
