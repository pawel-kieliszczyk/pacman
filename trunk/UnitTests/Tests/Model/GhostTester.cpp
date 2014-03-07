#include <memory>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Model/Ghost.hpp>

#include <Mocks/Model/BoardMock.hpp>
#include <Mocks/Model/GameModeManagerMock.hpp>
#include <Mocks/Model/PacMock.hpp>
#include <Mocks/Model/RandomDirectionSelectorMock.hpp>
#include <Mocks/Presentation/GhostGraphicControllerMock.hpp>


namespace GT = testing;


namespace Pacman
{
namespace Model
{
namespace Testing
{


struct GhostTester : public GT::Test
{
    GhostTester()
    {
        createGhost();
    }

    void createGhost()
    {
        EXPECT_CALL(*boardMock, getNumOfRows()).WillOnce(GT::Return(startingRow * 2));
        EXPECT_CALL(*boardMock, getNumOfColumns()).WillOnce(GT::Return(startingColumn * 2));

        const int pacsRow = 7;
        const int pacsColumn = 8;
        EXPECT_CALL(*pacMock, getCurrentRow()).WillOnce(GT::Return(pacsRow));
        EXPECT_CALL(*pacMock, getCurrentColumn()).WillOnce(GT::Return(pacsColumn));

        EXPECT_CALL(*boardMock, areInTheSameHole(startingRow, startingColumn, pacsRow, pacsColumn))
                .WillOnce(GT::Return(false));

        EXPECT_CALL(*boardMock, isVisitable(startingRow - 1, startingColumn)).WillOnce(GT::Return(true));
        EXPECT_CALL(*boardMock, isVisitable(startingRow + 1, startingColumn)).WillOnce(GT::Return(false));
        EXPECT_CALL(*boardMock, isVisitable(startingRow, startingColumn - 1)).WillOnce(GT::Return(false));
        EXPECT_CALL(*boardMock, isVisitable(startingRow, startingColumn + 1)).WillOnce(GT::Return(true));

        std::vector<Direction> directionsToVisitableFields{
                Direction::Up,
                Direction::Right};

        EXPECT_CALL(*randomDirectionSelectorMock, selectDirection(directionsToVisitableFields))
                .WillOnce(GT::Return(Direction::Right));

        ghost.reset(new Ghost(
                startingRow,
                startingColumn,
                moveResolution,
                color,
                boardMock,
                pacMock,
                gameModeManagerMock,
                randomDirectionSelectorMock,
                ghostGraphicControllerMock));
    }


    const int startingRow = 11;
    const int startingColumn = 22;
    const unsigned moveResolution = 3u;
    Model::Color color = Model::Color::Red;

    // mocks:
    std::shared_ptr<BoardMock> boardMock =
            std::make_shared<GT::StrictMock<BoardMock>>();
    std::shared_ptr<PacMock> pacMock =
            std::make_shared<GT::StrictMock<PacMock>>();
    std::shared_ptr<GameModeManagerMock> gameModeManagerMock =
            std::make_shared<GT::StrictMock<GameModeManagerMock>>();
    std::shared_ptr<RandomDirectionSelectorMock> randomDirectionSelectorMock =
            std::make_shared<GT::StrictMock<RandomDirectionSelectorMock>>();
    std::shared_ptr<Presentation::Testing::GhostGraphicControllerMock> ghostGraphicControllerMock =
            std::make_shared<GT::StrictMock<Presentation::Testing::GhostGraphicControllerMock>>();

