#include <string>
#include <iostream>
#include <curl/curl.h>
#include <map>
//#include <boost/>
#include "json.hpp"

//https://oauth.vk.com/blank.html#access_token=bbd505d23f9b60948f818637df858c8783df43e213eca9b8a76bbdde830193c821f3f08b8fc59c4525e3d&expires_in=86400&user_id=123373332
//https://oauth.vk.com/blank.html#access_token=6a690f374224523aea1efc7b270873d4a963e8e615ba59c15f05e37b6cef426ea93f2a49005146d598a08&expires_in=86400&user_id=123373332
//https://oauth.vk.com/blank.html#access_token=265be38a0481daeee53ed10adb2807c42d7b6f76bc12907ae90306028f1fdec953ada593093fd1ab03d30&expires_in=86400&user_id=123373332


using json = nlohmann::json;

class Client
{
public:
 //   using dict_t = std::map<std::string, std::string>;
  //  Client(dict_t settings) : _settings(settings) {};
    Client (std::string token);

    // проверка соединения с сервисом
    auto check_connection() -> bool;

    // список всех друзей для выбранного id
    auto friend_list() -> void;

private:
    std:: string a_token;
  //  dict_t _settings;
    static auto write_data(char* buffer, size_t size, size_t nmemb, std::string* userp) -> size_t;

};

auto Client::write_data(char* buffer, size_t size, size_t nmemb, std::string* userp_) -> size_t
{
    std::string& userp = *userp_;
    size_t result = 0;

    if (userp.c_str())
    {
        userp.append(buffer, size * nmemb);
        result = size * nmemb;
    }

    return result;
}

// конструктор, принимающий token
Client::Client(std::string token)
{
    a_token = token;
}

// проверка соединения
auto Client::check_connection() -> bool
{

    CURL* curl = curl_easy_init();

    // если удалось создать дескриптор
    if(curl)
    {
        // прописываем настройки для авторизации через token
        std::string fields = "access_token=" + a_token + "&v=5.59";

        // строка для получения ответа от сервера
        std::string buffer ="";

        // адрес, по которому будем переходить
        //curl_easy_setopt(curl, CURLOPT_URL, "yandex.ru");
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.vk.com/method/account.getProfileInfo?");
        //curl_easy_setopt(curl, CURLOPT_URL, "https://api.vk.com/method/account.getInfo?");
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        //все данные, передаваемые в HTTP POST-запросе
        // передаем токен
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields.c_str());

        // указываем размер; до 2 гб, иначе CURLOPT_POSTFIELDSIZE_LARGE
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, fields.length());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        // отправляем запрос к серверу
        if (curl_easy_perform(curl) == CURLE_OK)
        {
            json server_answer = json::parse(buffer);
            json response = server_answer["response"];
            if (!response.empty())
            {
                curl_easy_cleanup(curl);
                return true;
            }
            else
            {
                json error = server_answer["error"];
                std::cout << "ERROR: " << error << std::endl;
                curl_easy_cleanup(curl);
                return false;
            }
        }
        std::cout << "Something wrong with easy performing!" << std::endl;
        curl_easy_cleanup(curl);
        return false;
    }
    std::cout << "Something wrong with initialization!" << std::endl;
    return false;

//            curl_easy_cleanup(curl);


//            long response_code;
//            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
//            std::cout <<std::endl<< "CODE:  "<<response_code << std::endl;

        }


    // если дошли до этой строчки - значит соединение не установлено
//    json error = server_answer["error"];
//    std::cout << "ERROR: " << error << std::endl;
//    curl_easy_cleanup(curl);
//    return false;



// список всех друзей для выбранного id
auto Client::friend_list() -> void
{
    CURL* curl = curl_easy_init();

    // если удалось создать дескриптор
    if(curl)
    {
        // прописываем настройки для авторизации через token
        std::string fields = "access_token=" + a_token + "&v=5.52";


        // строка для получения ответа от сервера
        char* buffer = "";

        // адрес, по которому будем переходить
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.vk.com/method/friends.getOnline?");

        // передаем токен
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields.c_str());

        // указываем размер
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, fields.length());

        // переход по ссылке выше
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);

        // отправлем запрос к серверу
        if (curl_easy_perform(curl) == CURLE_OK)
        {
            std:: cout << buffer << std::endl;
        }
    }

}


int main()
{
    Client client ("bbd505d23f9b60948f818637df858c8783df43e213eca9b8a76bbdde830193c821f3f08b8fc59c4525e3d"); //старый "просроченный" токен
    if (client.check_connection())
    {
        std::cout<<std::endl<<"Удалось подключиться"<<std::endl;
    }
    else
        std::cout<<std::endl<<"Не удалось подключиться"<<std::endl;
    std::cout<<"Список id друзей онлайн:"<<std::endl;
    client.friend_list();
    return 0;
}
