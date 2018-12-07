from enum import Enum


class MoveType(Enum):
    DEPLOY = 1
    INVADE = 2
    MARCH = 3
    NOMOVE = 4


class AgentType(Enum):
    HUMAN = 1
    PASSIVE = 2
    AGGRESSIVE = 3
    PACIFIST = 4
    GREEDY = 5
    ASTAR = 6
    RASTAR = 7


class GamePlayId(Enum):
    P1 = 1
    P2 = 2
    NONE = 3


class GameStatus(Enum):
    ONGOING = 1
    ENDED = 2


class PlayerAction(Enum):
    DEPLOY = 1
    MARCH = 2
    INVADE = 3
