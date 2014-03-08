#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Model/CoinField.hpp>

#include <Mocks/Model/PacMock.hpp>
#include <Mocks/Presentation/BoardGraphicControllerMock.hpp>


namespace GT = testing;


namespace Pacman
{
namespace Model
{
namespace Testing
{


struct CoinFieldTester : public GT::Test
{
    void visitField(GT::StrictMock<PacMock>& pacMock)
    {
        // expect
        EXPECT_CALL(pacMock, eatCoin());

        // when and then
        coinField.visit(pacMock);
    }

    const unsigned x = 2u;
    const unsigned y = 3u;

    // tested class:
    CoinField coinField{x, y};
};


TEST_F(CoinFieldTester, checksVisitability)
{
    EXPECT_TRUE(coinField.isVisitable());
}


TEST_F(CoinFieldTester, visitsField)
{
    // given
    GT::StrictMock<PacMock> pacMock;

    // when and then
    visitField(pacMock);
}


TEST_F(CoinFieldTester, visitsAndDrawsField)
{
    // given
    GT::StrictMock<PacMock> pacMock;
    visitField(pacMock);

    GT::StrictMock<Presentation::Testing::BoardGraphicControllerMock> graphicControllerMock;

    // no mock expectations

    // then
    coinField.draw(graphicControllerMock);
}


TEST_F(CoinFieldTester, visitsFieldTwice)
{
    // given
    GT::StrictMock<PacMock> pacMock;
    visitField(pacMock);

    // no mock expectations

    // when and then
    coinField.visit(pacMock);
}


TEST_F(CoinFieldTester, drawsField)
{
    // given
    GT::StrictMock<Presentation::Testing::BoardGraphicControllerMock> graphicControllerMock;

    // expect
    EXPECT_CALL(graphicControllerMock, drawCoin(x, y));

    // when and then
    coinField.draw(graphicControllerMock);
}


TEST_F(CoinFieldTester, resetsField)
{
    // given
    GT::StrictMock<PacMock> pacMock;
    GT::StrictMock<Presentation::Testing::BoardGraphicControllerMock> graphicControllerMock;

    visitField(pacMock);

    // when
    coinField.reset();

    // expect
    EXPECT_CALL(graphicControllerMock, drawCoin(x, y));

    // when and then
    coinField.draw(graphicControllerMock);
}


} // namespace Testing
} // namespace Model
} // namespace Pacman
