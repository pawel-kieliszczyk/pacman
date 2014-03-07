#ifndef PACMAN_MODEL_IPACSLIFESCONTROLLER_HPP
#define PACMAN_MODEL_IPACSLIFESCONTROLLER_HPP


namespace Pacman
{
namespace Model
{


class IPacsLifesController
{
public:
    virtual void consumeNextLife() = 0;
    virtual bool isDead() const = 0;

    virtual void drawPacsLifes() const = 0;

    virtual void reset() = 0;

    virtual ~IPacsLifesController() = default;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_IPACSLIFESCONTROLLER_HPP
