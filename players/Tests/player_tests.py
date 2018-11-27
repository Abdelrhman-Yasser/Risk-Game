import unittest
from environment.Environment import Environment,GamePlayId,GameStatus
from players.humans import Human
from players.player import Player


class PlayerTests(unittest.TestCase):
    def test_reference(self):
        env = Environment("map_init.txt", "population_init.txt")
        p1 = Player(env, GamePlayId.P1)
        p1.env.game_status = 1
        self.assertEqual(env.game_status, 1)


class HumanTests(unittest.TestCase):

    def test_deploy_1(self):
        env = Environment("map_init.txt", "population_init.txt")
        p1 = Human(env, GamePlayId.P1)
        p2 = Human(env, GamePlayId.P2)
        p1.deploy_reserve_troops(1, 1)
        try:
            p2.deploy_reserve_troops(1, 1)
            self.fail()
        except Exception as error:
            self.assertEqual(str(error), "Can't deploy troops to unowned country : country owner ("
                             + str(GamePlayId.P1) + ") ,"
                             + "player " + str(GamePlayId.P2) + ")")

    def test_deploy_2(self):
        env = Environment("map_init.txt", "population_init.txt")
        p1 = Human(env, GamePlayId.P1)
        p1.deploy_reserve_troops(1, 1)
        self.assertEqual(env.country_list[0].troops_count, 4)

    def test_march_1(self):
        env = Environment("map_init.txt", "population_init.txt")
        p1 = Human(env, GamePlayId.P1)
        p1.march_troops(1, 3, 1)
        self.assertEqual(env.country_list[0].troops_count, 2)
        self.assertEqual(env.country_list[2].troops_count, 6)

    def test_march_2(self):
        env = Environment("map_init.txt", "population_init.txt")
        p1 = Human(env, GamePlayId.P1)
        try:
            p1.march_troops(2, 3, 1)
            self.fail()
        except Exception as error:
            self.assertEqual(str(error),
                             "Can't march troops from unowned country : country owner ("
                             + str(GamePlayId.P2) + ") ,"
                             + "player (" + str(GamePlayId.P1) + ")")

    def test_march_3(self):
        env = Environment("map_init.txt", "population_init.txt")
        p1 = Human(env, GamePlayId.P1)
        try:
            p1.march_troops(1, 4, 1)
            self.fail()
        except Exception as error:
            self.assertEqual(str(error),
                             "Can't march troops to unowned country : country owner ("
                             + str(GamePlayId.P2) + ") ,"
                             + "player (" + str(GamePlayId.P1) + ")")

    def test_march_4(self):
        env = Environment("map_init.txt", "population_init.txt")
        p1 = Human(env, GamePlayId.P1)
        try:
            p1.march_troops(1, 3, 13)
            self.fail()
        except Exception as error:
            self.assertEqual(str(error),
                             "Not enough troops to march from ( " + str(1)
                             + " ) to ( " + str(3) + " ) troops are in country are "
                             + str(3))

    def test_march_5(self):
        env = Environment("map_init.txt", "population_init.txt")
        p1 = Human(env, GamePlayId.P1)
        try:
            p1.march_troops(1, 5, 1)
            self.fail()
        except Exception as error:
            self.assertEqual(str(error),
                             "Can't march no route from ( " + str(1)
                             + " ) to ( " + str(5) + " )")

    def test_invade_1(self):
        env = Environment("map_init.txt", "population_init.txt")
        p2 = Human(env, GamePlayId.P2)
        p2.invade(2, 3)
        self.assertEqual(env.country_list[1].troops_count, 1)
        self.assertEqual(env.country_list[2].troops_count, 1)
        self.assertEqual(env.country_list[1].owner_id , GamePlayId.P2)

    def test_invade_2(self):
        env = Environment("map_init.txt", "population_init.txt")
        p2 = Human(env, GamePlayId.P2)
        try:
            p2.invade(2, 4)
        except Exception as error:
            self.assertEqual(str(error),"Can't invade your own country")

    def test_invade_3(self):
        env = Environment("map_init.txt", "population_init.txt")
        p2 = Human(env, GamePlayId.P2)
        try:
            p2.invade(1, 4)
        except Exception as error:
            self.assertEqual(str(error),
                             "Can't invade no route from ( " + str(1)
                             + " ) to ( " + str(4) + " )")


if __name__ == '__main__':
    unittest.main()
