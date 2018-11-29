from environment.GameEnums import MoveType
from players.state import EnvState
from collections import OrderedDict
import copy
import sys

class TreePrune:

    def get_states(self, state, player, move_type, number_elements=2):
        """
            :param state: state to be expanded
            :param player: player currently playing
            :param number_elements: number of states expanded from each level
            :param move_type: deploy , march , invade
            :return: res = expanded states
        """
        if move_type == MoveType.DEPLOY:
            prune1 = DefensivePrune()
            envs = self.__get_envs(state.env, player, number_elements, move_type, prune1)
            prune2 = ActualPrune()
            for env in self.__get_envs(state.env, player, number_elements, move_type, prune2):
                envs.append(env)
        if move_type == MoveType.INVADE:
            prune1 = OffensivePrune()
            envs = self.__get_envs(state.env, player, number_elements, move_type, prune1)
            prune2 = ActualPrune()
            for env in self.__get_envs(state.env, player, number_elements, move_type, prune2):
                envs.append(env)
        if move_type == MoveType.MARCH:
            prune1 = OffensivePrune()
            envs = self.__get_envs(state.env, player, number_elements, move_type, prune1)
            prune2 = NeutralPrune()
            for env in self.__get_envs(state.env, player, number_elements, move_type, prune2):
                envs.append(env)

        states = []
        for env in envs:
            states.append(EnvState(env, state))

        return states

    def __get_envs(self, env, player, number_elements, move_type, prune , attack=False):
        actions = self.__get_actions(env, player.player_id, number_elements, prune, attack)
        envs = []
        for action in actions:
            if move_type == MoveType.DEPLOY:
                env_c = copy.deepcopy(env)
                env_c.deploy_reserve_troops(player.player_id, action[1], player.reserve_troops)
                envs.append(env_c)
            if move_type == MoveType.MARCH:
                env_c = copy.deepcopy(env)
                env_c.march_troops(player.player_id, action[0], action[1], 0.5)
                envs.append(env_c)
            if move_type == MoveType.INVADE:
                env_c = copy.deepcopy(env)
                env_c.invade(player.player_id, action[1], action[2], 0.5)
                envs.append(env_c)
        return envs

    def __get_actions(self, env, player_id, number_elements, prune, attack=False):
        array = OrderedDict()
        actions = 0

        for border in env.border_list:
            if env.country_list[border.country1].owner_id != env.country_list[border.country2].owner_id:
                key, cost = prune.compute(env, border, player_id)
                if key is None:
                    continue
                array[key] = cost

        actions = self.__get_keys(array, number_elements)

        return actions

    def __get_keys(self, array, number_elements , attack=False):

        if attack:
            array = {k: v for k, v in array.items() if v > 0}

        array = sorted(array.items(), key=lambda kv: kv[1])

        array = [k for k,v in array]

        keys = []

        if len(array) <= 3:
            return array

        elements = array
        size = len(elements)

        for i in range(0, min(number_elements/2, size)):
            keys.append(elements[i])

        for i in range(size-1, max(size - number_elements/2, 0) , -1):
            keys.append(elements[i])

        return keys


class NeutralPrune:
    """
        put in mind city troops + their support vs enemy troops + their support
    """
    def compute(self, env, border, player_id):
        support_c1 = - sys.maxsize
        support_c2 = - sys.maxsize
        support_c1_in = -1
        support_c2_in = -1
        country1 = env.country_list[border.country1 - 1]
        country2 = env.country_list[border.country2 - 1]

        for country in env.adj_list[country1.id]:
            if country.owner_id == country1.owner_id and country.troops_count > support_c1:
                support_c1 = country.troops_count
                support_c1_in = country.id
        for country in env.adj_list[country2.id]:
            if country.owner_id == country2.owner_id and country.troops_count > support_c2:
                support_c2 = country.troops_count
                support_c2_in = country.id

        cost = 0
        key = None

        if country1.owner_id == player_id and support_c1_in != -1 and support_c2_in != -1:
            cost = (country2.troops_count + support_c2) - \
                (country1.troops_count + support_c1)
            key = (support_c1_in, country1.id, country2.id, support_c2_in)

        elif country2.owner_id == player_id and support_c1_in != -1 and support_c2_in != -1:
            cost = (country1.troops_count + support_c1) - \
                (country2.troops_count + support_c2)
            key = (support_c2_in, country2.id, country1.id, support_c1_in)

        return key, cost


class DefensivePrune:
    """
        put in mind city troops vs enemy troops + their support
    """
    def compute(self, env, border, player_id):

        support_c1 = - sys.maxsize
        support_c2 = - sys.maxsize
        support_c1_in = -1
        support_c2_in = -1
        country1 = env.country_list[border.country1 - 1]
        country2 = env.country_list[border.country2 - 1]

        for country in env.adj_list[country1.id]:
            if country.owner_id == country1.owner_id and country.troops_count > support_c1:
                support_c1 = country.troops_count
                support_c1_in = country.id
        for country in env.adj_list[country2.id]:
            if country.owner_id == country2.owner_id and country.troops_count > support_c2:
                support_c2 = country.troops_count
                support_c2_in = country.id

        cost = 0
        key = None

        if country1.owner_id == player_id and support_c2_in != -1:
            cost = (country2.troops_count + support_c2) - \
                   country1.troops_count
            key = (-1, country1.id, country2.id, support_c2_in)

        elif country2.owner_id == player_id and support_c1_in != -1:
            cost = (country1.troops_count + support_c1) - \
                    country2.troops_count
            key = (-1, country2.id, country1.id, support_c1_in)

        return key, cost

class OffensivePrune:
    """
        put in mind city troops + support vs enemy troops
    """
    def compute(self, env, border, player_id):
        support_c1 = - sys.maxsize
        support_c2 = - sys.maxsize
        support_c1_in = -1
        support_c2_in = -1
        country1 = env.country_list[border.country1 - 1]
        country2 = env.country_list[border.country2 - 1]

        for country in env.adj_list[country1.id]:
            if country.owner_id == country1.owner_id and country.troops_count > support_c1:
                support_c1 = country.troops_count
                support_c1_in = country.id
        for country in env.adj_list[country2.id]:
            if country.owner_id == country2.owner_id and country.troops_count > support_c2:
                support_c2 = country.troops_count
                support_c2_in = country.id

        cost = 0
        key = None

        if country1.owner_id == player_id and support_c1_in != -1:
            cost = country2.troops_count - \
                   (country1.troops_count + support_c1)
            key = (support_c1_in, country1.id, country2.id, -1)

        elif country2.owner_id == player_id and support_c2_in != -1:
            cost = country1.troops_count - \
                   (country2.troops_count + support_c2)
            key = (support_c2_in, country2.id, country1.id, -1)

        return key, cost


class ActualPrune:
    """
        put in mind city troops vs enemy troops
    """
    def compute(self, env, border, player_id):

        country1 = env.country_list[border.country1 - 1]
        country2 = env.country_list[border.country2 - 1]

        cost = 0

        if country1.owner_id == player_id:
            cost = country2.troops_count - country1.troops_count
            key = (-1, country1.id, country2.id, -1)

        elif country2.owner_id == player_id:
            cost = country1.troops_count - country2.troops_count
            key = (-1, country2.id, country1.id, -1)

        return key, cost
