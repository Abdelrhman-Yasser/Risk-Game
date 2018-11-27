from environment.Environment import Environment,AgentType


class Player:

    def __init__(self, env, player_id):
        self.__env = env
        self.__player_id = player_id
        self.__reserve_troops = 0

    @property
    def env(self):
        return self.__env

    @property
    def player_id(self):
        return self.__player_id

    @player_id.setter
    def player_id(self, player_id):
        self.__player_id = player_id

    @property
    def reserve_troops(self):
        return self.__reserve_troops

    @reserve_troops.setter
    def reserve_troops(self, reserve_troops):
        self.__reserve_troops = reserve_troops

    def deploy_reserve_troops(self):
        pass

    def march_troops(self):
        pass

    def invade(self):
        pass
