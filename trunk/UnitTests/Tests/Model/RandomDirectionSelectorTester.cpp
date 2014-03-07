#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Model/RandomDirectionSelector.hpp>

#include <Mocks/Model/RandomNumberGeneratorMock.hpp>


namespace GT = testing;


namespace Pacman
{
namespace Model
{
namespace Testing
{


struct RandomDirectionSelectorTester : public GT::Test
{
    // mocks:
    std::shared_ptr<RandomUnsignedLongGeneratorMock> randomUnsignedLongGeneratorMock =
            std::make_shared<GT::StrictMock<RandomUnsignedLongGeneratorMock>>();

    // tested class:
    RandomDirectionSelector selector{randomUnsignedLongGeneratorMock};
};


TEST_F(RandomDirectionSelectorTester, selectsDirection)
{
    // given
    std::vector<Direction> directions{Direction::Up, Direction::Down, Direction::Left, Direction::Right};

    // expect
    const unsigned long min = 0;
    const unsigned long max = 3;
    EXPECT_CALL(*randomUnsignedLongGeneratorMock, next(min, max)).WillOnce(GT::Return(2));

    // when and then
    EXPECT_EQ(Direction::Left, selector.selectDirection(directions));

    // expect
    EXPECT_CALL(*randomUnsignedLongGeneratorMock, next(min, max)).WillOnce(GT::Return(0));

    // when and then
    EXPECT_EQ(Direction::Up, selector.selectDirection(directions));
}


} // namespace Testing
} // namespace Model
} // namespace Pacman
