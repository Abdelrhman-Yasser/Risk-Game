from players.player import Player
from environment.Environment import AgentType


class Human(Player):

    def __init__(self, player_id):
        Player.__init__(self, player_id)
        self.__player_type = AgentType.HUMAN

    @property
    def player_type(self):
        return self.player_type

    def deploy_reserve_troops(self, env, target_country_id, count):
        env.deploy_reserve_troops(self.player_id, target_country_id, count)

    def march_troops(self, env, from_country_id, to_country_id,  count):
        env.march_troops(self.player_id, from_country_id, to_country_id, count)

    def invade(self, env, from_country_id, to_country_id, troops):
        env.invade(self.player_id, from_country_id, to_country_id, troops)

