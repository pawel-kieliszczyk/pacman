#ifndef PACMAN_MODEL_COINFIELD_HPP
#define PACMAN_MODEL_COINFIELD_HPP


#include <Model/FieldBase.hpp>


namespace Pacman
{
namespace Model
{


class CoinField : public FieldBase
{
public:
    CoinField(unsigned row, unsigned col);

    bool isVisitable() const override;
    void visit(IPac& pac) override;
    void draw(Presentation::IBoardGraphicController& graphicController) const override;
    void reset() override;

private:
    bool visited;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_COINFIELD_HPP
