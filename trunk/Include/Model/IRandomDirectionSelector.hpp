#ifndef PACMAN_MODEL_IRANDOMDIRECTIONSELECTOR_HPP
#define PACMAN_MODEL_IRANDOMDIRECTIONSELECTOR_HPP


#include <vector>

#include <Model/Direction.hpp>


namespace Pacman
{
namespace Model
{


class IRandomDirectionSelector
{
public:
    virtual Direction selectDirection(const std::vector<Direction>& directions) = 0;

    virtual ~IRandomDirectionSelector() = default;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_IRANDOMDIRECTIONSELECTOR_HPP
