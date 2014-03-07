#include <memory>

#include <gtest/gtest.h>

#include <Model/GameModeManager.hpp>


namespace GT = testing;


namespace Pacman
{
namespace Model
{
namespace Testing
{


struct GameModeManagerTester : public GT::Test
{
    const unsigned bigCoinModeDuration = 3u;
    const unsigned bigCoinLastSecondsModeDuration = 2u;

    // tested class:
    GameModeManager gameModeManager{bigCoinModeDuration, bigCoinLastSecondsModeDuration};
};


TEST_F(GameModeManagerTester, checksGameModeOnFreshlyCreatedManager)
{
    // when and then
    EXPECT_EQ(GameMode::Normal, gameModeManager.getGameMode());
}


TEST_F(GameModeManagerTester, activatesAndExpiresBigCoinMode)
{
    // when
    gameModeManager.activateBigCoinMode();

    // then
    for(unsigned i = bigCoinModeDuration; i > 0u; --i)
    {
        EXPECT_EQ(GameMode::BigCoin, gameModeManager.getGameMode());
        gameModeManager.onClockTick();
    }
    for(unsigned i = bigCoinLastSecondsModeDuration; i > 0u; --i)
    {
        EXPECT_EQ(GameMode::BigCoinLastSeconds, gameModeManager.getGameMode());
        gameModeManager.onClockTick();
    }

    EXPECT_EQ(GameMode::Normal, gameModeManager.getGameMode());
}


TEST_F(GameModeManagerTester, activatesBigCoinModeDuringBigCoinMode)
{
    // given
    gameModeManager.activateBigCoinMode();
    gameModeManager.onClockTick();
    gameModeManager.onClockTick();
    EXPECT_EQ(GameMode::BigCoin, gameModeManager.getGameMode());

    // when
    gameModeManager.activateBigCoinMode();

    // then
    for(unsigned i = bigCoinModeDuration; i > 0u; --i)
    {
        EXPECT_EQ(GameMode::BigCoin, gameModeManager.getGameMode());
        gameModeManager.onClockTick();
    }
    for(unsigned i = bigCoinLastSecondsModeDuration; i > 0u; --i)
    {
        EXPECT_EQ(GameMode::BigCoinLastSeconds, gameModeManager.getGameMode());
        gameModeManager.onClockTick();
    }

    EXPECT_EQ(GameMode::Normal, gameModeManager.getGameMode());
}


TEST_F(GameModeManagerTester, activatesBigCoinModeDuringBigCoinLastSecondsMode)
{
    // given
    gameModeManager.activateBigCoinMode();
    gameModeManager.onClockTick();
    gameModeManager.onClockTick();
    gameModeManager.onClockTick();
    gameModeManager.onClockTick();
    EXPECT_EQ(GameMode::BigCoinLastSeconds, gameModeManager.getGameMode());

    // when
    gameModeManager.activateBigCoinMode();

    // then
    for(unsigned i = bigCoinModeDuration; i > 0u; --i)
    {
        EXPECT_EQ(GameMode::BigCoin, gameModeManager.getGameMode());
        gameModeManager.onClockTick();
    }
    for(unsigned i = bigCoinLastSecondsModeDuration; i > 0u; --i)
    {
        EXPECT_EQ(GameMode::BigCoinLastSeconds, gameModeManager.getGameMode());
        gameModeManager.onClockTick();
    }

    EXPECT_EQ(GameMode::Normal, gameModeManager.getGameMode());
}


TEST_F(GameModeManagerTester, resetsManagerInNormalMode)
{
    // when
    gameModeManager.reset();

    // then
    EXPECT_EQ(GameMode::Normal, gameModeManager.getGameMode());
}


TEST_F(GameModeManagerTester, resetsManagerInBigCoinMode)
{
    // given
    gameModeManager.activateBigCoinMode();
    ASSERT_EQ(GameMode::BigCoin, gameModeManager.getGameMode());

    // when
    gameModeManager.reset();

    // then
    EXPECT_EQ(GameMode::Normal, gameModeManager.getGameMode());
}


TEST_F(GameModeManagerTester, resetsManagerInBigCoinLastSecondsMode)
{
    // given
    gameModeManager.activateBigCoinMode();
    gameModeManager.onClockTick();
    gameModeManager.onClockTick();
    gameModeManager.onClockTick();
    gameModeManager.onClockTick();
    ASSERT_EQ(GameMode::BigCoinLastSeconds, gameModeManager.getGameMode());

    // when
    gameModeManager.reset();

    // then
    EXPECT_EQ(GameMode::Normal, gameModeManager.getGameMode());
}


} // namespace Testing
} // namespace Model
} // namespace Pacman
