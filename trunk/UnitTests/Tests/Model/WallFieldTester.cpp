#include <memory>

#include <gtest/gtest.h>

#include <Model/WallField.hpp>

#include <Mocks/Model/PacMock.hpp>
#include <Mocks/Presentation/BoardGraphicControllerMock.hpp>


namespace GT = testing;


namespace Pacman
{
namespace Model
{
namespace Testing
{


struct WallFieldTester : public GT::Test
{
    const unsigned x = 2u;
    const unsigned y = 3u;

    // tested class:
    WallField wallField{x, y};
};


TEST_F(WallFieldTester, checksVisitability)
{
    EXPECT_FALSE(wallField.isVisitable());
}


TEST_F(WallFieldTester, visitsField)
{
    // given
    GT::StrictMock<PacMock> pacMock;

    // no mock expectations

    // when and then
    ASSERT_THROW(wallField.visit(pacMock), std::logic_error);
}


TEST_F(WallFieldTester, drawsField)
{
    // given
    GT::StrictMock<Presentation::Testing::BoardGraphicControllerMock> graphicControllerMock;

    // expect
    EXPECT_CALL(graphicControllerMock, drawWall(x, y));

    // when and then
    wallField.draw(graphicControllerMock);
}


TEST_F(WallFieldTester, resetsField)
{
    // no expectations

    // when and then
    wallField.reset();
}


} // namespace Testing
} // namespace Model
} // namespace Pacman
