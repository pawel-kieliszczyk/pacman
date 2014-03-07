#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Model/Cherry.hpp>

#include <Mocks/Presentation/BoardGraphicControllerMock.hpp>
#include <Mocks/Presentation/FruitGraphicControllerMock.hpp>


namespace GT = testing;


namespace Pacman
{
namespace Model
{
namespace Testing
{


struct CherryTester : public GT::Test
{
    // mocks:
    std::shared_ptr<Presentation::Testing::FruitGraphicControllerMock> fruitGraphicControllerMock =
            std::make_shared<GT::StrictMock<Presentation::Testing::FruitGraphicControllerMock>>();

    // tested class:
    Cherry cherry{fruitGraphicControllerMock};
};


TEST_F(CherryTester, drawsCherry)
{
    // given
    const unsigned fruitNumber = 1u;

    // expect
    EXPECT_CALL(*fruitGraphicControllerMock, drawCherry(fruitNumber));

    // when and then
    cherry.draw(fruitNumber);
}


TEST_F(CherryTester, drawsCherryUsingBoardBraphicController)
{
    // given
    const unsigned row = 11u;
    const unsigned column = 22u;
    GT::StrictMock<Presentation::Testing::BoardGraphicControllerMock> graphicController;

    // expect
    EXPECT_CALL(graphicController, drawCherry(row, column));

    // when and then
    cherry.draw(row, column, graphicController);
}


} // namespace Testing
} // namespace Model
} // namespace Pacman
