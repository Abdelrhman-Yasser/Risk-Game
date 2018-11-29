from players.player import Player
from environment.GameEnums import *
from environment.GameEnums import MoveType
from players.pruners import TreePrune
from heapdict import heapdict
import math


class Heuristic:

    countries_coff = 0.1
    percentage_cont_coff = 0.5
    army_coff = 0.001

    def sigmoid(self, x):
        return (2 / (1 + math.exp(-10 * x))) + 2

    def get_n_owned(self, env, player):
        n = 0
        for country in env.country_list:
            if country.owner_id == player.player_id:
                n += 1
        return n

    def get_continent_percentage(self, env, player):
        sum = 0
        for continent in env.continent_list:
            per = 0
            all = len(continent.country_list)
            for country_id in continent.country_list:
                if env.country_list[country_id].owner_id == player.player_id:
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

    def H(self, state, player):
        env = state.env
        n_owned_countries = self.get_n_owned(env, player)
        per_continents = self.get_continent_percentage(env, player)
        army = self.get_army_strength(env, player)

        return n_owned_countries * self.countries_coff + \
               per_continents * self.percentage_cont_coff + \
               army * self.army_coff


class Greedy(Player):

    def __init__(self, player_id):
        Player.__init__(self, player_id)
        self.__player_type = AgentType.GREEDY

    @property
    def player_type(self):
        return self.__player_type

    def expand(self, state):
        states = self.deploy_reserve_troops(state)
        states = self.march_troops(states)
        states = self.invade(states)
        return states

    def deploy_reserve_troops(self, state):
        extender = TreePrune()
        return extender.get_states(state, self, MoveType.DEPLOY)

    def march_troops(self, states):
        extender = TreePrune()
        n_states = []
        for state in states:
            n_states.extend(extender.get_states(state, self, MoveType.MARCH))
        return n_states

    def invade(self, states):
        extender = TreePrune()
        n_states = []
        for state in states:
            n_states.extend(extender.get_states(state, self, MoveType.INVADE))
        return n_states

    def search(self, initial_state, enemy_player):

        explored = set()
        in_fringe = set()

        fringe = heapdict()
        fringe[initial_state] = 0
        in_fringe.add(initial_state)

        state = fringe.popitem()[0]

        while state:

            in_fringe.remove(state)
            explored.add(state)

            if state.env.game_status == GameStatus.ENDED :
                #writeOutput(state)
                #end = time.time()
                #print("Time : ", end - start)
                #print("Nodes Explored : ", len(explored))
                return

            children = self.expand(state)

            for child in children:
                H = Heuristic.H(child.env, self)
                if child not in explored and child not in in_fringe:
                    fringe[child] = H
                    in_fringe.add(child)
                elif child in in_fringe and fringe[child] > H:
                    fringe[child] = H

            state = fringe.popitem()[0]
