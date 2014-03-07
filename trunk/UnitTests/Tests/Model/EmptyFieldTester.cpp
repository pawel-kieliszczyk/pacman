#include <memory>

#include <gtest/gtest.h>

#include <Model/EmptyField.hpp>

#include <Mocks/Model/PacMock.hpp>
#include <Mocks/Presentation/BoardGraphicControllerMock.hpp>


namespace GT = testing;


namespace Pacman
{
namespace Model
{
namespace Testing
{


struct EmptyFieldTester : public GT::Test
{
    const unsigned x = 2u;
    const unsigned y = 3u;

    // tested class:
    EmptyField emptyField{x, y};
};


TEST_F(EmptyFieldTester, checksVisitability)
{
    EXPECT_TRUE(emptyField.isVisitable());
}


TEST_F(EmptyFieldTester, visitsField)
{
    // given
    GT::StrictMock<PacMock> pacMock;

    // no expectations

    // when and then
    emptyField.visit(pacMock);
}


TEST_F(EmptyFieldTester, drawsField)
{
    // given
    GT::StrictMock<Presentation::Testing::BoardGraphicControllerMock> graphicControllerMock;

    // no expectations

    // when and then
    emptyField.draw(graphicControllerMock);
}


TEST_F(EmptyFieldTester, resetsField)
{
    // no expectations

    // when and then
    emptyField.reset();
}


} // namespace Testing
} // namespace Model
} // namespace Pacman
