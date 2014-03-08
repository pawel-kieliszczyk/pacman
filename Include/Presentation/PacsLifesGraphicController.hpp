#ifndef PACMAN_PRESENTATION_PACSLIFESGRAPHICCONTROLLER_HPP
#define PACMAN_PRESENTATION_PACSLIFESGRAPHICCONTROLLER_HPP


#include <vector>

#include <cinder/Vector.h>

#include <Presentation/IPacsLifesGraphicController.hpp>


namespace Pacman
{
namespace Presentation
{


namespace Detail
{


class PacsLifeSkeletonFactory
{
public:
    static std::vector<ci::Vec2f> create(const float lifeSize);
};


} // namespace Detail


class PacsLifesGraphicController : public IPacsLifesGraphicController
{
public:
    PacsLifesGraphicController(unsigned lifeSize_, unsigned boardHeight_, unsigned horizontalMargin_);

    void draw(unsigned lifes) override;

private:
    std::vector<ci::Vec2f> createLifesBorderPoints(const ci::Vec2f& position) const;

    void drawLifesBody(const std::vector<ci::Vec2f>& points);

    void drawLifesBorder(const std::vector<ci::Vec2f>& points);

    const float lifeSize;
    const unsigned boardHeight;
    const unsigned horizontalMargin;

    const std::vector<ci::Vec2f> skeleton;
};


} // namespace Presentation
} // namespace Pacman


#endif // PACMAN_PRESENTATION_PACSLIFESGRAPHICCONTROLLER_HPP
