#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Model/Apple.hpp>

#include <Mocks/Presentation/BoardGraphicControllerMock.hpp>
#include <Mocks/Presentation/FruitGraphicControllerMock.hpp>


namespace GT = testing;


namespace Pacman
{
namespace Model
{
namespace Testing
{


struct AppleTester : public GT::Test
{
    // mocks:
    std::shared_ptr<Presentation::Testing::FruitGraphicControllerMock> fruitGraphicControllerMock =
            std::make_shared<GT::StrictMock<Presentation::Testing::FruitGraphicControllerMock>>();

    // tested class:
    Apple apple{fruitGraphicControllerMock};
};


TEST_F(AppleTester, drawsApple)
{
    // given
    const unsigned fruitNumber = 1u;

    // expect
    EXPECT_CALL(*fruitGraphicControllerMock, drawApple(fruitNumber));

    // when and then
    apple.draw(fruitNumber);
}


TEST_F(AppleTester, drawsAppleUsingBoardBraphicController)
{
    // given
    const unsigned row = 11u;
    const unsigned column = 22u;
    GT::StrictMock<Presentation::Testing::BoardGraphicControllerMock> graphicController;

    // expect
    EXPECT_CALL(graphicController, drawApple(row, column));

    // when and then
    apple.draw(row, column, graphicController);
}


} // namespace Testing
} // namespace Model
} // namespace Pacman
