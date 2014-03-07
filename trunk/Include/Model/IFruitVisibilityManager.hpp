#ifndef PACMAN_MODEL_IFRUITVISIBILITYMANAGER_HPP
#define PACMAN_MODEL_IFRUITVISIBILITYMANAGER_HPP


#include <memory>

#include <Model/IFruit.hpp>


namespace Pacman
{
namespace Model
{


class IFruitVisibilityManager
{
public:
    virtual void showFruit(std::shared_ptr<IFruit> f) = 0;
    virtual void hideFruit() = 0;

    virtual ~IFruitVisibilityManager() = default;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_IFRUITVISIBILITYMANAGER_HPP
