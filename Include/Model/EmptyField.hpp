#ifndef PACMAN_MODEL_EMPTYFIELD_HPP
#define PACMAN_MODEL_EMPTYFIELD_HPP


#include <Model/FieldBase.hpp>


namespace Pacman
{
namespace Model
{


class EmptyField : public FieldBase
{
public:
    EmptyField(unsigned row, unsigned col);

    bool isVisitable() const override;
    void visit(IPac& pac) override;
    void draw(Presentation::IBoardGraphicController& graphicController) const override;
    void reset() override;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_EMPTYFIELD_HPP
