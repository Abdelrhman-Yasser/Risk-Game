from players.player import Player
from environment.GameEnums import AgentType
import sys


class AggressiveAgent(Player):

    def __init__(self, env, player_id):
        Player.__init__(self, env, player_id)
        self.__player_type = AgentType.AGGRESSIVE

    @property
    def player_type(self):
        return self.__player_type

    def deploy_reserve_troops(self):
        max_troops_country_id = -1
        max_troops_count = 0
        for country in self.env.country_list:
            if country.owner_id == self.player_id and country.troops_count > max_troops_count:
                max_troops_count = country.troops_count
                max_troops_country_id = self.player_id
        self.env.deploy_reserve_troops(self.player_id, max_troops_country_id, Player.reserve_troops)
        Player.reserve_troops = 0

    def march_troops(self):
        pass

    def __get_most_damage(self):
        max_enemy = 0
        max_enemy_id = -1
        own_id = -1
        for border in self.env.border_list:
            if border.country1.owner_id == self.player_id and border.country2.owner_id == self.player_id:
                continue
            if border.country1.owner_id == self.player_id and \
                    border.country1.troops_count - border.country2.troops_count > 1 and \
                    border.country2.troops_count > max_enemy:
                max_enemy = border.country2.troops_count
                max_enemy_id = border.country2.id
                own_id = border.country1.id
            if border.country2.owner_id == self.player_id and \
                    border.country2.troops_count - border.country1.troops_count > 1 and \
                    border.country1.troops_count > max_enemy:
                max_enemy = border.country1.troops_count
                max_enemy_id = border.country1.id
                own_id = border.country2.id
        return own_id , max_enemy_id

    def invade(self):
        from_country , to_country = self.__get_most_damage()
        Player.reserve_troops += self.env.invade(self.player_id, from_country, to_country)


class PacifistAgent(Player):

    def __init__(self, env, player_id):
        Player.__init__(self, env, player_id)
        self.__player_type = AgentType.PACIFIST

    @property
    def player_type(self):
        return self.__player_type

    def deploy_reserve_troops(self):
        min_troops_country_id = -1
        min_troops_count = sys.maxsize
        for country in self.env.country_list:
            if country.owner_id == self.player_id and country.troops_count < min_troops_count:
                min_troops_count = country.troops_count
                min_troops_country_id = self.player_id
        self.env.deploy_reserve_troops(self.player_id, min_troops_country_id, Player.reserve_troops)
        Player.reserve_troops = 0

    def march_troops(self, from_country_id, to_country_id, count):
        pass

    def __get_least_damage(self):
        min_enemy = sys.maxsize
        min_enemy_id = -1
        own_id = -1
        for border in self.env.border_list:
            if border.country1.owner_id == self.player_id and border.country2.owner_id == self.player_id:
                continue
            if border.country1.owner_id == self.player_id and \
                    border.country1.troops_count - border.country2.troops_count > 1 and \
                    border.country2.troops_count < min_enemy:
                min_enemy = border.country2.troops_count
                min_enemy_id = border.country2.id
                own_id = border.country1.id
            if border.country2.owner_id == self.player_id and \
                    border.country2.troops_count - border.country1.troops_count > 1 and\
                    border.country1.troops_count < min_enemy:
                min_enemy = border.country1.troops_count
                min_enemy_id = border.country1.id
                own_id = border.country2.id
        return own_id, min_enemy_id

    def invade(self, from_country_id, to_country_id):
        from_country, to_country = self.__get_least_damage()
        Player.reserve_troops += self.env.invade(self.player_id, from_country, to_country)


class PassiveAgent(Player):

    def __init__(self, env, player_id):
        Player.__init__(self, env, player_id)
        self.__player_type = AgentType.PASSIVE

    @property
    def player_type(self):
        return self.__player_type

    def deploy_reserve_troops(self):
        min_troops_country_id = -1
        min_troops_count = sys.maxsize
        for country in self.env.country_list:
            if country.owner_id == self.player_id and country.troops_count < min_troops_count:
                min_troops_count = country.troops_count
                min_troops_country_id = self.player_id
        self.env.deploy_reserve_troops(self.player_id, min_troops_country_id, Player.reserve_troops)
        Player.reserve_troops = 0