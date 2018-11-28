#include <catch/catch.hpp>
#include <util/util.h>

using namespace util;

namespace tests {

    TEST_CASE("Test default environment variables", "[util]") {
        std::string key = "JUNK_VAR";

        // Sanity check for null pointer when env var not set
        char const *val = getenv(key.c_str());
        REQUIRE(val == nullptr);

        REQUIRE(getEnvVar(key, "blah") == "blah");
    }

    TEST_CASE("Test valid environment variables", "[util]") {
        std::string actual = getEnvVar("LANGUAGE", "blah");

        std::string expectedA("en_GB:en");
        std::string expectedB("en_GB:utf8");

        bool isEqual = (actual == expectedA) || (actual == expectedB);
        REQUIRE(isEqual);
    }

    TEST_CASE("Test empty environment variables", "[util]") {
        util::unsetEnvVar("MY_VAR");

        // Sanity check for empty string when env var set to empty
        char *currentValue = getenv("MY_VAR");
        REQUIRE(currentValue == nullptr);

        REQUIRE(getEnvVar("MY_VAR", "alpha") == "alpha");
    }

    TEST_CASE("Test default system config initialisation", "[util]") {
        SystemConfig conf;

        REQUIRE(conf.prewarm_target == 20);
        REQUIRE(conf.max_queue_ratio == 4);
        REQUIRE(conf.max_workers_per_function == 10);

        REQUIRE(conf.bound_timeout == 30);
        REQUIRE(conf.unbound_timeout == 240);
    }

    TEST_CASE("Test overriding system config initialisation", "[util]") {
        setEnvVar("PREWARM_TARGET", "9999");
        setEnvVar("MAX_QUEUE_RATIO", "8888");
        setEnvVar("MAX_WORKERS_PER_FUNCTION", "7777");

        setEnvVar("BOUND_TIMEOUT", "6666");
        setEnvVar("UNBOUND_TIMEOUT", "5555");

        SystemConfig conf;
        REQUIRE(conf.prewarm_target == 9999);
        REQUIRE(conf.max_queue_ratio == 8888);
        REQUIRE(conf.max_workers_per_function == 7777);

        REQUIRE(conf.bound_timeout == 6666);
        REQUIRE(conf.unbound_timeout == 5555);

        util::unsetEnvVar("PREWARM_TARGET");
        util::unsetEnvVar("MAX_QUEUE_RATIO");
        util::unsetEnvVar("MAX_WORKERS_PER_FUNCTION");

        util::unsetEnvVar("BOUND_TIMEOUT");
        util::unsetEnvVar("UNBOUND_TIMEOUT");
    }
}