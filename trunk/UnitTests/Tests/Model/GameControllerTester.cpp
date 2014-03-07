#include <memory>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Model/GameController.hpp>

#include <Mocks/Model/BoardMock.hpp>
#include <Mocks/Model/ClockMock.hpp>
#include <Mocks/Model/CoinsCollectorMock.hpp>
#include <Mocks/Model/CollisionDetectorMock.hpp>
#include <Mocks/Model/FruitsCollectorMock.hpp>
#include <Mocks/Model/GameModeManagerMock.hpp>
#include <Mocks/Model/GhostMock.hpp>
#include <Mocks/Model/PacMock.hpp>
#include <Mocks/Model/PacsLifesControllerMock.hpp>
#include <Mocks/Model/ScoreControllerMock.hpp>
#include <Mocks/Presentation/WindowGraphicControllerMock.hpp>


namespace GT = testing;


namespace Pacman
{
namespace Model
{
namespace Testing
{


MATCHER_P(HasMemoryAddress, address, "") { return &arg == address; }


struct GameControllerTester : public GT::Test
{
    void startGame()
    {
        KeyPressed ret(Key::Return);
        gameController.process(ret);
    }

    void pauseStartedGame()
    {
        KeyPressed p(Key::P);
        gameController.process(p);
    }

    void resumePausedGame()
    {
        KeyPressed p(Key::P);
        gameController.process(p);
    }

    void movePacAndGhostsAndWinGame()
    {
        EXPECT_CALL(*gameModeManagerMock, getGameMode()).Times(GT::AtLeast(1)).WillRepeatedly(GT::Return(GameMode::Normal));

        EXPECT_CALL(*clockMock, tick());

        EXPECT_CALL(*pacMock, move()).Times(2);
        EXPECT_CALL(*ghostMock1, move()).Times(2);
        EXPECT_CALL(*ghostMock2, move()).Times(2);

        // collecting all coins means winning the game:
        EXPECT_CALL(*coinsCollectorMock, allCoinsCollected()).WillOnce(GT::Return(true));

        gameController.process(MoveRequested());
    }

    void movePacAndGhostsAndLoseGame()
    {
        EXPECT_CALL(*gameModeManagerMock, getGameMode()).Times(GT::AtLeast(1)).WillRepeatedly(GT::Return(GameMode::Normal));

        EXPECT_CALL(*clockMock, tick());

        EXPECT_CALL(*pacMock, move()).Times(2);
        EXPECT_CALL(*ghostMock1, move()).Times(2);
        EXPECT_CALL(*ghostMock2, move()).Times(2);

        EXPECT_CALL(*coinsCollectorMock, allCoinsCollected()).WillOnce(GT::Return(false));

        EXPECT_CALL(*collisionDetectorMock, areColliding(HasMemoryAddress(pacMock.get()), HasMemoryAddress(ghostMock1.get())))
                .WillOnce(GT::Return(false));
        EXPECT_CALL(*collisionDetectorMock, areColliding(HasMemoryAddress(pacMock.get()), HasMemoryAddress(ghostMock2.get())))
                .WillOnce(GT::Return(true));

        EXPECT_CALL(*pacsLifesControllerMock, consumeNextLife());
        EXPECT_CALL(*pacsLifesControllerMock, isDead()).WillOnce(GT::Return(true));

        gameController.process(MoveRequested());
    }

