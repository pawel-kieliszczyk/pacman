#ifndef PACMAN_MODEL_GAMECONTROLLER_HPP
#define PACMAN_MODEL_GAMECONTROLLER_HPP


#include <memory>

#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 30

#define BOOST_MSM_CONSTRUCTOR_ARG_SIZE 11

#include <boost/msm/back/state_machine.hpp>

#include <Model/Detail/GameControllerFsm.hpp>
#include <Model/IGameController.hpp>


namespace Pacman
{
namespace Model
{


class GameController : public IGameController
{
public:
    template<class... Args>
    explicit GameController(Args&&... args)
        : gameControllerFsm(new boost::msm::back::state_machine<Detail::GameControllerFsm>(std::forward<Args>(args)...))
    {
        gameControllerFsm->start();
    }

    ~GameController();

    void process(const KeyPressed& event);
    void process(const MoveRequested& event);
    void process(const DrawRequested& event);

private:
    std::unique_ptr<boost::msm::back::state_machine<Detail::GameControllerFsm>> gameControllerFsm;
};


} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_GAMECONTROLLER_HPP
