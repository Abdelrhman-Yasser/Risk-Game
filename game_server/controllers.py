from players.player import *
from players.agents import *
from players.ai import *
from players.humans import Human
from environment.Environment import Environment


class Controller:

    def __init__(self, player1_type, player2_type):
        self.player1 = self.get_player(player1_type, GamePlayId.P1)
        self.player2 = self.get_player(player2_type, GamePlayId.P2)
        self.player1.reserve_troops = 2
        self.player2.reserve_troops = 2
        self.env = Environment("/server_files/map_init.txt", "/server_files/population_init.txt")
        self.turn = True
        self.state = EnvState(self.env, None, None, GamePlayId.P1)

    def get_player(self, player1_type, player_id):
        if player1_type == "human":
            return Human(player_id)
        elif player1_type == "passive":
            return PassiveAgent(player_id)
        elif player1_type == "aggressive":
            return AggressiveAgent(player_id)
        elif player1_type == "pacifist":
            return PacifistAgent

    def deploy_human(self, target, count):
        target = int(target)
        count = int(count)
        if self.turn:
            self.player1.deploy_reserve_troops(self.env, target, count)
        else:
            self.player2.deploy_reserve_troops(self.env, target, count)

    def march_human(self, from_id, target_id, count):
        from_id = int(from_id)
        target_id = int(target_id)
        count = int(count)
        if self.turn:
            self.player1.march_troops(self.env, from_id, target_id, count)
        else:
            self.player2.march_troops(self.env, from_id, target_id, count)

    def invade_human(self, from_id, target_id, count):
        from_id = int(from_id)
        target_id = int(target_id)
        count = int(count)
        if self.turn:
            self.player1.invade(self.env, from_id, target_id, count)
        else:
            self.player2.invade(self.env, from_id, target_id, count)
        self.turn != self.turn

    def deploy_pc_agent(self, player):
        self.state = player.deploy_reserve_troops(self.state)

    def deploy_pc_rta(self, player):
        self.state = player.search(self.state, MoveType.DEPLOY)

    def deploy_pc(self):
        if self.turn:
            if (isinstance(self.player1, AggressiveAgent) or
                    isinstance(self.player1, PassiveAgent) or
                    isinstance(self.player1, PacifistAgent)):
                self.deploy_pc_agent()
            elif isinstance(self.player1, RTAStar):
                self.deploy_pc_rta()
        else:
            if (isinstance(self.player2, AggressiveAgent) or
                    isinstance(self.player2, PassiveAgent) or
                    isinstance(self.player2, PacifistAgent)):
                self.deploy_pc_agent()
            elif isinstance(self.player2, RTAStar):
                self.deploy_pc_rta()
        return self.state.change

    def march_pc_agent(self, player):
        self.state = player.march_troops(self.state)

    def march_pc_rta(self, player):
        self.state = player.search(self.state, MoveType.MARCH)

    def march_pc(self):
        if self.turn:
            if (isinstance(self.player1, AggressiveAgent) or
                    isinstance(self.player1, PassiveAgent) or
                    isinstance(self.player1, PacifistAgent)):
                self.march_pc_agent()
            elif isinstance(self.player1, RTAStar):
                self.march_pc_rta()
        else:
            if (isinstance(self.player2, AggressiveAgent) or
                    isinstance(self.player2, PassiveAgent) or
                    isinstance(self.player2, PacifistAgent)):
                self.march_pc_agent()
            elif isinstance(self.player2, RTAStar):
                self.march_pc_rta()
        return self.state.change

    def invade_pc_agent(self, player):
        self.state = player.invade(self.state)

    def invade_pc_rta(self, player):
        self.state = player.search(self.state, MoveType.INVADE)

    def invade_pc(self):
        if self.turn:
            if (isinstance(self.player1, AggressiveAgent) or
                    isinstance(self.player1, PassiveAgent) or
                    isinstance(self.player1, PacifistAgent)):
                self.invade_pc_agent()
            elif isinstance(self.player1, RTAStar):
                self.invade_pc_rta()
        else:
            if (isinstance(self.player2, AggressiveAgent) or
                    isinstance(self.player2, PassiveAgent) or
                    isinstance(self.player2, PacifistAgent)):
                self.invade_pc_agent()
            elif isinstance(self.player2, RTAStar):
                self.invade_pc_rta()
        return self.state.change
