from environment.Environment import Environment,AgentType


class Player:

    def __init__(self, player_id):
        self.__player_id = player_id

    @property
    def player_id(self):
        return self.__player_id

    @player_id.setter
    def player_id(self, player_id):
        self.__player_id = player_id
