#ifndef PACMAN_MODEL_ICOINSCOLLECTOR_HPP
#define PACMAN_MODEL_ICOINSCOLLECTOR_HPP


namespace Pacman
{
namespace Model
{


class ICoinsCollector
{
public:
    virtual void collectNextCoin() = 0;
    virtual bool allCoinsCollected() const = 0;
    virtual void reset() = 0;

    virtual ~ICoinsCollector() = default;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_ICOINSCOLLECTOR_HPP
