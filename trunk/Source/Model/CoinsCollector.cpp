#include <Model/CoinsCollector.hpp>


namespace Pacman
{
namespace Model
{


CoinsCollector::CoinsCollector(unsigned coins_)
    : startingCoins(coins_),
      coins(coins_)
{
}


void CoinsCollector::collectNextCoin()
{
    --coins;
}


bool CoinsCollector::allCoinsCollected() const
{
    return (coins == 0u);
}


void CoinsCollector::reset()
{
    coins = startingCoins;
}


} // namespace Model
} // namespace Pacman
