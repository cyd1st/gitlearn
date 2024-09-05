#include <iostream>
#include "../include/animal.h"
#include "gtest/gtest.h"

TEST(DogTest, SoundTest) {
    Dog dog;
    // dog.sound();
    std::ostringstream output;
    std::streambuf* previousCoutBuffer = std::cout.rdbuf(output.rdbuf());
    dog.sound();
    std::cout.rdbuf(previousCoutBuffer);
    ASSERT_EQ(output.str(), "Dog sound\n");
}

TEST(DogTest, LegsTest) {
    Dog dog;
    ASSERT_EQ(dog.getLegs(), 4);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}