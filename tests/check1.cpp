#include "vk/client.hpp"
#include "catch.hpp"



SCENARIO("client must check connection using a token") {
    GIVEN("a valid token")
    {

        WHEN("initialize client")
        {
            Client client("");

            THEN("check_connection() must return true")
            {
                REQUIRE(client.check_connection());
            }
        }
    }
}
