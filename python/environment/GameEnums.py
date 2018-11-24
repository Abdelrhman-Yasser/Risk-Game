from enum import Enum


class AgentType(Enum):
    HUMAN = 1
    PASSIVE = 2
    AGGRESSIVE = 3
    PACIFIST = 4
    GREEDY = 5


class GamePlayId(Enum):
    NONE = 1
    P1 = 2
    P2 = 3


class GameStatus(Enum):
    ONGOING = 1
    ENDED = 2


class PlayerAction(Enum):
    DEPLOY = 1
    MARCH = 2
    INVADE = 3
