from players.player import Player
from environment.Environment import AgentType


class Human(Player):

    def __init__(self, env, player_id):
        Player.__init__(self, env, player_id)
        self.__player_type = AgentType.HUMAN

    @property
    def player_type(self):
        return self.player_type

    def deploy_reserve_troops(self, target_country_id, count):
        self.env.deploy_reserve_troops(self.player_id, target_country_id, count)

    def march_troops(self, from_country_id, to_country_id,  count):
        self.env.march_troops(self.player_id, from_country_id, to_country_id, count)

    def invade(self, from_country_id, to_country_id):
        self.env.invade(self.player_id, from_country_id, to_country_id)