    // mocks:
    std::shared_ptr<BoardMock> boardMock =
            std::make_shared<GT::StrictMock<BoardMock>>();
    std::shared_ptr<PacMock> pacMock =
            std::make_shared<GT::StrictMock<PacMock>>();
    std::shared_ptr<GhostMock> ghostMock1 =
            std::make_shared<GT::StrictMock<GhostMock>>();
    std::shared_ptr<GhostMock> ghostMock2 =
            std::make_shared<GT::StrictMock<GhostMock>>();
    std::shared_ptr<ClockMock> clockMock =
            std::make_shared<GT::StrictMock<ClockMock>>();
    std::shared_ptr<GameModeManagerMock> gameModeManagerMock =
            std::make_shared<GT::StrictMock<GameModeManagerMock>>();
    std::shared_ptr<CoinsCollectorMock> coinsCollectorMock =
            std::make_shared<GT::StrictMock<CoinsCollectorMock>>();
    std::shared_ptr<FruitsCollectorMock> fruitsCollectorMock =
            std::make_shared<GT::StrictMock<FruitsCollectorMock>>();
    std::shared_ptr<CollisionDetectorMock> collisionDetectorMock =
            std::make_shared<GT::StrictMock<CollisionDetectorMock>>();
    std::shared_ptr<PacsLifesControllerMock> pacsLifesControllerMock =
            std::make_shared<GT::StrictMock<PacsLifesControllerMock>>();
    std::shared_ptr<ScoreControllerMock> scoreControllerMock =
            std::make_shared<GT::StrictMock<ScoreControllerMock>>();
    std::shared_ptr<Presentation::Testing::WindowGraphicControllerMock> windowGraphicControllerMock =
            std::make_shared<GT::StrictMock<Presentation::Testing::WindowGraphicControllerMock>>();

