#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <vk/client.hpp>
#include <vk/threads.hpp>
#include "../client.cpp"
#include "../threads.cpp"

std::vector<Document> lst;

int main()
{
    std::cout<<std::endl;
    std::cout<<std::thread::hardware_concurrency()<<std::endl;
    std::cout<<std::endl;
    Client client (""); //старый "просроченный" токен
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
    return 0;
}

