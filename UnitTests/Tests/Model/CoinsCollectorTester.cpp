#include <memory>

#include <gtest/gtest.h>

#include <Model/CoinsCollector.hpp>


namespace GT = testing;


namespace Pacman
{
namespace Model
{
namespace Testing
{


struct CoinsCollectorTester : public GT::Test
{
    void collectAllCoins()
    {
        // given
        EXPECT_FALSE(collector.allCoinsCollected());

        // when
        for(unsigned i = INITIAL_NUM_OF_COINS; i > 0; --i)
        {
            EXPECT_FALSE(collector.allCoinsCollected());
            collector.collectNextCoin();
        }

        // then
        EXPECT_TRUE(collector.allCoinsCollected());
    }

    const unsigned INITIAL_NUM_OF_COINS = 4u;

    // tested class:
    CoinsCollector collector{INITIAL_NUM_OF_COINS};
};


TEST_F(CoinsCollectorTester, collectsCoins)
{
    // when and then
    collectAllCoins();
}


TEST_F(CoinsCollectorTester, resetsCollector)
{
    // given
    for(unsigned i = INITIAL_NUM_OF_COINS; i > 0; --i)
        collector.collectNextCoin();

    ASSERT_TRUE(collector.allCoinsCollected());

    // when
    collector.reset();

    // then
    ASSERT_FALSE(collector.allCoinsCollected());

    // when and then
    collectAllCoins();
}


} // namespace Testing
} // namespace Model
} // namespace Pacman
