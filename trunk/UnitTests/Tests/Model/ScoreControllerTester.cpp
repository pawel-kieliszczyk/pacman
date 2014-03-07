#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Model/ScoreController.hpp>

#include <Mocks/Presentation/ScoreGraphicControllerMock.hpp>


namespace GT = testing;


namespace Pacman
{
namespace Model
{
namespace Testing
{


struct ScoreControllerTester : public GT::Test
{
    const unsigned coinScore = 10u;
    const unsigned bigCoinScore = 50u;
    const unsigned ghostScore = 100u;

    // mocks:
    std::shared_ptr<Presentation::Testing::ScoreGraphicControllerMock> scoreGraphicControllerMock =
            std::make_shared<GT::StrictMock<Presentation::Testing::ScoreGraphicControllerMock>>();

    // tested class:
    ScoreController scoreController{coinScore, bigCoinScore, ghostScore, scoreGraphicControllerMock};
};


TEST_F(ScoreControllerTester, drawsCoinScore)
{
    // when
    scoreController.addCoinScore();

    // expect
    EXPECT_CALL(*scoreGraphicControllerMock, draw(coinScore));

    // then
    scoreController.drawScore();

    // when
    scoreController.addCoinScore();

    // expect
    EXPECT_CALL(*scoreGraphicControllerMock, draw(2 * coinScore));

    // then
    scoreController.drawScore();
}


TEST_F(ScoreControllerTester, drawsBigCoinScore)
{
    // when
    scoreController.addBigCoinScore();

    // expect
    EXPECT_CALL(*scoreGraphicControllerMock, draw(bigCoinScore));

    // then
    scoreController.drawScore();

    // when
    scoreController.addBigCoinScore();

    // expect
    EXPECT_CALL(*scoreGraphicControllerMock, draw(2 * bigCoinScore));

    // then
    scoreController.drawScore();
}


TEST_F(ScoreControllerTester, drawsGhostScore)
{
    // when
    scoreController.addGhostScore();

    // expect
    EXPECT_CALL(*scoreGraphicControllerMock, draw(ghostScore));

    // then
    scoreController.drawScore();

    // when
    scoreController.addGhostScore();

    // expect
    EXPECT_CALL(*scoreGraphicControllerMock, draw(2 * ghostScore));

    // then
    scoreController.drawScore();
}


TEST_F(ScoreControllerTester, drawsMixedScore)
{
    // when
    scoreController.addCoinScore();
    scoreController.addBigCoinScore();
    scoreController.addGhostScore();

    // expect
    EXPECT_CALL(*scoreGraphicControllerMock, draw(coinScore + bigCoinScore + ghostScore));

    // then
    scoreController.drawScore();
}


TEST_F(ScoreControllerTester, resetsScore)
{
    // given
    scoreController.addCoinScore();

    // when
    scoreController.reset();

    // expect
    EXPECT_CALL(*scoreGraphicControllerMock, draw(0u));

    // then
    scoreController.drawScore();
}


} // namespace Testing
} // namespace Model
} // namespace Pacman
