
#include "tests.hh"
#include <tplib/RuntimeConfiguration.hh>

#include <iostream>

int main(int argc, char *argv[])
{
    tplib::RuntimeConfiguration rc("./tests/RuntimeConfiguration.rc");

    if (rc.get("simple.name")
        .compare("simple value") != 0)
    {
        return TEST_FAIL;
    }

    if (rc.get("multi word name")
        .compare("some value") != 0)
    {
        return TEST_FAIL;
    }

    if (rc.get("dotted.name")
        .compare("some value") != 0)
    {
        return TEST_FAIL;
    }

    if (rc.get("name with")
        .compare("leading tab") != 0)
    {
        return TEST_FAIL;
    }

    if (rc.get("name that")
        .compare("has a # comment in its value") != 0)
    {
        return TEST_FAIL;
    }

    return TEST_PASS;
}

