from players.player import Player
from environment.GameEnums import *

class Greedy(Player):

    def __init__(self, env, player_id):
        Player.__init__(self, env, player_id)
        self.__player_type = AgentType.GREEDY

    @property
    def player_type(self):
        return self.__player_type

    