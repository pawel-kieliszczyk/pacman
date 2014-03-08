#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Model/FruitField.hpp>

#include <Mocks/Presentation/BoardGraphicControllerMock.hpp>
#include <Mocks/Model/FruitMock.hpp>
#include <Mocks/Model/PacMock.hpp>


namespace GT = testing;


namespace Pacman
{
namespace Model
{
namespace Testing
{


MATCHER_P(MatchSmartPointer, p, "") { return arg.get() == p.get(); }
MATCHER_P(MatchMemoryAddress, address, "") { return &arg == address; }


struct FruitFieldTester : public GT::Test
{
    const unsigned row = 11u;
    const unsigned column = 22u;
    const unsigned maxNumberOfFruitsToEat = 2u;

    // mocks:
    std::shared_ptr<PacMock> pacMock =
            std::make_shared<GT::StrictMock<PacMock>>();
    std::shared_ptr<FruitMock> fruitMock =
            std::make_shared<GT::StrictMock<FruitMock>>();
    std::shared_ptr<Presentation::Testing::BoardGraphicControllerMock> boardGraphicControllerMock =
            std::make_shared<GT::StrictMock<Presentation::Testing::BoardGraphicControllerMock>>();

    // tested class:
    FruitField fruitField{row, column, maxNumberOfFruitsToEat};
};


TEST_F(FruitFieldTester, checksVisitability)
{
    EXPECT_TRUE(fruitField.isVisitable());
}


TEST_F(FruitFieldTester, visitsField)
{
    // no expectations

    // when and then
    fruitField.visit(*pacMock);
}


TEST_F(FruitFieldTester, showsFruitAndVisitsField)
{
    // when
    fruitField.showFruit(fruitMock);

    // expect
    EXPECT_CALL(*pacMock, eatFruit(MatchSmartPointer(fruitMock)));

    // then
    fruitField.visit(*pacMock);
}


TEST_F(FruitFieldTester, showsFruitAndVisitsFieldTwice)
{
    // when
    fruitField.showFruit(fruitMock);

    // expect
    EXPECT_CALL(*pacMock, eatFruit(MatchSmartPointer(fruitMock)));

    // then
    fruitField.visit(*pacMock); // first visit eats the fruit

    // no expectations
    fruitField.visit(*pacMock);
}


TEST_F(FruitFieldTester, showsAndHidesFruitAndVisitsField)
{
    // given
    fruitField.showFruit(fruitMock);

    // when
    fruitField.hideFruit();

    // no expectations

    // then
    fruitField.visit(*pacMock);
}


TEST_F(FruitFieldTester, exhaustAllFruitsToEat)
{
    // given
    fruitField.showFruit(fruitMock);

    // expect
    EXPECT_CALL(*pacMock, eatFruit(MatchSmartPointer(fruitMock)));

    // when and then
    fruitField.visit(*pacMock);


    // given
    fruitField.showFruit(fruitMock);

    // expect
    EXPECT_CALL(*pacMock, eatFruit(MatchSmartPointer(fruitMock)));

    // when and then
    fruitField.visit(*pacMock);


    // given
    fruitField.showFruit(fruitMock);

    // no expectations

    // when and then
    fruitField.visit(*pacMock);
}


TEST_F(FruitFieldTester, drawsField)
{
    // no expectations

    // when and then
    fruitField.draw(*boardGraphicControllerMock);
}


TEST_F(FruitFieldTester, showsFruitAndDrawsField)
{
    // given
    fruitField.showFruit(fruitMock);

    // expect
    EXPECT_CALL(*fruitMock, draw(row, column, MatchMemoryAddress(boardGraphicControllerMock.get())));

    // when and then
    fruitField.draw(*boardGraphicControllerMock);
}


TEST_F(FruitFieldTester, hidesFruitAndDrawsField)
{
    // given
    fruitField.showFruit(fruitMock);

    // when
    fruitField.hideFruit();

    // no expectations

    // when and then
    fruitField.draw(*boardGraphicControllerMock);
}


TEST_F(FruitFieldTester, resetsField)
{
    // given
    fruitField.showFruit(fruitMock);

    // when
    fruitField.reset();

    // no expectations

    // when and then
    fruitField.visit(*pacMock);
    fruitField.draw(*boardGraphicControllerMock);
}


} // namespace Testing
} // namespace Model
} // namespace Pacman
