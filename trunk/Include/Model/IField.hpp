#ifndef PACMAN_MODEL_IFIELD_HPP
#define PACMAN_MODEL_IFIELD_HPP


#include <Model/IPac.hpp>
#include <Presentation/IBoardGraphicController.hpp>


namespace Pacman
{
namespace Model
{

class IField
{
public:
    virtual bool isVisitable() const = 0;
    virtual void visit(IPac& pac) = 0;
    virtual void draw(Presentation::IBoardGraphicController& graphicController) const = 0;
    virtual void reset() = 0;

    virtual ~IField() = default;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_IFIELD_HPP
