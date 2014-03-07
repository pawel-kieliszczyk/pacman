#ifndef PACMAN_MODEL_DETAIL_GAMECONTROLLERFSM_HPP
#define PACMAN_MODEL_DETAIL_GAMECONTROLLERFSM_HPP


#include <memory>
#include <vector>

#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 30

#include <boost/mpl/vector.hpp>
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/states.hpp>

#include <Model/Detail/GameControllerFsmActions.hpp>
#include <Model/Detail/GameControllerFsmGuards.hpp>
#include <Model/GameControllerEvents.hpp>
#include <Model/IBoard.hpp>
#include <Model/IClock.hpp>
#include <Model/ICoinsCollector.hpp>
#include <Model/ICollisionDetector.hpp>
#include <Model/IFruitsCollector.hpp>
#include <Model/IGameModeManager.hpp>
#include <Model/IGhost.hpp>
#include <Model/IPac.hpp>
#include <Model/IPacsLifesController.hpp>
#include <Model/IScoreController.hpp>
#include <Presentation/IWindowGraphicController.hpp>


namespace Pacman
{
namespace Model
{
namespace Detail
{


// only inside Detail namespace:
namespace mpl = ::boost::mpl;
using namespace ::boost::msm::front;


class GameControllerFsm : public state_machine_def<GameControllerFsm>
{
    // states:
    struct Idle                    : state<> {};
    struct Playing                 : state<> {};
    struct Paused                  : state<> {};
    struct CheckingCoinsCollection : state<> {};
    struct DetectingEatenPac       : state<> {};
    struct DetectingEatenGhosts    : state<> {};
    struct CheckingPacsLifes       : state<> {};
    struct GameWon                 : state<> {};
    struct GameLost                : state<> {};

public:
    GameControllerFsm(
            std::shared_ptr<IBoard> board_,
            std::shared_ptr<IPac> pac_,
            std::vector<std::shared_ptr<IGhost>> ghosts_,
            std::shared_ptr<IClock> clock_,
            std::shared_ptr<IGameModeManager> gameModeManager_,
            std::shared_ptr<ICoinsCollector> coinsCollector_,
            std::shared_ptr<IFruitsCollector> fruitsCollector_,
            std::shared_ptr<ICollisionDetector> collisionDetector_,
            std::shared_ptr<IPacsLifesController> pacsLifesController_,
            std::shared_ptr<IScoreController> scoreController_,
            std::shared_ptr<Presentation::IWindowGraphicController> windowGraphicController_);

    void clearWindow();

    void drawBoard();
    void drawPac();
    void drawGhosts();
    void drawPacsLifes();
    void drawScore();
    void drawFruits();

    void drawStoppedGameCurtain();
    void drawPausedGameCurtain();
    void drawWonGameCurtain();
    void drawLostGameCurtain();

    void tickClock();

    void setPacsDirection(const KeyPressed& event);
    void movePac();
    void moveGhosts();

    void consumePacsLife();

    void resetBoard();
    void resetPac();
    void resetGhosts();
    void resetCollidingGhosts();
    void resetCoinsCollector();
    void resetFruitsCollector();
    void resetPacsLifesController();
    void resetScoreController();
    void resetGameModeManager();

    bool areAllCoinsCollected() const;
    bool isBigCoinModeActive() const;
    bool areAnyCollisions() const;
    bool isPacDead() const;

    template<class Event, class Fsm>
    void no_transition(const Event& /*e*/, Fsm& /*fsm*/, const int /*state*/)
    {
        // ignore events which don't cause transitions
    }

    typedef Idle initial_state;

