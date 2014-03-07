#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Model/Orange.hpp>

#include <Mocks/Presentation/BoardGraphicControllerMock.hpp>
#include <Mocks/Presentation/FruitGraphicControllerMock.hpp>


namespace GT = testing;


namespace Pacman
{
namespace Model
{
namespace Testing
{


struct OrangeTester : public GT::Test
{
    // mocks:
    std::shared_ptr<Presentation::Testing::FruitGraphicControllerMock> fruitGraphicControllerMock =
            std::make_shared<GT::StrictMock<Presentation::Testing::FruitGraphicControllerMock>>();

    // tested class:
    Orange orange{fruitGraphicControllerMock};
};


TEST_F(OrangeTester, drawsOrange)
{
    // given
    const unsigned fruitNumber = 1u;

    // expect
    EXPECT_CALL(*fruitGraphicControllerMock, drawOrange(fruitNumber));

    // when and then
    orange.draw(fruitNumber);
}


TEST_F(OrangeTester, drawsOrangeUsingBoardBraphicController)
{
    // given
    const unsigned row = 11u;
    const unsigned column = 22u;
    GT::StrictMock<Presentation::Testing::BoardGraphicControllerMock> graphicController;

    // expect
    EXPECT_CALL(graphicController, drawOrange(row, column));

    // when and then
    orange.draw(row, column, graphicController);
}


} // namespace Testing
} // namespace Model
} // namespace Pacman
