#include "vk/threads.hpp"

Vk_Thread::Vk_Thread(std::vector<Document> l)
{
    lst = l;
}

auto Vk_Thread::print_thread(int id) -> void
{

   do
   {
       auto begin = std::chrono::high_resolution_clock::now();
       time_t  time_vk;
       time_vk=time(0);
       std::lock_guard<std::recursive_mutex> lk(m);
       //std::lock_guard<std::mutex> lk(m);
       if (counter < (lst.size()))
        {
       //     std::lock_guard<std::mutex> lk(m);
            std::cout<<std::endl<<"----------------------------------------------"<<std::endl<<"Document #"<<(counter+1)<<" "<<std::endl;
            if (flag)
            {
                std::cout<<"Start time:"<<puts(ctime(&time_vk))<<std::endl;
              //  std::cout<<start.count()<<std::endl;
                std::cout << "number_of_thread: " << id << std::endl;
                lst[counter].print_doc();
               // time_vk=time(0);
                std::cout<<"End time:"<<puts(ctime(&time_vk))<<std::endl;
                auto end = std::chrono::high_resolution_clock::now();
                std::cout<<"Duration time: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()<<" nanoseconds"<< std::endl;

            }
            else
            {
                lst[counter].print_doc();
            }

        }
        counter ++;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } while (counter < (lst.size()));

}

auto Vk_Thread::launch_threads(int n)->bool
{
    counter = 0;

    if (n<1 || n>std::thread::hardware_concurrency())
    {
        return false;
    }

    for (size_t i = 0; i < n; i++)
    {
        vk_vec.push_back(std::thread(&Vk_Thread::print_thread, this, i));
    }

    for (size_t i = 0; i < n; i++)
    {
        vk_vec[i].join();
    }
    return true;
}

auto Vk_Thread::user_input()->bool
{
    std::string input;
    int n;
    std::cin >> input;

    if (input == "get_docsv")
    {
        flag = true;
        std::cout << "Enter the number of threads:" << std::endl;
        std::cin >> n;
        return launch_threads(n);
    }
    if (input == "get_docs")
    {
        flag = false;
        std::cout << "Number of threads:" << std::endl;
        std::cin >> n;
        return launch_threads(n);
    }
    return false;

}

Vk_Thread::~Vk_Thread()
{

}
