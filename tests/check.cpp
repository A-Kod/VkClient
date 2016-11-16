
#include "vk/client.hpp"
#include "catch.hpp"

SCENARIO("client must check connection using a token") {
    GIVEN("an invalid token") {

        WHEN("initialize client") {
            Client client("bd505d23f9b60948f818637df858c8783df43e213eca9b8a76bbdde830193c821f3f08b8fc59c4525e3d");

            THEN("check_connection() must return false") {
                REQUIRE(!client.check_connection());
            }
        }
    }



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
