import copy

from action.action import NoAction
from players.agents import AggressiveAgent
from players.player import Player
from environment.GameEnums import *
from environment.GameEnums import MoveType
from players.pruners import TreePrune
from heapdict import heapdict
from players.state import EnvState
import math
import sys

class Heuristic:

    countries_coff = 10
    percentage_cont_coff = 100
    army_coff = 2

    def sigmoid(self, x):
        return (1 / (1 + math.exp(-1 * x))) + 1

    def get_n_owned(self, env, player):
        n = 0
        all = 0
        for country in env.country_list:
            if country.owner_id == player.player_id:
                n += 1
            all += 1
        return all , n

    def get_continent_percentage(self, env, player):
        sum = 0
        for continent in env.continent_list:
            per = 0
            all = len(continent.country_list)
            for country_id in continent.country_list:
                if env.country_list[country_id - 1].owner_id == player.player_id:
                    per += 1
            per /= all
            per *= continent.reward
            sum += per
        return sum

    def get_army_strength(self, env, player):
        troops = 0
        for country in env.country_list:
            if country.owner_id == player.player_id:
                troops += country.troops_count
        return troops

    def H1(self, state, player):
        env = state.env
        total , n_owned_countries = self.get_n_owned(env, player)
        per_continents = self.get_continent_percentage(env, player)
        army = self.get_army_strength(env, player)

        fraction = n_owned_countries * self.countries_coff + \
                   per_continents * self.percentage_cont_coff + \
                   army * self.army_coff

        cost = (1/self.sigmoid(fraction)) * (total - n_owned_countries)
        return cost


class Greedy(Player):

    def __init__(self, player_id):
        Player.__init__(self, player_id)
        self.__player_type = AgentType.GREEDY
        self.goal_state = None

    @property
    def player_type(self):
        return self.__player_type

    def writeout_path(self):
        state = self.goal_state

        path_states = []

        while not state is None:
            path_states.append(state)
            state = state.parent

        path_states.reverse()

        path = []

        for state in path_states:
            path.append("Action to get state from before : " + str(state.env.change) + "\n")
            path.append(str(state) + "\n")
        path.append(("\n" + str(state.env.winner) + " wins\n"))

        strg = ""
        for s in path:
            strg += s
        return strg

    def expand(self, state):
        #x = input()
        states = self.deploy_reserve_troops(state)
        #x = input()
        states = self.march_troops(states)
        #x = input()
        states = self.invade(states)
        return states

    def deploy_reserve_troops(self, state):
        extender = TreePrune()
        n_state = extender.get_states(state, self, MoveType.DEPLOY)
        if len(n_state) == 0:
            return [state.expand_same(MoveType.DEPLOY, self.player_id)]
        return n_state

    def march_troops(self, states):
        extender = TreePrune()
        n_states = []
        for state in states:
            n_state = extender.get_states(state, self, MoveType.MARCH)
            if len(n_state) == 0:
                n_states.extend([state.expand_same(MoveType.MARCH, self.player_id)])
            else:
                n_states.extend(n_state)
        return n_states

    def invade(self, states):
        extender = TreePrune()
        n_states = []
        for state in states:
            n_state = extender.get_states(state, self, MoveType.INVADE)
            if len(n_state) == 0:
                n_states.extend([state.expand_same(MoveType.INVADE, self.player_id)])
            else:
                n_states.extend(n_state)
        return n_states

    def search(self, initial_state, enemy_player):

        explored = set()
        in_fringe = set()

        fringe = heapdict()
        fringe[initial_state] = 0
        in_fringe.add(initial_state)

        while True:

            try:
                state = fringe.popitem()[0]
            except Exception as e:
                print("end")
                break
            in_fringe.remove(state)
            explored.add(state)

            children = self.expand(state)

            n_children = []
            for child in children:
                n_state = enemy_player.expand(child)
                n_children.append(n_state)

            for child in n_children:
                if child.env.game_status == GameStatus.ENDED:
                    self.goal_state = child
                    return

            for child in n_children:
                H = Heuristic()
                H = H.H1(child, self)
                if child not in explored and child not in in_fringe:
                    fringe[child] = H
                    in_fringe.add(child)
                elif child in in_fringe and fringe[child] > H:
                    fringe[child] = H


