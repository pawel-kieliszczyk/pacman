#ifndef PACMAN_PRESENTATION_TESTING_PACSLIFESGRAPHICCONTROLLERMOCK_HPP
#define PACMAN_PRESENTATION_TESTING_PACSLIFESGRAPHICCONTROLLERMOCK_HPP


#include <gmock/gmock.h>

#include <Presentation/IPacsLifesGraphicController.hpp>


namespace Pacman
{
namespace Presentation
{
namespace Testing
{


class PacsLifesGraphicControllerMock : public IPacsLifesGraphicController
{
public:
    MOCK_METHOD1(draw, void(unsigned));
};


}
}
}


#endif // PACMAN_PRESENTATION_TESTING_PACSLIFESGRAPHICCONTROLLERMOCK_HPP
