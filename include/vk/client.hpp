#ifndef VKONT_CLIENT_H
#define VKONT_CLIENT_H
#include <string>
#include <iostream>
#include <list>
#include <curl/curl.h>
#include "json.hpp"

using json = nlohmann::json;

struct Document
{
    uint32_t id = 0;
    std::string title = "";
    std::string url = "";
    uint32_t size = 0;

    auto print_doc() -> void
    {
        std::cout<< "ID: " << id << std::endl;
        std::cout<< "TITLE: " << title << std::endl;
        std::cout<< "URL: " << url << std::endl;
        std::cout<< "SIZE: " << size << std::endl;
    }

};


class Client
{
public:
    Client (std::string token);

    // проверка соединения с сервисом
    auto check_connection() -> bool;

    // список всех друзей для выбранного id
    auto get_docs() ->  std::list<Document>;

    auto print_docs() -> void;

private:
    std:: string a_token;
    static auto write_data(char* buffer, size_t size, size_t nmemb, std::string* userp) -> size_t;

};


#endif //VKONT_CLIENT_H

//5688332

//https://oauth.vk.com/blank.html#access_token=90be8cecdd94e266ece912fae740d606d24fa57f5fc93609b5a189123cb913346182579a6ed6e593270f0&expires_in=86400&user_id=123373332
