from environment.Environment import Environment
from environment.Encoders import Encoder
from environment.GameEnums import MoveType
from action.action import *
import json
import copy


class EnvState:

    def __init__(self, env, parent, move_type, game_player):
        self.env = env
        self.parent = parent
        self.move_type = move_type
        self.game_play = game_player
        if parent is None:
            self.distance = 0
        else:
            self.distance = parent.distance + 1

    def __str__(self):
        strg = "state:\nmove_type = "+str(self.move_type)+" for player : "+str(self.game_play)+"\n\n"
        strg += str(self.env)
        return strg

    def __eq__(self, other):
        if isinstance(other, EnvState):
            return json.dumps(self.env.reprJson(), cls=Encoder) + str(self.move_type) == \
                   json.dumps(other.env.reprJson(), cls=Encoder) + str(other.move_type)
        else:
            return False

    def __hash__(self):
        return hash(json.dumps(self.env.reprJson(), cls=Encoder) + str(self.move_type) + str(self.game_play))

    def expand_same(self, move_type, game_play):
        env_c = copy.deepcopy(self.env)
        env_c.change = NoAction()
        return EnvState(env_c, self, move_type, game_play)
