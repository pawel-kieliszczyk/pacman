#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Model/BigCoinField.hpp>

#include <Mocks/Model/PacMock.hpp>
#include <Mocks/Presentation/BoardGraphicControllerMock.hpp>


namespace GT = testing;


namespace Pacman
{
namespace Model
{
namespace Testing
{


struct BigCoinFieldTester : public GT::Test
{
    void visitField(GT::StrictMock<PacMock>& pacMock)
    {
        // expect
        EXPECT_CALL(pacMock, eatBigCoin());

        // when and then
        bigCoinField.visit(pacMock);
    }

    const unsigned x = 2u;
    const unsigned y = 3u;

    // tested class:
    BigCoinField bigCoinField{x, y};
};


TEST_F(BigCoinFieldTester, checksVisitability)
{
    EXPECT_TRUE(bigCoinField.isVisitable());
}


TEST_F(BigCoinFieldTester, visitsField)
{
    // given
    GT::StrictMock<PacMock> pacMock;

    // when and then
    visitField(pacMock);
}


TEST_F(BigCoinFieldTester, visitsAndDrawsField)
{
    // given
    GT::StrictMock<PacMock> pacMock;
    visitField(pacMock);

    GT::StrictMock<Presentation::Testing::BoardGraphicControllerMock> graphicControllerMock;

    // no mock expectations

    // then
    bigCoinField.draw(graphicControllerMock);
}


TEST_F(BigCoinFieldTester, visitsFieldTwice)
{
    // given
    GT::StrictMock<PacMock> pacMock;
    visitField(pacMock);

    // no mock expectations

    // when and then
    bigCoinField.visit(pacMock);
}


TEST_F(BigCoinFieldTester, drawsField)
{
    // given
    GT::StrictMock<Presentation::Testing::BoardGraphicControllerMock> graphicControllerMock;

    // expect
    EXPECT_CALL(graphicControllerMock, drawBigCoin(x, y));

    // when and then
    bigCoinField.draw(graphicControllerMock);
}


TEST_F(BigCoinFieldTester, resetsField)
{
    // given
    GT::StrictMock<PacMock> pacMock;
    GT::StrictMock<Presentation::Testing::BoardGraphicControllerMock> graphicControllerMock;

    visitField(pacMock);

    // when
    bigCoinField.reset();

    // expect
    EXPECT_CALL(graphicControllerMock, drawBigCoin(x, y));

    // when and then
    bigCoinField.draw(graphicControllerMock);
}


} // namespace Testing
} // namespace Model
} // namespace Pacman
