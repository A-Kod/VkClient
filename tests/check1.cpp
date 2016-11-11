SCENARIO("client must check connection using a token") {
    GIVEN("a valid token")
    {

        WHEN("initialize client")
        {
            Client client("353651d3df30e78c2f3daeef244865daeda1fdd20845c3d9a359a772460992379520524cb8f1dd2d68348");

            THEN("check_connection() must return true")
            {
                REQUIRE(client.check_connection());
            }
        }
    }
}