    // tested class:
    GameController gameController{
            boardMock,
            pacMock,
            std::vector<std::shared_ptr<IGhost>>{ghostMock1, ghostMock2},
            clockMock,
            gameModeManagerMock,
            coinsCollectorMock,
            fruitsCollectorMock,
            collisionDetectorMock,
            pacsLifesControllerMock,
            scoreControllerMock,
            windowGraphicControllerMock};
};


TEST_F(GameControllerTester, drawsGameBeforeStart)
{
    // expect
    GT::InSequence seq;

    EXPECT_CALL(*windowGraphicControllerMock, clearWindow());
    EXPECT_CALL(*boardMock, draw());
    EXPECT_CALL(*windowGraphicControllerMock, drawStoppedGameCurtain());

    // when and then
    gameController.process(DrawRequested());
}


TEST_F(GameControllerTester, movesPacAndGhostsBeforeStart)
{
    // no expectations

    // when and then
    gameController.process(MoveRequested());
}


TEST_F(GameControllerTester, startsGame)
{
    // when and then
    startGame();
}


TEST_F(GameControllerTester, startsAndDrawsGame)
{
    // given
    startGame();

    // expect
    GT::InSequence seq;

    EXPECT_CALL(*windowGraphicControllerMock, clearWindow());
    EXPECT_CALL(*boardMock, draw());
    EXPECT_CALL(*pacMock, draw());
    EXPECT_CALL(*ghostMock1, draw());
    EXPECT_CALL(*ghostMock2, draw());
    EXPECT_CALL(*pacsLifesControllerMock, drawPacsLifes());
    EXPECT_CALL(*scoreControllerMock, drawScore());
    EXPECT_CALL(*fruitsCollectorMock, drawFruits());

    // when and then
    gameController.process(DrawRequested());
}


TEST_F(GameControllerTester, startsGameAndMovesPacAndGhosts)
{
    // given
    startGame();

    // expect
    EXPECT_CALL(*gameModeManagerMock, getGameMode()).Times(GT::AtLeast(1)).WillRepeatedly(GT::Return(GameMode::Normal));

    EXPECT_CALL(*clockMock, tick());

    EXPECT_CALL(*pacMock, move()).Times(2);
    EXPECT_CALL(*ghostMock1, move()).Times(2);
    EXPECT_CALL(*ghostMock2, move()).Times(2);

    EXPECT_CALL(*coinsCollectorMock, allCoinsCollected()).WillOnce(GT::Return(false));

    EXPECT_CALL(*collisionDetectorMock, areColliding(HasMemoryAddress(pacMock.get()), HasMemoryAddress(ghostMock1.get())))
            .WillOnce(GT::Return(false));
    EXPECT_CALL(*collisionDetectorMock, areColliding(HasMemoryAddress(pacMock.get()), HasMemoryAddress(ghostMock2.get())))
            .WillOnce(GT::Return(false));

    // when and then
    gameController.process(MoveRequested());
}


TEST_F(GameControllerTester, startsGameAndPressesUpArrowKey)
{
    // given
    startGame();

    KeyPressed up(Key::UpArrow);

    // expect
    EXPECT_CALL(*pacMock, setDirection(Model::Direction::Up));

    // when and then
    gameController.process(up);
}


TEST_F(GameControllerTester, startsGameAndPressesDownArrowKey)
{
    // given
    startGame();

    KeyPressed down(Key::DownArrow);

    // expect
    EXPECT_CALL(*pacMock, setDirection(Model::Direction::Down));

    // when and then
    gameController.process(down);
}


TEST_F(GameControllerTester, startsGameAndPressesLeftArrowKey)
{
    // given
    startGame();

    KeyPressed left(Key::LeftArrow);

    // expect
    EXPECT_CALL(*pacMock, setDirection(Model::Direction::Left));

    // when and then
    gameController.process(left);
}


TEST_F(GameControllerTester, startsGameAndPressesRightArrowKey)
{
    // given
    startGame();

    KeyPressed right(Key::RightArrow);

    // expect
    EXPECT_CALL(*pacMock, setDirection(Model::Direction::Right));

    // when and then
    gameController.process(right);
}


TEST_F(GameControllerTester, pausesStartedGame)
{
    // given
    startGame();

    // when and then
    pauseStartedGame();
}


TEST_F(GameControllerTester, pausesStartedGameAndDrawsGame)
{
    // given
    startGame();
    pauseStartedGame();

    // no expectations
    GT::InSequence seq;

    EXPECT_CALL(*windowGraphicControllerMock, clearWindow());
    EXPECT_CALL(*boardMock, draw());
    EXPECT_CALL(*windowGraphicControllerMock, drawPausedGameCurtain());

    // when and then
    gameController.process(DrawRequested());
}


TEST_F(GameControllerTester, pausesStartedGameAndMovesPacAndGhosts)
{
    // given
    startGame();
    pauseStartedGame();

    // no expectations

    // when and then
    gameController.process(MoveRequested());
}


TEST_F(GameControllerTester, resumesPausedGame)
{
    // given
    startGame();
    pauseStartedGame();

    // when and then
    resumePausedGame();
}


TEST_F(GameControllerTester, resumesPausedGameAndDrawsGame)
{
    // given
    startGame();
    pauseStartedGame();
    resumePausedGame();

    // expect
    GT::InSequence seq;

    EXPECT_CALL(*windowGraphicControllerMock, clearWindow());
    EXPECT_CALL(*boardMock, draw());
    EXPECT_CALL(*pacMock, draw());
    EXPECT_CALL(*ghostMock1, draw());
    EXPECT_CALL(*ghostMock2, draw());
    EXPECT_CALL(*pacsLifesControllerMock, drawPacsLifes());
    EXPECT_CALL(*scoreControllerMock, drawScore());
    EXPECT_CALL(*fruitsCollectorMock, drawFruits());

    // when and then
    gameController.process(DrawRequested());
}


TEST_F(GameControllerTester, winsGame)
{
    // given
    startGame();

    // when and then
    movePacAndGhostsAndWinGame();
}


TEST_F(GameControllerTester, winsGameAndDrawsGame)
{
    // given
    startGame();
    movePacAndGhostsAndWinGame();

    // expect
    GT::InSequence seq;

    EXPECT_CALL(*windowGraphicControllerMock, clearWindow());
    EXPECT_CALL(*boardMock, draw());
    EXPECT_CALL(*pacMock, draw());
    EXPECT_CALL(*ghostMock1, draw());
    EXPECT_CALL(*ghostMock2, draw());
    EXPECT_CALL(*pacsLifesControllerMock, drawPacsLifes());
    EXPECT_CALL(*scoreControllerMock, drawScore());
    EXPECT_CALL(*fruitsCollectorMock, drawFruits());
    EXPECT_CALL(*windowGraphicControllerMock, drawWonGameCurtain());

    // when and then
    gameController.process(DrawRequested());
}


TEST_F(GameControllerTester, winsGameAndMovesPacAndGhosts)
{
    // given
    startGame();
    movePacAndGhostsAndWinGame();

    // no expectations

    // when and then
    gameController.process(MoveRequested());
}


TEST_F(GameControllerTester, movesPacToCollisionWithGhost)
{
    // given
    startGame();

    // when and then
    // big coin mode is inactive...
    EXPECT_CALL(*gameModeManagerMock, getGameMode()).Times(GT::AtLeast(1)).WillRepeatedly(GT::Return(GameMode::Normal));

    // ...tick clock...
    EXPECT_CALL(*clockMock, tick());

    // ...pac and ghosts should be moved...
    EXPECT_CALL(*pacMock, move()).Times(2);
    EXPECT_CALL(*ghostMock1, move()).Times(2);
    EXPECT_CALL(*ghostMock2, move()).Times(2);

    // ...coins are not collected...
    EXPECT_CALL(*coinsCollectorMock, allCoinsCollected()).WillOnce(GT::Return(false));

    // ...the seconds ghost catches Pac...
    EXPECT_CALL(*collisionDetectorMock, areColliding(HasMemoryAddress(pacMock.get()), HasMemoryAddress(ghostMock1.get())))
            .WillOnce(GT::Return(false));
    EXPECT_CALL(*collisionDetectorMock, areColliding(HasMemoryAddress(pacMock.get()), HasMemoryAddress(ghostMock2.get())))
            .WillOnce(GT::Return(true));

    // ...so another life should be consumed but Pac is still alive...
    EXPECT_CALL(*pacsLifesControllerMock, consumeNextLife());
    EXPECT_CALL(*pacsLifesControllerMock, isDead()).WillOnce(GT::Return(false));

    // ...pac and ghosts should return to their starting positions
    EXPECT_CALL(*pacMock, reset());
    EXPECT_CALL(*ghostMock1, reset());
    EXPECT_CALL(*ghostMock2, reset());

    gameController.process(MoveRequested());
}


TEST_F(GameControllerTester, movesPacToCollisionWithGhostInBigCoinMode)
{
    // given
    startGame();

    // when and then
    // big coin mode is active...
    EXPECT_CALL(*gameModeManagerMock, getGameMode()).Times(GT::AtLeast(1)).WillRepeatedly(GT::Return(GameMode::BigCoin));

    // ...tick clock...
    EXPECT_CALL(*clockMock, tick());

    // ...pac and ghosts should be moved...
    EXPECT_CALL(*pacMock, move()).Times(2);
    EXPECT_CALL(*ghostMock1, move());
    EXPECT_CALL(*ghostMock2, move());

    // ...coins are not collected...
    EXPECT_CALL(*coinsCollectorMock, allCoinsCollected()).WillOnce(GT::Return(false));

    // ...Pac catches the second ghost...
    EXPECT_CALL(*collisionDetectorMock, areColliding(HasMemoryAddress(pacMock.get()), HasMemoryAddress(ghostMock1.get())))
            .WillOnce(GT::Return(false));
    EXPECT_CALL(*collisionDetectorMock, areColliding(HasMemoryAddress(pacMock.get()), HasMemoryAddress(ghostMock2.get())))
            .WillOnce(GT::Return(true));

    // ...which should be reset...
    EXPECT_CALL(*ghostMock2, reset());

    // ..and the score should be properly increased
    EXPECT_CALL(*scoreControllerMock, addGhostScore());

    gameController.process(MoveRequested());
}


TEST_F(GameControllerTester, movesPacToCollisionWithGhostInBigCoinLastSecondsMode)
{
    // given
    startGame();

    // when and then
    // big coin mode is active...
    EXPECT_CALL(*gameModeManagerMock, getGameMode()).Times(GT::AtLeast(1)).WillRepeatedly(GT::Return(GameMode::BigCoinLastSeconds));

    // ...tick clock...
    EXPECT_CALL(*clockMock, tick());

    // ...pac and ghosts should be moved...
    EXPECT_CALL(*pacMock, move()).Times(2);
    EXPECT_CALL(*ghostMock1, move());
    EXPECT_CALL(*ghostMock2, move());

    // ...coins are not collected...
    EXPECT_CALL(*coinsCollectorMock, allCoinsCollected()).WillOnce(GT::Return(false));

    // ...Pac catches the second ghost...
    EXPECT_CALL(*collisionDetectorMock, areColliding(HasMemoryAddress(pacMock.get()), HasMemoryAddress(ghostMock1.get())))
            .WillOnce(GT::Return(false));
    EXPECT_CALL(*collisionDetectorMock, areColliding(HasMemoryAddress(pacMock.get()), HasMemoryAddress(ghostMock2.get())))
            .WillOnce(GT::Return(true));

    // ...which should be reset...
    EXPECT_CALL(*ghostMock2, reset());

    // ..and the score should be properly increased
    EXPECT_CALL(*scoreControllerMock, addGhostScore());

    gameController.process(MoveRequested());
}


TEST_F(GameControllerTester, losesGame)
{
    // given
    startGame();

    // when and then
    movePacAndGhostsAndLoseGame();
}


TEST_F(GameControllerTester, losesGameAndDrawsGame)
{
    // given
    startGame();
    movePacAndGhostsAndLoseGame();

    // expect
    GT::InSequence seq;

    EXPECT_CALL(*windowGraphicControllerMock, clearWindow());
    EXPECT_CALL(*boardMock, draw());
    EXPECT_CALL(*pacMock, draw());
    EXPECT_CALL(*ghostMock1, draw());
    EXPECT_CALL(*ghostMock2, draw());
    EXPECT_CALL(*pacsLifesControllerMock, drawPacsLifes());
    EXPECT_CALL(*scoreControllerMock, drawScore());
    EXPECT_CALL(*fruitsCollectorMock, drawFruits());
    EXPECT_CALL(*windowGraphicControllerMock, drawLostGameCurtain());

    // when and then
    gameController.process(DrawRequested());
}


TEST_F(GameControllerTester, losesGameAndMovesPacAndGhosts)
{
    // given
    startGame();
    movePacAndGhostsAndLoseGame();

    // no expectations

    // when and then
    gameController.process(MoveRequested());
}


TEST_F(GameControllerTester, winsAndResetsGame)
{
    // given
    startGame();
    movePacAndGhostsAndWinGame();

    EXPECT_CALL(*boardMock, reset());
    EXPECT_CALL(*pacMock, reset());
    EXPECT_CALL(*ghostMock1, reset());
    EXPECT_CALL(*ghostMock2, reset());
    EXPECT_CALL(*coinsCollectorMock, reset());
    EXPECT_CALL(*pacsLifesControllerMock, reset());
    EXPECT_CALL(*scoreControllerMock, reset());
    EXPECT_CALL(*fruitsCollectorMock, reset());
    EXPECT_CALL(*gameModeManagerMock, reset());

    // when and then
    KeyPressed ret(Key::Return);
    gameController.process(ret);
}


TEST_F(GameControllerTester, losesAndResetsGame)
{
    // given
    startGame();
    movePacAndGhostsAndLoseGame();

    EXPECT_CALL(*boardMock, reset());
    EXPECT_CALL(*pacMock, reset());
    EXPECT_CALL(*ghostMock1, reset());
    EXPECT_CALL(*ghostMock2, reset());
    EXPECT_CALL(*coinsCollectorMock, reset());
    EXPECT_CALL(*pacsLifesControllerMock, reset());
    EXPECT_CALL(*scoreControllerMock, reset());
    EXPECT_CALL(*fruitsCollectorMock, reset());
    EXPECT_CALL(*gameModeManagerMock, reset());

    // when and then
    KeyPressed ret(Key::Return);
    gameController.process(ret);
}


} // namespace Testing
} // namespace Model
} // namespace Pacman