    // tested class:
    std::unique_ptr<Ghost> ghost;
};


TEST_F(GhostTester, drawsGhost)
{
    // expect
    const unsigned currentStep = 0;
    const int nextRow = startingRow;
    const int nextColumn = startingColumn + 1;
    EXPECT_CALL(*gameModeManagerMock, getGameMode()).WillOnce(GT::Return(GameMode::Normal));
    EXPECT_CALL(*ghostGraphicControllerMock, drawNormalGhost(startingRow, startingColumn, nextRow, nextColumn, currentStep, moveResolution, color));

    // when and then
    ghost->draw();
}


TEST_F(GhostTester, drawsGhostInBigCoinMode)
{
    // expect
    const unsigned currentStep = 0;
    const int nextRow = startingRow;
    const int nextColumn = startingColumn + 1;
    EXPECT_CALL(*gameModeManagerMock, getGameMode()).WillOnce(GT::Return(GameMode::BigCoin));
    EXPECT_CALL(*ghostGraphicControllerMock, drawScaredGhost(startingRow, startingColumn, nextRow, nextColumn, currentStep, moveResolution, color));

    // when and then
    ghost->draw();
}


TEST_F(GhostTester, drawsGhostInBigCoinLastSecondsMode)
{
    // expect
    const unsigned currentStep = 0;
    const int nextRow = startingRow;
    const int nextColumn = startingColumn + 1;
    EXPECT_CALL(*gameModeManagerMock, getGameMode()).WillOnce(GT::Return(GameMode::BigCoinLastSeconds));
    EXPECT_CALL(*ghostGraphicControllerMock, drawLastSecondsScaredGhost(startingRow, startingColumn, nextRow, nextColumn, currentStep, moveResolution, color));

    // when and then
    ghost->draw();
}


TEST_F(GhostTester, movesGhost)
{
    // no expectations

    // when and then
    ghost->move();
}


TEST_F(GhostTester, movesAndDrawsGhost)
{
    // given
    ghost->move();

    // expect
    const unsigned currentStep = 1;
    const int nextRow = startingRow;
    const int nextColumn = startingColumn + 1;
    EXPECT_CALL(*gameModeManagerMock, getGameMode()).WillOnce(GT::Return(GameMode::Normal));
    EXPECT_CALL(*ghostGraphicControllerMock, drawNormalGhost(startingRow, startingColumn, nextRow, nextColumn, currentStep, moveResolution, color));

    // when and then
    ghost->draw();
}


TEST_F(GhostTester, getsGhostsCurrentXAndYWhenGhostIsMovingUp)
{
    // given
    const unsigned long rows = 3;
    const unsigned long cols = 3;

    EXPECT_CALL(*boardMock, getNumOfRows()).WillOnce(GT::Return(rows));
    EXPECT_CALL(*boardMock, getNumOfColumns()).WillOnce(GT::Return(cols));

    const int pacsRow = 0;
    const int pacsColumn = 2;
    EXPECT_CALL(*pacMock, getCurrentRow()).WillOnce(GT::Return(pacsRow));
    EXPECT_CALL(*pacMock, getCurrentColumn()).WillOnce(GT::Return(pacsColumn));

    EXPECT_CALL(*boardMock, areInTheSameHole(1, 2, pacsRow, pacsColumn))
            .WillOnce(GT::Return(true));

    // when
    Ghost g(1, 2, moveResolution, color, boardMock, pacMock, gameModeManagerMock, randomDirectionSelectorMock, ghostGraphicControllerMock);

    // then
    EXPECT_DOUBLE_EQ(2.0, g.getCurrentX());
    EXPECT_DOUBLE_EQ(1.0, g.getCurrentY());

    // when
    g.move();

    // then
    EXPECT_DOUBLE_EQ(2.0, g.getCurrentX());
    EXPECT_DOUBLE_EQ(2.0 / 3.0, g.getCurrentY());

    // when
    g.move();

    // then
    EXPECT_DOUBLE_EQ(2.0, g.getCurrentX());
    EXPECT_DOUBLE_EQ(1.0 / 3.0, g.getCurrentY());
}


TEST_F(GhostTester, getsGhostsCurrentXAndYWhenGhostIsMovingDown)
{
    // given
    const unsigned long rows = 3;
    const unsigned long cols = 3;

    EXPECT_CALL(*boardMock, getNumOfRows()).WillOnce(GT::Return(rows));
    EXPECT_CALL(*boardMock, getNumOfColumns()).WillOnce(GT::Return(cols));

    const int pacsRow = 2;
    const int pacsColumn = 2;
    EXPECT_CALL(*pacMock, getCurrentRow()).WillOnce(GT::Return(pacsRow));
    EXPECT_CALL(*pacMock, getCurrentColumn()).WillOnce(GT::Return(pacsColumn));

    EXPECT_CALL(*boardMock, areInTheSameHole(1, 2, pacsRow, pacsColumn))
            .WillOnce(GT::Return(true));

    // when
    Ghost g(1, 2, moveResolution, color, boardMock, pacMock, gameModeManagerMock, randomDirectionSelectorMock, ghostGraphicControllerMock);

    // then
    EXPECT_DOUBLE_EQ(2.0, g.getCurrentX());
    EXPECT_DOUBLE_EQ(1.0, g.getCurrentY());

    // when
    g.move();

    // then
    EXPECT_DOUBLE_EQ(2.0, g.getCurrentX());
    EXPECT_DOUBLE_EQ(4.0 / 3.0, g.getCurrentY());

    // when
    g.move();

    // then
    EXPECT_DOUBLE_EQ(2.0, g.getCurrentX());
    EXPECT_DOUBLE_EQ(5.0 / 3.0, g.getCurrentY());
}


TEST_F(GhostTester, getsGhostsCurrentXAndYWhenGhostIsMovingLeft)
{
    // given
    const unsigned long rows = 3;
    const unsigned long cols = 3;

    EXPECT_CALL(*boardMock, getNumOfRows()).WillOnce(GT::Return(rows));
    EXPECT_CALL(*boardMock, getNumOfColumns()).WillOnce(GT::Return(cols));

    const int pacsRow = 2;
    const int pacsColumn = 0;
    EXPECT_CALL(*pacMock, getCurrentRow()).WillOnce(GT::Return(pacsRow));
    EXPECT_CALL(*pacMock, getCurrentColumn()).WillOnce(GT::Return(pacsColumn));

    EXPECT_CALL(*boardMock, areInTheSameHole(2, 1, pacsRow, pacsColumn))
            .WillOnce(GT::Return(true));

    // when
    Ghost g(2, 1, moveResolution, color, boardMock, pacMock, gameModeManagerMock, randomDirectionSelectorMock, ghostGraphicControllerMock);

    // then
    EXPECT_DOUBLE_EQ(1.0, g.getCurrentX());
    EXPECT_DOUBLE_EQ(2.0, g.getCurrentY());

    // when
    g.move();

    // then
    EXPECT_DOUBLE_EQ(2.0 / 3.0, g.getCurrentX());
    EXPECT_DOUBLE_EQ(2.0, g.getCurrentY());

    // when
    g.move();

    // then
    EXPECT_DOUBLE_EQ(1.0 / 3.0, g.getCurrentX());
    EXPECT_DOUBLE_EQ(2.0, g.getCurrentY());
}


TEST_F(GhostTester, getsGhostsCurrentXAndYWhenGhostIsMovingRight)
{
    // given
    const unsigned long rows = 3;
    const unsigned long cols = 3;

    EXPECT_CALL(*boardMock, getNumOfRows()).WillOnce(GT::Return(rows));
    EXPECT_CALL(*boardMock, getNumOfColumns()).WillOnce(GT::Return(cols));

    const int pacsRow = 2;
    const int pacsColumn = 2;
    EXPECT_CALL(*pacMock, getCurrentRow()).WillOnce(GT::Return(pacsRow));
    EXPECT_CALL(*pacMock, getCurrentColumn()).WillOnce(GT::Return(pacsColumn));

    EXPECT_CALL(*boardMock, areInTheSameHole(2, 1, pacsRow, pacsColumn))
            .WillOnce(GT::Return(true));

    // when
    Ghost g(2, 1, moveResolution, color, boardMock, pacMock, gameModeManagerMock, randomDirectionSelectorMock, ghostGraphicControllerMock);

    // then
    EXPECT_DOUBLE_EQ(1.0, g.getCurrentX());
    EXPECT_DOUBLE_EQ(2.0, g.getCurrentY());

    // when
    g.move();

    // then
    EXPECT_DOUBLE_EQ(4.0 / 3.0, g.getCurrentX());
    EXPECT_DOUBLE_EQ(2.0, g.getCurrentY());

    // when
    g.move();

    // then
    EXPECT_DOUBLE_EQ(5.0 / 3.0, g.getCurrentX());
    EXPECT_DOUBLE_EQ(2.0, g.getCurrentY());
}


TEST_F(GhostTester, movesGhostToNextFieldWithoutCrossroadAndDrawsGhost)
{
    // given
    ghost->move();
    ghost->move();

    // expect
    const int currentRow = startingRow;
    const int currentColumn = startingColumn + 1;
    const int pacsRow = 7;
    const int pacsColumn = 8;

    EXPECT_CALL(*pacMock, getCurrentRow()).WillOnce(GT::Return(pacsRow));
    EXPECT_CALL(*pacMock, getCurrentColumn()).WillOnce(GT::Return(pacsColumn));

    EXPECT_CALL(*boardMock, areInTheSameHole(currentRow, currentColumn, pacsRow, pacsColumn))
            .WillOnce(GT::Return(false));

    EXPECT_CALL(*boardMock, isVisitable(currentRow - 1, currentColumn)).WillOnce(GT::Return(false));
    EXPECT_CALL(*boardMock, isVisitable(currentRow + 1, currentColumn)).WillOnce(GT::Return(false));
    EXPECT_CALL(*boardMock, isVisitable(currentRow, currentColumn - 1)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(currentRow, currentColumn + 1)).WillOnce(GT::Return(true));

    std::vector<Direction> directionsToVisitableFields{Direction::Right};

    EXPECT_CALL(*randomDirectionSelectorMock, selectDirection(directionsToVisitableFields))
            .WillOnce(GT::Return(Direction::Right));

    // when and then
    ghost->move();

    // expect
    const unsigned currentStep = 0;
    const int nextRow = currentRow;
    const int nextColumn = currentColumn + 1;
    EXPECT_CALL(*gameModeManagerMock, getGameMode()).WillOnce(GT::Return(GameMode::Normal));
    EXPECT_CALL(*ghostGraphicControllerMock, drawNormalGhost(currentRow, currentColumn, nextRow, nextColumn, currentStep, moveResolution, color));

    // when and then
    ghost->draw();
}


TEST_F(GhostTester, movesGhostToNextFieldWithFullCrossroadAndDrawsGhost)
{
    // given
    ghost->move();
    ghost->move();

    // expect
    const int currentRow = startingRow;
    const int currentColumn = startingColumn + 1;
    const int pacsRow = 7;
    const int pacsColumn = 8;

    EXPECT_CALL(*pacMock, getCurrentRow()).WillOnce(GT::Return(pacsRow));
    EXPECT_CALL(*pacMock, getCurrentColumn()).WillOnce(GT::Return(pacsColumn));

    EXPECT_CALL(*boardMock, areInTheSameHole(currentRow, currentColumn, pacsRow, pacsColumn))
            .WillOnce(GT::Return(false));

    EXPECT_CALL(*boardMock, isVisitable(currentRow - 1, currentColumn)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(currentRow + 1, currentColumn)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(currentRow, currentColumn - 1)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(currentRow, currentColumn + 1)).WillOnce(GT::Return(true));

    std::vector<Direction> directionsToVisitableFields{
            Direction::Up,
            Direction::Down,
            Direction::Right};

    EXPECT_CALL(*randomDirectionSelectorMock, selectDirection(directionsToVisitableFields))
            .WillOnce(GT::Return(Direction::Up));

    // when and then
    ghost->move();

    // expect
    const unsigned currentStep = 0;
    const int nextRow = currentRow - 1;
    const int nextColumn = currentColumn;
    EXPECT_CALL(*gameModeManagerMock, getGameMode()).WillOnce(GT::Return(GameMode::Normal));
    EXPECT_CALL(*ghostGraphicControllerMock, drawNormalGhost(currentRow, currentColumn, nextRow, nextColumn, currentStep, moveResolution, color));

    // when and then
    ghost->draw();
}


TEST_F(GhostTester, movesGhostToNextFieldWithTurnsAndDrawsGhost)
{
    // given
    ghost->move();
    ghost->move();

    // expect
    const int currentRow = startingRow;
    const int currentColumn = startingColumn + 1;
    const int pacsRow = 7;
    const int pacsColumn = 8;

    EXPECT_CALL(*pacMock, getCurrentRow()).WillOnce(GT::Return(pacsRow));
    EXPECT_CALL(*pacMock, getCurrentColumn()).WillOnce(GT::Return(pacsColumn));

    EXPECT_CALL(*boardMock, areInTheSameHole(currentRow, currentColumn, pacsRow, pacsColumn))
            .WillOnce(GT::Return(false));

    EXPECT_CALL(*boardMock, isVisitable(currentRow - 1, currentColumn)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(currentRow + 1, currentColumn)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(currentRow, currentColumn - 1)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(currentRow, currentColumn + 1)).WillOnce(GT::Return(false));

    std::vector<Direction> directionsToVisitableFields{
            Direction::Up,
            Direction::Down,
            Direction::Left};

    EXPECT_CALL(*randomDirectionSelectorMock, selectDirection(directionsToVisitableFields))
            .WillOnce(GT::Return(Direction::Left));

    // when and then
    ghost->move();

    // expect
    const unsigned currentStep = 0;
    const int nextRow = currentRow;
    const int nextColumn = currentColumn - 1;
    EXPECT_CALL(*gameModeManagerMock, getGameMode()).WillOnce(GT::Return(GameMode::Normal));
    EXPECT_CALL(*ghostGraphicControllerMock, drawNormalGhost(currentRow, currentColumn, nextRow, nextColumn, currentStep, moveResolution, color));

    // when and then
    ghost->draw();
}


TEST_F(GhostTester, movesGhostToBlindAlleyAndDrawsGhost)
{
    // given
    ghost->move();
    ghost->move();

    // expect
    const int currentRow = startingRow;
    const int currentColumn = startingColumn + 1;
    const int pacsRow = 7;
    const int pacsColumn = 8;

    EXPECT_CALL(*pacMock, getCurrentRow()).WillOnce(GT::Return(pacsRow));
    EXPECT_CALL(*pacMock, getCurrentColumn()).WillOnce(GT::Return(pacsColumn));

    EXPECT_CALL(*boardMock, areInTheSameHole(currentRow, currentColumn, pacsRow, pacsColumn))
            .WillOnce(GT::Return(false));

    EXPECT_CALL(*boardMock, isVisitable(currentRow - 1, currentColumn)).WillOnce(GT::Return(false));
    EXPECT_CALL(*boardMock, isVisitable(currentRow + 1, currentColumn)).WillOnce(GT::Return(false));
    EXPECT_CALL(*boardMock, isVisitable(currentRow, currentColumn - 1)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(currentRow, currentColumn + 1)).WillOnce(GT::Return(false));

    std::vector<Direction> directionsToVisitableFields{Direction::Left};

    EXPECT_CALL(*randomDirectionSelectorMock, selectDirection(directionsToVisitableFields))
            .WillOnce(GT::Return(Direction::Left));

    // when and then
    ghost->move();

    // expect
    const unsigned currentStep = 0;
    const int nextRow = currentRow;
    const int nextColumn = currentColumn - 1;
    EXPECT_CALL(*gameModeManagerMock, getGameMode()).WillOnce(GT::Return(GameMode::Normal));
    EXPECT_CALL(*ghostGraphicControllerMock, drawNormalGhost(currentRow, currentColumn, nextRow, nextColumn, currentStep, moveResolution, color));

    // when and then
    ghost->draw();
}


TEST_F(GhostTester, movesGhostOutsideLeftBoardsEdge)
{
    // given
    const unsigned long rows = 3;
    const unsigned long cols = 3;

    // expect
    EXPECT_CALL(*boardMock, getNumOfRows()).WillOnce(GT::Return(rows));
    EXPECT_CALL(*boardMock, getNumOfColumns()).WillOnce(GT::Return(cols));

    const int pacsRow = 7;
    const int pacsColumn = 8;
    EXPECT_CALL(*pacMock, getCurrentRow()).WillOnce(GT::Return(pacsRow));
    EXPECT_CALL(*pacMock, getCurrentColumn()).WillOnce(GT::Return(pacsColumn));

    EXPECT_CALL(*boardMock, areInTheSameHole(1, 0, pacsRow, pacsColumn))
            .WillOnce(GT::Return(false));

    EXPECT_CALL(*boardMock, isVisitable(0u, 0u)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(2u, 0u)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(1u, 2u)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(1u, 1u)).WillOnce(GT::Return(true));

    std::vector<Direction> directionsToVisitableFields{
            Direction::Up,
            Direction::Down,
            Direction::Left,
            Direction::Right};

    EXPECT_CALL(*randomDirectionSelectorMock, selectDirection(directionsToVisitableFields))
            .WillOnce(GT::Return(Direction::Left));

    // when and then
    Ghost g(1, 0, moveResolution, color, boardMock, pacMock, gameModeManagerMock, randomDirectionSelectorMock, ghostGraphicControllerMock);

    // given
    g.move();

    // expect
    const unsigned currentStep = 1;
    EXPECT_CALL(*gameModeManagerMock, getGameMode()).Times(2).WillRepeatedly(GT::Return(GameMode::Normal));
    EXPECT_CALL(*ghostGraphicControllerMock, drawNormalGhost(1, 0, 1, -1, currentStep, moveResolution, color));
    EXPECT_CALL(*ghostGraphicControllerMock, drawNormalGhost(1, 3, 1, 2, currentStep, moveResolution, color));

    // when and then
    g.draw();

    // given
    g.move();

    // expect
    EXPECT_CALL(*pacMock, getCurrentRow()).WillOnce(GT::Return(pacsRow));
    EXPECT_CALL(*pacMock, getCurrentColumn()).WillOnce(GT::Return(pacsColumn));

    EXPECT_CALL(*boardMock, areInTheSameHole(1, 2, pacsRow, pacsColumn))
            .WillOnce(GT::Return(false));

    EXPECT_CALL(*boardMock, isVisitable(0u, 2u)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(2u, 2u)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(1u, 1u)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(1u, 0u)).WillOnce(GT::Return(true));

    directionsToVisitableFields = {
            Direction::Up,
            Direction::Down,
            Direction::Left};

    EXPECT_CALL(*randomDirectionSelectorMock, selectDirection(directionsToVisitableFields))
            .WillOnce(GT::Return(Direction::Left));

    // when and then
    g.move();
}


TEST_F(GhostTester, movesGhostOutsideRightBoardsEdge)
{
    // given
    const unsigned long rows = 3;
    const unsigned long cols = 3;

    // expect
    EXPECT_CALL(*boardMock, getNumOfRows()).WillOnce(GT::Return(rows));
    EXPECT_CALL(*boardMock, getNumOfColumns()).WillOnce(GT::Return(cols));

    const int pacsRow = 7;
    const int pacsColumn = 8;
    EXPECT_CALL(*pacMock, getCurrentRow()).WillOnce(GT::Return(pacsRow));
    EXPECT_CALL(*pacMock, getCurrentColumn()).WillOnce(GT::Return(pacsColumn));

    EXPECT_CALL(*boardMock, areInTheSameHole(1, 2, pacsRow, pacsColumn))
            .WillOnce(GT::Return(false));

    EXPECT_CALL(*boardMock, isVisitable(0u, 2u)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(2u, 2u)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(1u, 1u)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(1u, 0u)).WillOnce(GT::Return(true));

    std::vector<Direction> directionsToVisitableFields{
            Direction::Up,
            Direction::Down,
            Direction::Left,
            Direction::Right};

    EXPECT_CALL(*randomDirectionSelectorMock, selectDirection(directionsToVisitableFields))
            .WillOnce(GT::Return(Direction::Right));

    // when and then
    Ghost g(1, 2, moveResolution, color, boardMock, pacMock, gameModeManagerMock, randomDirectionSelectorMock, ghostGraphicControllerMock);

    // given
    g.move();

    // expect
    const unsigned currentStep = 1;
    EXPECT_CALL(*gameModeManagerMock, getGameMode()).Times(2).WillRepeatedly(GT::Return(GameMode::Normal));
    EXPECT_CALL(*ghostGraphicControllerMock, drawNormalGhost(1, 2, 1, 3, currentStep, moveResolution, color));
    EXPECT_CALL(*ghostGraphicControllerMock, drawNormalGhost(1, -1, 1, 0, currentStep, moveResolution, color));

    // when and then
    g.draw();

    // given
    g.move();

    // expect
    EXPECT_CALL(*pacMock, getCurrentRow()).WillOnce(GT::Return(pacsRow));
    EXPECT_CALL(*pacMock, getCurrentColumn()).WillOnce(GT::Return(pacsColumn));

    EXPECT_CALL(*boardMock, areInTheSameHole(1, 0, pacsRow, pacsColumn))
            .WillOnce(GT::Return(false));

    EXPECT_CALL(*boardMock, isVisitable(0u, 0u)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(2u, 0u)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(1u, 2u)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(1u, 1u)).WillOnce(GT::Return(true));

    directionsToVisitableFields = {
            Direction::Up,
            Direction::Down,
            Direction::Right};

    EXPECT_CALL(*randomDirectionSelectorMock, selectDirection(directionsToVisitableFields))
            .WillOnce(GT::Return(Direction::Right));

    // when and then
    g.move();
}


TEST_F(GhostTester, movesGhostOutsideTopBoardsEdge)
{
    // given
    const unsigned long rows = 3;
    const unsigned long cols = 3;

    // expect
    EXPECT_CALL(*boardMock, getNumOfRows()).WillOnce(GT::Return(rows));
    EXPECT_CALL(*boardMock, getNumOfColumns()).WillOnce(GT::Return(cols));

    const int pacsRow = 7;
    const int pacsColumn = 8;
    EXPECT_CALL(*pacMock, getCurrentRow()).WillOnce(GT::Return(pacsRow));
    EXPECT_CALL(*pacMock, getCurrentColumn()).WillOnce(GT::Return(pacsColumn));

    EXPECT_CALL(*boardMock, areInTheSameHole(0, 1, pacsRow, pacsColumn))
            .WillOnce(GT::Return(false));

    EXPECT_CALL(*boardMock, isVisitable(2u, 1u)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(1u, 1u)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(0u, 0u)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(0u, 2u)).WillOnce(GT::Return(true));

    std::vector<Direction> directionsToVisitableFields{
            Direction::Up,
            Direction::Down,
            Direction::Left,
            Direction::Right};

    EXPECT_CALL(*randomDirectionSelectorMock, selectDirection(directionsToVisitableFields))
            .WillOnce(GT::Return(Direction::Up));

    // when and then
    Ghost g(0, 1, moveResolution, color, boardMock, pacMock, gameModeManagerMock, randomDirectionSelectorMock, ghostGraphicControllerMock);

    // given
    g.move();

    // expect
    const unsigned currentStep = 1;
    EXPECT_CALL(*gameModeManagerMock, getGameMode()).Times(2).WillRepeatedly(GT::Return(GameMode::Normal));
    EXPECT_CALL(*ghostGraphicControllerMock, drawNormalGhost(0, 1, -1, 1, currentStep, moveResolution, color));
    EXPECT_CALL(*ghostGraphicControllerMock, drawNormalGhost(3, 1, 2, 1, currentStep, moveResolution, color));

    // when and then
    g.draw();

    // given
    g.move();

    // expect
    EXPECT_CALL(*pacMock, getCurrentRow()).WillOnce(GT::Return(pacsRow));
    EXPECT_CALL(*pacMock, getCurrentColumn()).WillOnce(GT::Return(pacsColumn));

    EXPECT_CALL(*boardMock, areInTheSameHole(2, 1, pacsRow, pacsColumn))
            .WillOnce(GT::Return(false));

    EXPECT_CALL(*boardMock, isVisitable(1u, 1u)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(0u, 1u)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(2u, 0u)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(2u, 2u)).WillOnce(GT::Return(true));

    directionsToVisitableFields = {
            Direction::Up,
            Direction::Left,
            Direction::Right};

    EXPECT_CALL(*randomDirectionSelectorMock, selectDirection(directionsToVisitableFields))
            .WillOnce(GT::Return(Direction::Up));

    // when and then
    g.move();
}


TEST_F(GhostTester, movesGhostOutsideBottomBoardsEdge)
{
    // given
    const unsigned long rows = 3;
    const unsigned long cols = 3;

    // expect
    EXPECT_CALL(*boardMock, getNumOfRows()).WillOnce(GT::Return(rows));
    EXPECT_CALL(*boardMock, getNumOfColumns()).WillOnce(GT::Return(cols));

    const int pacsRow = 7;
    const int pacsColumn = 8;
    EXPECT_CALL(*pacMock, getCurrentRow()).WillOnce(GT::Return(pacsRow));
    EXPECT_CALL(*pacMock, getCurrentColumn()).WillOnce(GT::Return(pacsColumn));

    EXPECT_CALL(*boardMock, areInTheSameHole(2, 1, pacsRow, pacsColumn))
            .WillOnce(GT::Return(false));

    EXPECT_CALL(*boardMock, isVisitable(1u, 1u)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(0u, 1u)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(2u, 0u)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(2u, 2u)).WillOnce(GT::Return(true));

    std::vector<Direction> directionsToVisitableFields{
            Direction::Up,
            Direction::Down,
            Direction::Left,
            Direction::Right};

    EXPECT_CALL(*randomDirectionSelectorMock, selectDirection(directionsToVisitableFields))
            .WillOnce(GT::Return(Direction::Down));

    // when and then
    Ghost g(2, 1, moveResolution, color, boardMock, pacMock, gameModeManagerMock, randomDirectionSelectorMock, ghostGraphicControllerMock);

    // given
    g.move();

    // expect
    const unsigned currentStep = 1;
    EXPECT_CALL(*gameModeManagerMock, getGameMode()).Times(2).WillRepeatedly(GT::Return(GameMode::Normal));
    EXPECT_CALL(*ghostGraphicControllerMock, drawNormalGhost(2, 1, 3, 1, currentStep, moveResolution, color));
    EXPECT_CALL(*ghostGraphicControllerMock, drawNormalGhost(-1, 1, 0, 1, currentStep, moveResolution, color));

    // when and then
    g.draw();

    // given
    g.move();

    // expect
    EXPECT_CALL(*pacMock, getCurrentRow()).WillOnce(GT::Return(pacsRow));
    EXPECT_CALL(*pacMock, getCurrentColumn()).WillOnce(GT::Return(pacsColumn));

    EXPECT_CALL(*boardMock, areInTheSameHole(0, 1, pacsRow, pacsColumn))
            .WillOnce(GT::Return(false));

    EXPECT_CALL(*boardMock, isVisitable(2u, 1u)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(1u, 1u)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(0u, 0u)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(0u, 2u)).WillOnce(GT::Return(true));

    directionsToVisitableFields = {
            Direction::Down,
            Direction::Left,
            Direction::Right};

    EXPECT_CALL(*randomDirectionSelectorMock, selectDirection(directionsToVisitableFields))
            .WillOnce(GT::Return(Direction::Down));

    // when and then
    g.move();
}


TEST_F(GhostTester, createsGhostInTheSameHoleAsPac)
{
    // given
    const unsigned long rows = 3;
    const unsigned long cols = 3;

    // expect
    EXPECT_CALL(*boardMock, getNumOfRows()).WillOnce(GT::Return(rows));
    EXPECT_CALL(*boardMock, getNumOfColumns()).WillOnce(GT::Return(cols));

    const int pacsRow = 1;
    const int pacsColumn = 2;
    EXPECT_CALL(*pacMock, getCurrentRow()).WillOnce(GT::Return(pacsRow));
    EXPECT_CALL(*pacMock, getCurrentColumn()).WillOnce(GT::Return(pacsColumn));

    EXPECT_CALL(*boardMock, areInTheSameHole(1, 0, pacsRow, pacsColumn))
            .WillOnce(GT::Return(true));

    // when and then
    Ghost g(1, 0, moveResolution, color, boardMock, pacMock, gameModeManagerMock, randomDirectionSelectorMock, ghostGraphicControllerMock);

    // expect
    const unsigned currentStep = 0;
    EXPECT_CALL(*gameModeManagerMock, getGameMode()).WillOnce(GT::Return(GameMode::Normal));
    EXPECT_CALL(*ghostGraphicControllerMock, drawNormalGhost(1, 0, 1, 1, currentStep, moveResolution, color));

    // when and then
    g.draw();
}


TEST_F(GhostTester, movesGhostToNextFieldWherePacIsVisibleAndDrawsGhost)
{
    // given
    ghost->move();
    ghost->move();

    // expect
    const int currentRow = startingRow;
    const int currentColumn = startingColumn + 1;

    const int pacsRow = currentRow + 5;
    const int pacsColumn = currentColumn;
    EXPECT_CALL(*pacMock, getCurrentRow()).WillOnce(GT::Return(pacsRow));
    EXPECT_CALL(*pacMock, getCurrentColumn()).WillOnce(GT::Return(pacsColumn));

    EXPECT_CALL(*boardMock, areInTheSameHole(currentRow, currentColumn, pacsRow, pacsColumn))
            .WillOnce(GT::Return(true));

    EXPECT_CALL(*gameModeManagerMock, getGameMode()).WillOnce(GT::Return(GameMode::Normal));

    // when and then
    ghost->move();

    // expect
    const unsigned currentStep = 0;
    const int nextRow = currentRow + 1;
    const int nextColumn = currentColumn;
    EXPECT_CALL(*gameModeManagerMock, getGameMode()).WillOnce(GT::Return(GameMode::Normal));
    EXPECT_CALL(*ghostGraphicControllerMock, drawNormalGhost(currentRow, currentColumn, nextRow, nextColumn, currentStep, moveResolution, color));

    // when and then
    ghost->draw();
}


TEST_F(GhostTester, movesGhostInBigCoinModeToNextFieldWherePacIsVisibleAndDrawsGhost)
{
    // given
    ghost->move();
    ghost->move();

    // expect
    const int currentRow = startingRow;
    const int currentColumn = startingColumn + 1;

    const int pacsRow = currentRow + 5;
    const int pacsColumn = currentColumn;
    EXPECT_CALL(*pacMock, getCurrentRow()).WillOnce(GT::Return(pacsRow));
    EXPECT_CALL(*pacMock, getCurrentColumn()).WillOnce(GT::Return(pacsColumn));

    EXPECT_CALL(*boardMock, areInTheSameHole(currentRow, currentColumn, pacsRow, pacsColumn))
            .WillOnce(GT::Return(true));

    EXPECT_CALL(*gameModeManagerMock, getGameMode()).WillOnce(GT::Return(GameMode::BigCoin));

    EXPECT_CALL(*boardMock, isVisitable(currentRow - 1, currentColumn)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(currentRow, currentColumn - 1)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(currentRow, currentColumn + 1)).WillOnce(GT::Return(true));

    std::vector<Direction> directionsToRunAway{Direction::Up, Direction::Left, Direction::Right};

    EXPECT_CALL(*randomDirectionSelectorMock, selectDirection(directionsToRunAway)).WillOnce(GT::Return(Direction::Right));

    // when and then
    ghost->move();

    // expect
    const unsigned currentStep = 0;
    const int nextRow = currentRow;
    const int nextColumn = currentColumn + 1;
    EXPECT_CALL(*gameModeManagerMock, getGameMode()).WillOnce(GT::Return(GameMode::BigCoin));
    EXPECT_CALL(*ghostGraphicControllerMock, drawScaredGhost(currentRow, currentColumn, nextRow, nextColumn, currentStep, moveResolution, color));

    // when and then
    ghost->draw();
}


TEST_F(GhostTester, movesGhostInBigCoinLastSecondsModeToNextFieldWherePacIsVisibleAndDrawsGhost)
{
    // given
    ghost->move();
    ghost->move();

    // expect
    const int currentRow = startingRow;
    const int currentColumn = startingColumn + 1;

    const int pacsRow = currentRow + 5;
    const int pacsColumn = currentColumn;
    EXPECT_CALL(*pacMock, getCurrentRow()).WillOnce(GT::Return(pacsRow));
    EXPECT_CALL(*pacMock, getCurrentColumn()).WillOnce(GT::Return(pacsColumn));

    EXPECT_CALL(*boardMock, areInTheSameHole(currentRow, currentColumn, pacsRow, pacsColumn))
            .WillOnce(GT::Return(true));

    EXPECT_CALL(*gameModeManagerMock, getGameMode()).WillOnce(GT::Return(GameMode::BigCoinLastSeconds));

    EXPECT_CALL(*boardMock, isVisitable(currentRow - 1, currentColumn)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(currentRow, currentColumn - 1)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(currentRow, currentColumn + 1)).WillOnce(GT::Return(true));

    std::vector<Direction> directionsToRunAway{Direction::Up, Direction::Left, Direction::Right};

    EXPECT_CALL(*randomDirectionSelectorMock, selectDirection(directionsToRunAway)).WillOnce(GT::Return(Direction::Right));

    // when and then
    ghost->move();

    // expect
    const unsigned currentStep = 0;
    const int nextRow = currentRow;
    const int nextColumn = currentColumn + 1;
    EXPECT_CALL(*gameModeManagerMock, getGameMode()).WillOnce(GT::Return(GameMode::BigCoinLastSeconds));
    EXPECT_CALL(*ghostGraphicControllerMock, drawLastSecondsScaredGhost(currentRow, currentColumn, nextRow, nextColumn, currentStep, moveResolution, color));

    // when and then
    ghost->draw();
}


TEST_F(GhostTester, resetsGhost)
{
    // given
    ghost->move();

    // expect
    EXPECT_CALL(*boardMock, isVisitable(startingRow - 1, startingColumn)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(startingRow + 1, startingColumn)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(startingRow, startingColumn - 1)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(startingRow, startingColumn + 1)).WillOnce(GT::Return(false));

    std::vector<Direction> directionsToVisitableFields{
            Direction::Up,
            Direction::Down,
            Direction::Left};

    EXPECT_CALL(*randomDirectionSelectorMock, selectDirection(directionsToVisitableFields))
            .WillOnce(GT::Return(Direction::Down));

    // when and then
    ghost->reset();
}


TEST_F(GhostTester, resetsAndDrawsGhost)
{
    // given
    ghost->move();

    EXPECT_CALL(*boardMock, isVisitable(startingRow - 1, startingColumn)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(startingRow + 1, startingColumn)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(startingRow, startingColumn - 1)).WillOnce(GT::Return(true));
    EXPECT_CALL(*boardMock, isVisitable(startingRow, startingColumn + 1)).WillOnce(GT::Return(false));

    std::vector<Direction> directionsToVisitableFields{
            Direction::Up,
            Direction::Down,
            Direction::Left};

    EXPECT_CALL(*randomDirectionSelectorMock, selectDirection(directionsToVisitableFields))
            .WillOnce(GT::Return(Direction::Down));

    ghost->reset();

    // expect
    const unsigned currentStep = 0;
    const int nextRow = startingRow + 1;
    const int nextColumn = startingColumn;
    EXPECT_CALL(*gameModeManagerMock, getGameMode()).WillOnce(GT::Return(GameMode::Normal));
    EXPECT_CALL(*ghostGraphicControllerMock, drawNormalGhost(startingRow, startingColumn, nextRow, nextColumn, currentStep, moveResolution, color));

    // when and then
    ghost->draw();
}


} // namespace Testing
} // namespace Model
} // namespace Pacman
