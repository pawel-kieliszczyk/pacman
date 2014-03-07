#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Model/ClockTickNotifier.hpp>

#include <Mocks/Model/ClockTickListenerMock.hpp>


namespace GT = testing;


namespace Pacman
{
namespace Model
{
namespace Testing
{


struct ClockTickNotifierTester : public GT::Test
{
    // mocks:
    std::shared_ptr<ClockTickListenerMock> listenerMock1 = std::make_shared<GT::StrictMock<ClockTickListenerMock>>();
    std::shared_ptr<ClockTickListenerMock> listenerMock2 = std::make_shared<GT::StrictMock<ClockTickListenerMock>>();

    // tested class:
    ClockTickNotifier notifier{{listenerMock1, listenerMock2}};
};


TEST_F(ClockTickNotifierTester, ticks)
{
    // expect
    EXPECT_CALL(*listenerMock1, onClockTick());
    EXPECT_CALL(*listenerMock2, onClockTick());

    // when and then
    notifier.tick();
}


} // namespace Testing
} // namespace Model
} // namespace Pacman
