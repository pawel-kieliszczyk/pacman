#include <gtest/gtest.h>

#include <Model/GameControllerEvents.hpp>


namespace GT = testing;


namespace Pacman
{
namespace Model
{
namespace Testing
{


class GameControllerEventsTester : public GT::Test
{
};


TEST_F(GameControllerEventsTester, getsPressedKey)
{
    // given
    KeyPressed upArrowKeyPressed(Key::UpArrow);
    KeyPressed enterKeyPressed(Key::Return);

    // when and then
    EXPECT_EQ(Key::UpArrow, upArrowKeyPressed.getKey());
    EXPECT_EQ(Key::Return, enterKeyPressed.getKey());
}


TEST_F(GameControllerEventsTester, comparesKeyPressedEvents)
{
    // given
    KeyPressed leftArrowKeyPressed1(Key::LeftArrow);
    KeyPressed leftArrowKeyPressed2(Key::LeftArrow);
    KeyPressed rightArrowKeyPressed(Key::RightArrow);

    // when and then
    EXPECT_EQ(leftArrowKeyPressed1, leftArrowKeyPressed2);
    EXPECT_TRUE(leftArrowKeyPressed1 == leftArrowKeyPressed2);
    EXPECT_FALSE(leftArrowKeyPressed1 == rightArrowKeyPressed);
}


TEST_F(GameControllerEventsTester, comparesMoveRequestedEvents)
{
    // given
    MoveRequested mr1;
    MoveRequested mr2;

    // when and then
    EXPECT_EQ(mr1, mr2);
}


TEST_F(GameControllerEventsTester, comparesDrawRequestedEvents)
{
    // given
    DrawRequested dr1;
    DrawRequested dr2;

    // when and then
    EXPECT_EQ(dr1, dr2);
}


} // namespace Testing
} // namespace Model
} // namespace Pacman
