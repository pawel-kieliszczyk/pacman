#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Model/FruitsCollector.hpp>

#include <Mocks/Model/FruitMock.hpp>


namespace GT = testing;


namespace Pacman
{
namespace Model
{
namespace Testing
{


struct FruitsCollectorTester : public GT::Test
{
    // mocks:
    std::shared_ptr<FruitMock> fruitMock0 = std::make_shared<GT::StrictMock<FruitMock>>();
    std::shared_ptr<FruitMock> fruitMock1 = std::make_shared<GT::StrictMock<FruitMock>>();
    std::shared_ptr<FruitMock> fruitMock2 = std::make_shared<GT::StrictMock<FruitMock>>();

    // tested class:
    FruitsCollector fruitsCollector;
};


TEST_F(FruitsCollectorTester, collectsAndDrawsFruits)
{
    // given
    fruitsCollector.collectFruit(fruitMock0);
    fruitsCollector.collectFruit(fruitMock1);
    fruitsCollector.collectFruit(fruitMock2);

    // expect
    EXPECT_CALL(*fruitMock0, draw(0u));
    EXPECT_CALL(*fruitMock1, draw(1u));
    EXPECT_CALL(*fruitMock2, draw(2u));

    // when and then
    fruitsCollector.drawFruits();
}


TEST_F(FruitsCollectorTester, resetsCollector)
{
    // given
    fruitsCollector.collectFruit(fruitMock0);
    fruitsCollector.collectFruit(fruitMock1);
    fruitsCollector.collectFruit(fruitMock2);

    // when
    fruitsCollector.reset();

    // no expectations

    // then
    fruitsCollector.drawFruits();
}


} // namespace Testing
} // namespace Model
} // namespace Pacman
