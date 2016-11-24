#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <vk/client.hpp>
#include <vk/threads.hpp>
//#include "sources/client.cpp"

std::vector<Document> lst;

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
    return 0;
}