class AStar(Player):

    def __init__(self, player_id):
        Player.__init__(self, player_id)
        self.__player_type = AgentType.GREEDY
        self.goal_state = None

    @property
    def player_type(self):
        return self.__player_type

    def writeout_path(self):
        state = self.goal_state

        path_states = []

        while not state is None:
            path_states.append(state)
            state = state.parent

        path_states.reverse()

        path = []

        for state in path_states:
            path.append("Action to get state from before : " + str(state.env.change) + "\n")
            path.append(str(state) + "\n")
        path.append(("\n" + str(state.env.winner) + " wins\n"))

        strg = ""
        for s in path:
            strg += s
        return strg

    def expand(self, state):
        states = self.deploy_reserve_troops(state)
        states = self.march_troops(states)
        states = self.invade(states)
        return states

    def deploy_reserve_troops(self, state):
        extender = TreePrune()
        n_state = extender.get_states(state, self, MoveType.DEPLOY)
        if len(n_state) == 0:
            return [state.expand_same(MoveType.DEPLOY, self.player_id)]
        return n_state

    def march_troops(self, states):
        extender = TreePrune()
        n_states = []
        for state in states:
            n_state = extender.get_states(state, self, MoveType.MARCH)
            if len(n_state) == 0:
                n_states.extend([state.expand_same(MoveType.DEPLOY, self.player_id)])
            else:
                n_states.extend(n_state)
        return n_states

    def invade(self, states):
        extender = TreePrune()
        n_states = []
        for state in states:
            n_state = extender.get_states(state, self, MoveType.INVADE)
            if len(n_state) == 0:
                n_states.extend([state.expand_same(MoveType.DEPLOY, self.player_id)])
            else:
                n_states.extend(n_state)
        return n_states

    def search(self, initial_state, enemy_player):

        explored = set()
        in_fringe = set()

        fringe = heapdict()
        fringe[initial_state] = 0
        in_fringe.add(initial_state)

        while True:

            try:
                state = fringe.popitem()[0]
            except Exception as e:
                print("end")
                break
            in_fringe.remove(state)
            explored.add(state)
            children = self.expand(state)

            n_children = []
            for child in children:
                n_state = enemy_player.expand(child)
                n_children.append(n_state)

            for child in n_children:
                if child.env.game_status == GameStatus.ENDED:
                    self.goal_state = child
                    return

            for child in n_children:
                H = Heuristic()
                H = H.H1(child, self)
                if child not in explored and child not in in_fringe:
                    fringe[child] = H + child.distance
                    in_fringe.add(child)
                elif child in in_fringe and fringe[child] > H + child.distance:
                    fringe[child] = H + child.distance


class RTAStar(Player):

    def __init__(self, player_id):
        Player.__init__(self, player_id)
        self.__player_type = AgentType.GREEDY
        self.goal_state = None

    @property
    def player_type(self):
        return self.__player_type


    def expand(self, state):
        #x = input()
        states = self.deploy_reserve_troops(state)
        #x = input()
        states = self.march_troops(states)
        #x = input()
        states = self.invade(states)
        return states

    def deploy_reserve_troops(self, state):
        extender = TreePrune()
        n_state = extender.get_states(state, self, MoveType.DEPLOY)
        if len(n_state) == 0:
            return [state.expand_same(MoveType.DEPLOY, self.player_id)]
        return n_state

    def march_troops(self, states):
        extender = TreePrune()
        n_states = []
        for state in states:
            n_state = extender.get_states(state, self, MoveType.MARCH)
            if len(n_state) == 0:
                n_states.extend([state.expand_same(MoveType.MARCH, self.player_id)])
            else:
                n_states.extend(n_state)
        return n_states

    def invade(self, states):
        extender = TreePrune()
        n_states = []
        for state in states:
            n_state = extender.get_states(state, self, MoveType.INVADE)
            if len(n_state) == 0:
                n_states.extend([state.expand_same(MoveType.INVADE, self.player_id)])
            else:
                n_states.extend(n_state)
        return n_states

    def search(self, initial_state, start_move_type):

        if self.player_id == GamePlayId.P1:
            enemy_id = GamePlayId.P2
        else:
            enemy_id = GamePlayId.P1

        enemy_player = AggressiveAgent(enemy_id)
        initial_state.depth = 1

        game_ended = False

        if start_move_type == MoveType.DEPLOY:
            states = self.deploy_reserve_troops(initial_state)
            states = self.march_troops(states)
            states = self.invade(states)
        elif start_move_type == MoveType.MARCH:
            states = self.march_troops([initial_state])
            states = self.invade(states)
        else:
            states = self.invade([initial_state])

        n_children = []
        for child in states:
            n_state = enemy_player.expand(child)
            n_children.append(n_state)

        for child in n_children:
            if child.env.game_status == GameStatus.ENDED:
                self.goal_state = child

        if not game_ended:
            mini = sys.maxsize
            mini_child = -1
            H = Heuristic()
            for child in n_children:
                He = H.H1(child, self) + child.distance
                if He < mini:
                    mini = He
                    mini_child = child
            self.goal_state = mini_child

        if self.goal_state.parent is None:
            return NoAction()
        res_state = self.goal_state
        while res_state.parent.parent is not None:
            res_state = res_state.parent
        state = copy.deepcopy(res_state)
        state.parent = None

        return state



