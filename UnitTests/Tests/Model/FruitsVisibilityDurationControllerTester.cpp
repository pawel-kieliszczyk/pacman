#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Model/FruitsVisibilityDurationController.hpp>

#include <Mocks/Model/FruitVisibilityManagerMock.hpp>
#include <Mocks/Model/RandomNumberGeneratorMock.hpp>
#include <Mocks/Presentation/FruitGraphicControllerMock.hpp>


namespace GT = testing;


namespace Pacman
{
namespace Model
{
namespace Testing
{


struct FruitsVisibilityDurationControllerTester : public GT::Test
{
    void showFruit()
    {
        // given
        for(auto i = maxHiddenFruitDuration; i > 1; --i)
            controller.onClockTick();

        // expect
        EXPECT_CALL(*randomDurationGeneratorMock, next(0, 2)).WillOnce(GT::Return(0));
        EXPECT_CALL(*visibilityManagerMock, showFruit(GT::_));

        EXPECT_CALL(*randomDurationGeneratorMock, next(minShownFruitDuration, maxShownFruitDuration))
                .WillOnce(GT::Return(minShownFruitDuration));

        // when and then
        controller.onClockTick();
    }

    void hideFruit()
    {
        // given
        for(auto i = minShownFruitDuration; i > 1; --i)
            controller.onClockTick();

        // expect
        EXPECT_CALL(*visibilityManagerMock, hideFruit());

        EXPECT_CALL(*randomDurationGeneratorMock, next(minHiddenFruitDuration, maxHiddenFruitDuration))
                .WillOnce(GT::Return(minHiddenFruitDuration));

        // when and then
        controller.onClockTick();
    }

    const unsigned long minShownFruitDuration = 1;
    const unsigned long maxShownFruitDuration = 3;
    const unsigned long minHiddenFruitDuration = 5;
    const unsigned long maxHiddenFruitDuration = 7;

    // mocks:
    std::shared_ptr<RandomUnsignedLongGeneratorMock> randomDurationGeneratorMock =
            std::make_shared<GT::StrictMock<RandomUnsignedLongGeneratorMock>>();
    std::shared_ptr<FruitVisibilityManagerMock> visibilityManagerMock =
            std::make_shared<GT::StrictMock<FruitVisibilityManagerMock>>();
    std::shared_ptr<Presentation::Testing::FruitGraphicControllerMock> fruitGraphicControllerMock =
            std::make_shared<GT::NiceMock<Presentation::Testing::FruitGraphicControllerMock>>();

    // tested class:
    FruitsVisibilityDurationController controller{
            minShownFruitDuration,
            maxShownFruitDuration,
            minHiddenFruitDuration,
            maxHiddenFruitDuration,
            randomDurationGeneratorMock,
            visibilityManagerMock,
            fruitGraphicControllerMock};
};


TEST_F(FruitsVisibilityDurationControllerTester, showsFruit)
{
    // when and then
    showFruit();
}


TEST_F(FruitsVisibilityDurationControllerTester, hidesFruit)
{
    // given
    showFruit();

    // when and then
    hideFruit();
}


} // namespace Testing
} // namespace Model
} // namespace Pacman
