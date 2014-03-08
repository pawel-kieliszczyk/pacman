#ifndef PACMAN_MODEL_ICLOCK_HPP
#define PACMAN_MODEL_ICLOCK_HPP


namespace Pacman
{
namespace Model
{


class IClock
{
public:
    virtual void tick() = 0;

    virtual ~IClock() = default;
};


}
}


#endif // PACMAN_MODEL_ICLOCK_HPP
