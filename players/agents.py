from players.player import Player
from environment.GameEnums import AgentType,MoveType
from players.state import EnvState
import sys
import copy


class AggressiveAgent(Player):

    def __init__(self, player_id):
        Player.__init__(self, player_id)
        self.__player_type = AgentType.AGGRESSIVE

    @property
    def player_type(self):
        return self.__player_type

    def expand(self, state):
        state = self.deploy_reserve_troops(state)
        state = state.expand_same(MoveType.MARCH, self.player_id)
        return self.invade(state)

    def deploy_reserve_troops(self, state):
        try:
            env_c = copy.deepcopy(state.env)
            max_troops_country_id = -1
            max_troops_count = 0
            for country in env_c.country_list:
                if country.owner_id == self.player_id and country.troops_count > max_troops_count:
                    max_troops_count = country.troops_count
                    max_troops_country_id = self.player_id
            env_c.deploy_reserve_troops(self.player_id, max_troops_country_id)
            return EnvState(env_c, state, MoveType.DEPLOY, self.player_id)
        except Exception as e:
            return state.expand_same(MoveType.DEPLOY, self.player_id)

    def march_troops(self, state):
        return state.expand_same(MoveType.MARCH, self.player_id)

    def __get_most_damage(self, env):
        max_enemy = 0
        max_enemy_id = -1
        own_id = -1
        for border in env.border_list:

            country1 = env.country_list[border.country1 - 1]
            country2 = env.country_list[border.country2 - 1]

            if country1.owner_id == self.player_id and country2.owner_id == self.player_id:
                continue
            if country1.owner_id == self.player_id and \
                    country1.troops_count - country2.troops_count > 1 and \
                    country2.troops_count > max_enemy:
                max_enemy = country2.troops_count
                max_enemy_id = country2.id
                own_id = country1.id
            if country2.owner_id == self.player_id and \
                    country2.troops_count - country1.troops_count > 1 and \
                    country1.troops_count > max_enemy:
                max_enemy = country1.troops_count
                max_enemy_id = country1.id
                own_id = country2.id
        return own_id, max_enemy_id

    def invade(self, state):
        try:
            env_c = copy.deepcopy(state.env)
            from_country, to_country = self.__get_most_damage(env_c)
            env_c.invade(self.player_id, from_country, to_country, 0.9)
            return EnvState(env_c, state, MoveType.INVADE, self.player_id)
        except Exception as e:
            return state.expand_same(MoveType.INVADE, self.player_id)


class PacifistAgent(Player):

    def __init__(self, player_id):
        Player.__init__(self, player_id)
        self.__player_type = AgentType.PACIFIST

    @property
    def player_type(self):
        return self.__player_type

    def expand(self, state):
        state = self.deploy_reserve_troops(state)
        state = self.march_troops(state)
        return self.invade(state)

    def deploy_reserve_troops(self, state):
        try:
            env_c = copy.deepcopy(state.env)
            min_troops_country_id = -1
            min_troops_count = sys.maxsize
            for country in env_c.country_list:
                if country.owner_id == self.player_id and country.troops_count < min_troops_count:
                    min_troops_count = country.troops_count
                    min_troops_country_id = self.player_id
            env_c.deploy_reserve_troops(self.player_id, min_troops_country_id)
            return EnvState(env_c, state, MoveType.DEPLOY, self.player_id)
        except Exception as e:
            return state.expand_same(MoveType.DEPLOY, self.player_id)

    def march_troops(self, state):
        return state.expand_same(MoveType.MARCH, self.player_id)

    def __get_least_damage(self, env):
        min_enemy = sys.maxsize
        min_enemy_id = -1
        own_id = -1
        for border in env.border_list:
            country1 = env.country_list[border.country1 - 1]
            country2 = env.country_list[border.country2 - 1]

            if country1.owner_id == self.player_id and country2.owner_id == self.player_id:
                continue
            if country1.owner_id == self.player_id and \
                    country1.troops_count - country2.troops_count > 1 and \
                    country2.troops_count < min_enemy:
                min_enemy = country2.troops_count
                min_enemy_id = country2.id
                own_id = country1.id
            if country2.owner_id == self.player_id and \
                    country2.troops_count - country1.troops_count > 1 and\
                    country1.troops_count < min_enemy:
                min_enemy = country1.troops_count
                min_enemy_id = country1.id
                own_id = country2.id
        return own_id, min_enemy_id

    def invade(self, state):
        try:
            env_c = copy.deepcopy(state.env)
            from_country, to_country = self.__get_least_damage(env_c)
            env_c.invade(self.player_id, from_country, to_country, 0.9)
            return EnvState(env_c, state, MoveType.INVADE, self.player_id)
        except Exception as e:
            return state.expand_same(MoveType.INVADE, self.player_id)


class PassiveAgent(Player):

    def __init__(self, player_id):
        Player.__init__(self, player_id)
        self.__player_type = AgentType.PASSIVE

    @property
    def player_type(self):
        return self.__player_type

    def expand(self, state):
        state = self.deploy_reserve_troops(state)
        state = self.march_troops(state)
        return self.invade(state)

    def deploy_reserve_troops(self, state):
        try:
            env_c = copy.deepcopy(state.env)
            min_troops_country_id = -1
            min_troops_count = sys.maxsize
            for country in env_c.country_list:
                if country.owner_id == self.player_id and country.troops_count < min_troops_count:
                    min_troops_count = country.troops_count
                    min_troops_country_id = country.id
            if min_troops_country_id == -1:
                return state.expand_state(MoveType.DEPLOY, self.player_id)
            env_c.deploy_reserve_troops(self.player_id, min_troops_country_id)
            return EnvState(env_c, state, MoveType.DEPLOY, self.player_id)
        except Exception as e:
            return state.expand_same(MoveType.DEPLOY, self.player_id)

    def march_troops(self, state):
        return state.expand_same(MoveType.MARCH, self.player_id)

    def invade(self, state):
        return state.expand_same(MoveType.INVADE, self.player_id)
