#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Model/CollisionDetector.hpp>

#include <Mocks/Model/GhostMock.hpp>
#include <Mocks/Model/PacMock.hpp>


namespace GT = testing;


namespace Pacman
{
namespace Model
{
namespace Testing
{


struct CollisionDetectorTester : public GT::Test
{
    const double distanceToCollide = 0.5;

    // mocks:
    std::shared_ptr<PacMock> pacMock = std::make_shared<GT::StrictMock<PacMock>>();
    std::shared_ptr<GhostMock> ghostMock = std::make_shared<GT::StrictMock<GhostMock>>();

    // tested class:
    CollisionDetector detector{distanceToCollide};
};


TEST_F(CollisionDetectorTester, testsCollidingPacAndGhost)
{
    // given
    const double x1 = 1.0;
    const double y1 = 1.0;

    const double x2 = 1.2;
    const double y2 = 1.2;

    // expect
    EXPECT_CALL(*pacMock, getCurrentX()).WillOnce(GT::Return(x1));
    EXPECT_CALL(*pacMock, getCurrentY()).WillOnce(GT::Return(y1));

    EXPECT_CALL(*ghostMock, getCurrentX()).WillOnce(GT::Return(x2));
    EXPECT_CALL(*ghostMock, getCurrentY()).WillOnce(GT::Return(y2));

    // when and then
    EXPECT_TRUE(detector.areColliding(*pacMock, *ghostMock));
}


TEST_F(CollisionDetectorTester, testsNonCollidingPacAndGhost)
{
    // given
    const double x1 = 1.0;
    const double y1 = 1.0;

    const double x2 = 2.0;
    const double y2 = 2.0;

    // expect
    EXPECT_CALL(*pacMock, getCurrentX()).WillOnce(GT::Return(x1));
    EXPECT_CALL(*pacMock, getCurrentY()).WillOnce(GT::Return(y1));

    EXPECT_CALL(*ghostMock, getCurrentX()).WillOnce(GT::Return(x2));
    EXPECT_CALL(*ghostMock, getCurrentY()).WillOnce(GT::Return(y2));

    // when and then
    EXPECT_FALSE(detector.areColliding(*pacMock, *ghostMock));
}


} // namespace Testing
} // namespace Model
} // namespace Pacman
