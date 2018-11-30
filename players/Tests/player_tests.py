import unittest
from environment.Environment import Environment,GamePlayId,GameStatus
from players.humans import Human
from players.agents import PassiveAgent
from players.state import EnvState
from players.player import Player
from players.ai import Greedy

class PlayerTests(unittest.TestCase):
    def test_reference(self):
        env = Environment("map_init.txt", "population_init.txt")
        p1 = Player(GamePlayId.P1)
        self.assertEqual(1, 1)


class HumanTests(unittest.TestCase):

    def test_deploy_1(self):
        env = Environment("map_init.txt", "population_init.txt")
        p1 = Human(GamePlayId.P1)
        p2 = Human(GamePlayId.P2)
        p1.deploy_reserve_troops(env, 1, 1)
        try:
            p2.deploy_reserve_troops(env, 1, 1)
            self.fail()
        except Exception as error:
            self.assertEqual(str(error), "Can't deploy troops to unowned country : country owner ("
                             + str(GamePlayId.P1) + ") ,"
                             + "player " + str(GamePlayId.P2) + ")")

    def test_deploy_2(self):
        env = Environment("map_init.txt", "population_init.txt")
        p1 = Human(GamePlayId.P1)
        p1.deploy_reserve_troops(env, 1, 1)
        self.assertEqual(env.country_list[0].troops_count, 4)

    def test_march_1(self):
        env = Environment("map_init.txt", "population_init.txt")
        p1 = Human(GamePlayId.P1)
        p1.march_troops(env, 1, 3, 1)
        self.assertEqual(env.country_list[0].troops_count, 2)
        self.assertEqual(env.country_list[2].troops_count, 6)

    def test_march_2(self):
        env = Environment("map_init.txt", "population_init.txt")
        p1 = Human(GamePlayId.P1)
        try:
            p1.march_troops(env, 2, 3, 1)
            self.fail()
        except Exception as error:
            self.assertEqual(str(error),
                             "Can't march troops from unowned country : country owner ("
                             + str(GamePlayId.P2) + ") ,"
                             + "player (" + str(GamePlayId.P1) + ")")

    def test_march_3(self):
        env = Environment("map_init.txt", "population_init.txt")
        p1 = Human(GamePlayId.P1)
        try:
            p1.march_troops(env, 1, 4, 1)
            self.fail()
        except Exception as error:
            self.assertEqual(str(error),
                             "Can't march troops to unowned country : country owner ("
                             + str(GamePlayId.P2) + ") ,"
                             + "player (" + str(GamePlayId.P1) + ")")

    def test_march_4(self):
        env = Environment("map_init.txt", "population_init.txt")
        p1 = Human(GamePlayId.P1)
        try:
            p1.march_troops(env, 1, 3, 13)
            self.fail()
        except Exception as error:
            self.assertEqual(str(error),
                             "Not enough troops to march from ( " + str(1)
                             + " ) to ( " + str(3) + " ) troops are in country are "
                             + str(3))

    def test_march_5(self):
        env = Environment("map_init.txt", "population_init.txt")
        p1 = Human(GamePlayId.P1)
        try:
            p1.march_troops(env, 1, 5, 1)
            self.fail()
        except Exception as error:
            self.assertEqual(str(error),
                             "Can't march no route from ( " + str(1)
                             + " ) to ( " + str(5) + " )")

    def test_invade_1(self):
        env = Environment("map_init.txt", "population_init.txt")
        p2 = Human(GamePlayId.P2)
        p2.invade(env, 2, 3, 6)
        self.assertEqual(env.country_list[1].troops_count, 1)
        self.assertEqual(env.country_list[2].troops_count, 1)
        self.assertEqual(env.country_list[1].owner_id , GamePlayId.P2)

    def test_invade_1_corner(self):
        env = Environment("map_init.txt", "population_init.txt")
        p2 = Human(GamePlayId.P2)
        p2.invade(env, 2, 3, 5)
        self.assertEqual(env.country_list[1].troops_count, 2)
        self.assertEqual(env.country_list[2].troops_count, 0)
        self.assertEqual(env.country_list[2].owner_id, GamePlayId.NONE)

    def test_invade_2(self):
        env = Environment("map_init.txt", "population_init.txt")
        p2 = Human(GamePlayId.P2)
        try:
            p2.invade(env, 2, 4, 1)
        except Exception as error:
            self.assertEqual(str(error), "Can't invade your own country")

    def test_invade_3(self):
        env = Environment("map_init.txt", "population_init.txt")
        p2 = Human(GamePlayId.P2)
        try:
            p2.invade(env, 1, 4, 1)
        except Exception as error:
            self.assertEqual(str(error),
                             "Can't invade no route from ( " + str(1)
                             + " ) to ( " + str(4) + " )")


class TestEnvState(unittest.TestCase):

    def test1(self):
        env1 = Environment("map_init.txt", "population_init.txt")
        state1 = EnvState(env1, None)
        env2 = Environment("map_init.txt", "population_init.txt")
        env2.country_list[0].owner_id = GamePlayId.NONE
        state2 = EnvState(env2, None)
        self.assertNotEqual(state1, state2)



class AiTests(unittest.TestCase):

    def test1(self):
        env = Environment("map_init.txt", "population_init.txt")
        state = EnvState(env, None)
        player1 = Greedy(GamePlayId.P1)
        player2 = PassiveAgent(GamePlayId.P2)
        player1.search(state, player2)





if __name__ == '__main__':
    unittest.main()
