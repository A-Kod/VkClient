#include <string>
#include <iostream>
#include <curl/curl.h>
#include "../sources/client.cpp"

int main()
{
    Client client ("6a690f374224523aea1efc7b270873d4a963e8e615ba59c15f05e37b6cef426ea93f2a49005146d598a08"); //старый "просроченный" токен
    if (client.check_connection())
    {
        std::cout<<std::endl<<"Удалось подключиться"<<std::endl;
    }
    else
        std::cout<<std::endl<<" Не удалось подключиться"<<std::endl;
    std::cout<<"Список друзей онлайн:"<<std::endl;
    client.friend_list();
    return 0;
}
