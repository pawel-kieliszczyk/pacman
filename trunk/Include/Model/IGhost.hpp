#ifndef PACMAN_MODEL_IGHOST_HPP
#define PACMAN_MODEL_IGHOST_HPP


namespace Pacman
{
namespace Model
{


class IGhost
{
public:
    virtual void move() = 0;

    virtual double getCurrentX() const = 0;
    virtual double getCurrentY() const = 0;

    virtual void draw() const = 0;

    virtual void reset() = 0;

    virtual ~IGhost() = default;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_IGHOST_HPP
