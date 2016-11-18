#include <iostream>
#include "vk/client.hpp"
//#include "sources/client.cpp"


int main()
{
    Client client ("a1cf532920c3843b7f17b445e139d7419a110173937db90d1536142290715dccd49a794f1adc75dc0fcfd"); //старый "просроченный" токен
    if (client.check_connection())
    {
        std::cout<<std::endl<<"Удалось подключиться"<<std::endl;
    }
    else
        std::cout<<std::endl<<"Не удалось подключиться"<<std::endl;
    std::cout<<"Список документов:"<<std::endl;
    client.print_docs();
    return 0;
}
