#include <string>
#include <iostream>
#include <curl/curl.h>

class Client
{
private:
    std:: string a_token;
//    static auto write_callback(char *data, size_t size, size_t nmemb, std::string &buff) -> size_t;
public:
    Client (std::string token);

    auto check_connection() -> bool;

    auto friend_list() -> void;

};

Client::Client(std::string token)
{
    a_token = token;
}

auto Client::check_connection() -> bool
{

    CURL* curl = curl_easy_init();

    if(curl)
    {
        std::string fields = "access_token=" + a_token + "&v=5.59";

        std::string buffer = "";

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.vk.com/method/account.getProfileInfo?");
        //curl_easy_setopt(curl, CURLOPT_URL, "https://api.vk.com/method/account.getInfo?");

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields.c_str());

        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, fields.length());

        if (curl_easy_perform(curl) == CURLE_OK)
        {
            //std::cout<<buffer;
            curl_easy_cleanup(curl);
            return true;


        }
    }
    curl_easy_cleanup(curl);
    return false;
}


auto Client::friend_list() -> void
{
    CURL* curl = curl_easy_init();

    if(curl)
    {
        std::string fields = "access_token=" + a_token + "&v=5.52";
        
        char* buffer = "";

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.vk.com/method/friends.getOnline?");

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields.c_str());

        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, fields.length());

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);

        if (curl_easy_perform(curl) == CURLE_OK)
        {
            std:: cout << buffer << std::endl;
        }
    }

}



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