    struct transition_table : mpl::vector<
//           Start                     Event           Target                    Action                              Guard
//         +-------------------------+---------------+-------------------------+-----------------------------------+----------------------+
        Row< Idle                    , DrawRequested , Idle                    , ActionSequence_<
                                                                                     mpl::vector<
                                                                                         ClearWindow,
                                                                                         DrawBoard,
                                                                                         DrawStoppedGameCurtain>>  , none                 >,
        Row< Idle                    , KeyPressed    , Playing                 , none                              , IsKey<Key::Return>   >,
//         +-------------------------+---------------+-------------------------+-----------------------------------+----------------------+
        Row< Playing                 , MoveRequested , CheckingCoinsCollection , ActionSequence_<
                                                                                     mpl::vector<
                                                                                         TickClock,
                                                                                         MovePac,
                                                                                         MovePac,
                                                                                         MoveGhosts,
                                                                                         MoveGhosts>>              , none                 >,
        Row< Playing                 , MoveRequested , CheckingCoinsCollection , ActionSequence_<
                                                                                     mpl::vector<
                                                                                         TickClock,
                                                                                         MovePac,
                                                                                         MovePac,
                                                                                         MoveGhosts>>              , IsBigCoinModeActive  >,
        Row< Playing                 , DrawRequested , Playing                 , ActionSequence_<
                                                                                     mpl::vector<
                                                                                         ClearWindow,
                                                                                         DrawBoard,
                                                                                         DrawPac,
                                                                                         DrawGhosts,
                                                                                         DrawPacsLifes,
                                                                                         DrawScore,
                                                                                         DrawFruits>>              , none                 >,
        Row< Playing                 , KeyPressed    , Playing                 , SetPacsDirection                  , IsAnyOfKeys<
                                                                                                                         Key::UpArrow,
                                                                                                                         Key::DownArrow,
                                                                                                                         Key::LeftArrow,
                                                                                                                         Key::RightArrow> >,
        Row< Playing                 , KeyPressed    , Paused                  , none                              , IsKey<Key::P>        >,
//         +-------------------------+---------------+-------------------------+-----------------------------------+----------------------+
        Row< CheckingCoinsCollection , none          , DetectingEatenPac       , none                              , none                 >,
        Row< CheckingCoinsCollection , none          , DetectingEatenGhosts    , none                              , IsBigCoinModeActive  >,
        Row< CheckingCoinsCollection , none          , GameWon                 , none                              , AreAllCoinsCollected >,
//         +-------------------------+---------------+-------------------------+-----------------------------------+----------------------+
        Row< DetectingEatenPac       , none          , Playing                 , none                              , none                 >,
        Row< DetectingEatenPac       , none          , CheckingPacsLifes       , ConsumePacsLife                   , AreAnyCollisions     >,
//         +-------------------------+---------------+-------------------------+-----------------------------------+----------------------+
        Row< DetectingEatenGhosts    , none          , Playing                 , ResetCollidingGhosts              , none                 >,
//         +-------------------------+---------------+-------------------------+-----------------------------------+----------------------+
        Row< CheckingPacsLifes       , none          , Playing                 , ActionSequence_<
                                                                                     mpl::vector<
                                                                                         ResetPac,
                                                                                         ResetGhosts>>             , none                 >,
        Row< CheckingPacsLifes       , none          , GameLost                , none                              , IsPacDead            >,
//         +-------------------------+---------------+-------------------------+-----------------------------------+----------------------+
        Row< Paused                  , DrawRequested , Paused                  , ActionSequence_<
                                                                                     mpl::vector<
                                                                                         ClearWindow,
                                                                                         DrawBoard,
                                                                                         DrawPausedGameCurtain>>   , none                 >,
        Row< Paused                  , KeyPressed    , Playing                 , none                              , IsKey<Key::P>        >,
//         +-------------------------+---------------+-------------------------+-----------------------------------+----------------------+
        Row< GameWon                 , DrawRequested , GameWon                 , ActionSequence_<
                                                                                     mpl::vector<
                                                                                         ClearWindow,
                                                                                         DrawBoard,
                                                                                         DrawPac,
                                                                                         DrawGhosts,
                                                                                         DrawPacsLifes,
                                                                                         DrawScore,
                                                                                         DrawFruits,
                                                                                         DrawWonGameCurtain>>      , none                 >,
        Row< GameWon                 , KeyPressed    , Idle                    , ActionSequence_<
                                                                                     mpl::vector<
                                                                                         ResetBoard,
                                                                                         ResetPac,
                                                                                         ResetGhosts,
                                                                                         ResetCoinsCollector,
                                                                                         ResetFruitsCollector,
                                                                                         ResetPacsLifesController,
                                                                                         ResetScoreController,
                                                                                         ResetGameModeManager>>    , IsKey<Key::Return>   >,
//         +-------------------------+---------------+-------------------------+-----------------------------------+----------------------+
        Row< GameLost                , DrawRequested , GameLost                , ActionSequence_<
                                                                                     mpl::vector<
                                                                                         ClearWindow,
                                                                                         DrawBoard,
                                                                                         DrawPac,
                                                                                         DrawGhosts,
                                                                                         DrawPacsLifes,
                                                                                         DrawScore,
                                                                                         DrawFruits,
                                                                                         DrawLostGameCurtain>>     , none                 >,
        Row< GameLost                , KeyPressed    , Idle                    , ActionSequence_<
                                                                                     mpl::vector<
                                                                                         ResetBoard,
                                                                                         ResetPac,
                                                                                         ResetGhosts,
                                                                                         ResetCoinsCollector,
                                                                                         ResetFruitsCollector,
                                                                                         ResetPacsLifesController,
                                                                                         ResetScoreController,
                                                                                         ResetGameModeManager>>    , IsKey<Key::Return>   >
//         +-------------------------+---------------+-------------------------+-----------------------------------+----------------------+
    > {};

private:
    std::shared_ptr<IBoard> board;
    std::shared_ptr<IPac> pac;
    std::vector<std::shared_ptr<IGhost>> ghosts;
    std::shared_ptr<IClock> clock;
    std::shared_ptr<IGameModeManager> gameModeManager;
    std::shared_ptr<ICoinsCollector> coinsCollector;
    std::shared_ptr<IFruitsCollector> fruitsCollector;
    std::shared_ptr<ICollisionDetector> collisionDetector;
    std::shared_ptr<IPacsLifesController> pacsLifesController;
    std::shared_ptr<IScoreController> scoreController;
    std::shared_ptr<Presentation::IWindowGraphicController> windowGraphicController;
};


} // namespace Detail
} // namespace Model
} // namespace Pacman


#endif // PACMAN_MODEL_DETAIL_GAMECONTROLLERFSM_HPP
