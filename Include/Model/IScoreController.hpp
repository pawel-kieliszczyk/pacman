#ifndef PACMAN_MODEL_ISCORECONTROLLER_HPP
#define PACMAN_MODEL_ISCORECONTROLLER_HPP


namespace Pacman
{
namespace Model
{


class IScoreController
{
public:
    virtual void addCoinScore() = 0;
    virtual void addBigCoinScore() = 0;
    virtual void addGhostScore() = 0;

    virtual void drawScore() const = 0;

    virtual void reset() = 0;

    virtual ~IScoreController() = default;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_ISCORECONTROLLER_HPP
