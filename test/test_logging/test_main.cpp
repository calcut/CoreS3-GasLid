#include <gtest/gtest.h>
#include <Arduino.h>

#ifdef WOKWI
#include "hal_wokwi.h"
#else
#include "hal_coreS3.h"
#endif

#include "rtos_tasks.h"

TEST(DummyTest, ShouldPass)
{
    EXPECT_EQ(1, 1);
}

TEST(HALTest, Should_print_error_log_messages_at_all_levels)
{
    hal_setup();
}


void setup()
{
    // should be the same value as for the `test_speed` option in "platformio.ini"
    // default value is test_speed=115200
    Serial.begin(115200);

    ::testing::InitGoogleTest();
    // if you plan to use GMock, replace the line above with
    // ::testing::InitGoogleMock();

    // Run tests
    if (RUN_ALL_TESTS())
    ;

    // sleep for 1 sec
    delay(1000);
}

void loop(){}