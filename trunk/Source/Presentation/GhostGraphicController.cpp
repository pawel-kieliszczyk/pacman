#include <algorithm>
#include <cassert>
#include <iterator>
#include <utility>
#include <vector>

#include <cinder/Color.h>
#include <cinder/gl/gl.h>
#include <cinder/PolyLine.h>
#include <cinder/Vector.h>

#include <Presentation/GhostGraphicController.hpp>


namespace Pacman
{
namespace Presentation
{


namespace Detail
{


std::vector<ci::Vec2f> GhostSkeletonFactory::create(const float ghostSize)
{
    std::vector<ci::Vec2f> skeleton;

    const float PI = 3.14159265f;
    const float STEP = 0.2;

    for(float i = PI; i < (2.0f * PI + STEP); i += STEP)
    {
        const float r = ghostSize / 2.0f;

        const float x = r + r * std::cos(i);
        const float y = r + r * std::sin(i);
        skeleton.emplace_back(x, y);
    }

    skeleton.emplace_back(ghostSize,               ghostSize);
    skeleton.emplace_back(ghostSize * 5.0f / 6.0f, ghostSize * 5.0f / 6.0f);
    skeleton.emplace_back(ghostSize * 2.0f / 3.0f, ghostSize);
    skeleton.emplace_back(ghostSize        / 2.0f, ghostSize * 5.0f / 6.0f);
    skeleton.emplace_back(ghostSize        / 3.0f, ghostSize);
    skeleton.emplace_back(ghostSize        / 6.0f, ghostSize * 5.0f / 6.0f);
    skeleton.emplace_back(0.0f,                    ghostSize);

    const float offset = ghostSize / 2;
    std::for_each(
            std::begin(skeleton),
            std::end(skeleton),
            [offset](ci::Vec2f& p){ p -= ci::Vec2f(offset, offset); });

    return skeleton;
}


ci::Color ColorConverter::toBodyColor(Model::Color color)
{
    switch(color)
    {
        case Model::Color::Red :
            return ci::Color(0.5f, 0.0f, 0.0f);
        case Model::Color::Green :
            return ci::Color(0.0f, 0.5f, 0.0f);
        case Model::Color::Pink :
            return ci::Color(0.5f, 0.0f, 0.5f);
        case Model::Color::Orange :
            return ci::Color(0.6f, 0.4f, 0.0f);
        case Model::Color::LightBlue :
            return ci::Color(0.0f, 0.7f, 1.0f);
    }
}


ci::Color ColorConverter::toBorderColor(Model::Color color)
{
    switch(color)
    {
        case Model::Color::Red :
            return ci::Color(1.0f, 0.0f, 0.0f);
        case Model::Color::Green :
            return ci::Color(0.0f, 1.0f, 0.5f);
        case Model::Color::Pink :
            return ci::Color(1.0f, 0.0f, 1.f);
        case Model::Color::Orange :
            return ci::Color(1.0f, 0.5f, 0.0f);
        case Model::Color::LightBlue :
            return ci::Color(0.0f, 1.0f, 1.0f);
    }
}


ci::Color ColorConverter::toEyeColor(Model::Color /*color*/)
{
    return ci::Color(0.8f, 0.8f, 0.8f);
}


ci::Color ColorConverter::toPupilOfEyeColor(Model::Color color)
{
    if(color == Model::Color::LightBlue)
        return ci::Color(0.0f, 0.7f, 1.0f);

    return ci::Color(0.0f, 0.0f, 0.8f);
}


} // namespace Detail


GhostGraphicController::GhostGraphicController(
        unsigned fieldSize_,
        unsigned horizontalOffset_,
        float ghostSizeScale,
        std::shared_ptr<IDirectionCalculator> directionCalculator_)
    : fieldSize(fieldSize_),
      horizontalOffset(horizontalOffset_),
      directionCalculator(directionCalculator_),
      ghostSize(ghostSizeScale * static_cast<float>(fieldSize)),
      ghostSkeleton(std::move(Detail::GhostSkeletonFactory::create(ghostSize))),
      direction(Model::Direction::Up)
{
}


void GhostGraphicController::drawNormalGhost(
        int fromRow,
        int fromColumn,
        int toRow,
        int toColumn,
        unsigned step,
        unsigned resolution,
        Model::Color color)
{
    drawGhost(fromRow, fromColumn, toRow, toColumn, step, resolution, color, EyeState::Dynamic);
}


void GhostGraphicController::drawScaredGhost(
        int fromRow,
        int fromColumn,
        int toRow,
        int toColumn,
        unsigned step,
        unsigned resolution,
        Model::Color /*color*/)
{
    const Model::Color color = Model::Color::LightBlue;
    drawGhost(fromRow, fromColumn, toRow, toColumn, step, resolution, color, EyeState::Static);
}


void GhostGraphicController::drawLastSecondsScaredGhost(
        int fromRow,
        int fromColumn,
        int toRow,
        int toColumn,
        unsigned step,
        unsigned resolution,
        Model::Color color)
{
    const bool hasColor = step < (resolution / 2);
    const Model::Color colorToDraw = (hasColor ? color : Model::Color::LightBlue);

    drawGhost(fromRow, fromColumn, toRow, toColumn, step, resolution, colorToDraw, EyeState::Static);
}


void GhostGraphicController::drawGhost(
        int fromRow,
        int fromColumn,
        int toRow,
        int toColumn,
        unsigned step,
        unsigned resolution,
        Model::Color color,
        EyeState eyeState)
{
    calculateDirection(fromRow, fromColumn, toRow, toColumn);

    const ci::Vec2f position = calculateGhostsPosition(fromRow, fromColumn, toRow, toColumn, step, resolution);
    std::vector<ci::Vec2f> points = createGhostsBorderPoints(position);

    drawGhostsBody(points, position, color);
    drawGhostsEyes(position, color, eyeState);
    drawGhostsBorder(points, color);
}


void GhostGraphicController::calculateDirection(
            int fromRow,
            int fromColumn,
            int toRow,
            int toColumn)
{
    boost::optional<Model::Direction> dir = directionCalculator->calculate(fromRow, fromColumn, toRow, toColumn);
    assert(dir);
    direction = *dir;
}


ci::Vec2f GhostGraphicController::calculateGhostsPosition(
            int fromRow,
            int fromColumn,
            int toRow,
            int toColumn,
            unsigned step,
            unsigned resolution) const
{
    float x = (fromColumn * static_cast<int>(fieldSize)) + (static_cast<float>(fieldSize) / 2);
    float y = (fromRow * static_cast<int>(fieldSize)) + (static_cast<float>(fieldSize) / 2);

    if(toColumn > fromColumn)
        x += static_cast<float>(fieldSize * step) / static_cast<float>(resolution);
    if(toColumn < fromColumn)
        x -= static_cast<float>(fieldSize * step) / static_cast<float>(resolution);

    if(toRow > fromRow)
        y += static_cast<float>(fieldSize * step) / static_cast<float>(resolution);
    if(toRow < fromRow)
        y -= static_cast<float>(fieldSize * step) / static_cast<float>(resolution);

    const ci::Vec2f position(horizontalOffset + x, y);

    return position;
}


std::vector<ci::Vec2f> GhostGraphicController::createGhostsBorderPoints(const ci::Vec2f& position) const
{
    std::vector<ci::Vec2f> points;

    std::transform(
            std::begin(ghostSkeleton),
            std::end(ghostSkeleton),
            std::back_inserter(points),
            [&position](const ci::Vec2f& v){ return v + position; });

    return points;
}


void GhostGraphicController::alignPupilsOfEyesToDirection(
        ci::Vec2f& leftPupil,
        ci::Vec2f& rightPupil,
        float pupilRadius) const
{
    const float offset = pupilRadius;// * 2;

    switch(direction)
    {
        case Model::Direction::Up :
            leftPupil += ci::Vec2f(0.0f, -offset);
            rightPupil += ci::Vec2f(0.0f, -offset);
            break;
        case Model::Direction::Down :
            leftPupil += ci::Vec2f(0.0f, offset);
            rightPupil += ci::Vec2f(0.0f, offset);
            break;
        case Model::Direction::Left :
            leftPupil += ci::Vec2f(-offset, 0.0f);
            rightPupil += ci::Vec2f(-offset, 0.0f);
            break;
        case Model::Direction::Right :
            leftPupil += ci::Vec2f(offset, 0.0f);
            rightPupil += ci::Vec2f(offset, 0.0f);
            break;
    }
}


void GhostGraphicController::drawGhostsBody(
        const std::vector<ci::Vec2f>& points,
        const ci::Vec2f& center,
        Model::Color ghostColor)
{
    ci::Color cinderColor = Detail::ColorConverter::toBodyColor(ghostColor);
    ci::gl::color(cinderColor);

    const auto numOfPoints = points.size();

    for(auto i = 0u; i < numOfPoints; ++i)
    {
        const ci::Vec2f& p1 = points[i];
        const ci::Vec2f& p2 = points[(i + 1) % numOfPoints];

        ci::gl::drawSolidTriangle(p1, p2, center);
    }
}


void GhostGraphicController::drawGhostsEyes(const ci::Vec2f& center, Model::Color ghostColor, EyeState eyeState)
{
    const float eyesHorizontalOffset = ghostSize / 5;
    const float eyesVerticalOffset = ghostSize / 6;

    const float eyeRadius = ghostSize / 6;
    const float pupilRadius = eyeRadius / 2;

    const ci::Vec2f leftEyeCenter = center + ci::Vec2f(-eyesHorizontalOffset, -eyesVerticalOffset);
    const ci::Vec2f rightEyeCenter = center + ci::Vec2f(eyesHorizontalOffset, -eyesVerticalOffset);

    ci::Vec2f leftPupilOfEyeCenter = center + ci::Vec2f(-eyesHorizontalOffset, -eyesVerticalOffset);
    ci::Vec2f rightPupilOfEyeCenter = center + ci::Vec2f(eyesHorizontalOffset, -eyesVerticalOffset);

    if(eyeState == EyeState::Dynamic)
        alignPupilsOfEyesToDirection(leftPupilOfEyeCenter, rightPupilOfEyeCenter, pupilRadius);

    // draw eye
    ci::Color cinderColor = Detail::ColorConverter::toEyeColor(ghostColor);
    ci::gl::color(cinderColor);

    ci::gl::drawSolidCircle(leftEyeCenter, eyeRadius);
    ci::gl::drawSolidCircle(rightEyeCenter, eyeRadius);

    // draw pupil of the eye
    cinderColor = Detail::ColorConverter::toPupilOfEyeColor(ghostColor);
    ci::gl::color(cinderColor);

    ci::gl::drawSolidCircle(leftPupilOfEyeCenter, pupilRadius);
    ci::gl::drawSolidCircle(rightPupilOfEyeCenter, pupilRadius);
}


void GhostGraphicController::drawGhostsBorder(
        const std::vector<ci::Vec2f>& points,
        Model::Color ghostColor)
{
    ci::Color cinderColor = Detail::ColorConverter::toBorderColor(ghostColor);
    ci::gl::color(cinderColor);

    ci::PolyLine2f pl(points);
    pl.setClosed();

    ci::gl::draw(pl);
}


} // namespace Presentation
} // namespace Pacman
