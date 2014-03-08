#ifndef PACMAN_MODEL_COINSCOLLECTOR_HPP
#define PACMAN_MODEL_COINSCOLLECTOR_HPP


#include <Model/ICoinsCollector.hpp>


namespace Pacman
{
namespace Model
{


class CoinsCollector : public ICoinsCollector
{
public:
    CoinsCollector(unsigned coins_);

    void collectNextCoin();
    bool allCoinsCollected() const;
    void reset() override;

private:
    const unsigned startingCoins;
    unsigned coins;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_COINSCOLLECTOR_HPP
