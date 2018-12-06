from environment.Environment import Environment
from environment.Structures import *
import unittest
import copy


class MyTestCase(unittest.TestCase):
    def test_init(self):
        env = Environment("map_init.txt", "population_init.txt")
        for i, continent in enumerate(env.continent_list):
            for country_id in continent.country_list:
                self.assertEqual(env.country_list[country_id-1].continent_id, i+1)

    def test_deploy_1(self):
        env = Environment("map_init.txt", "population_init.txt")
        env.reserve_1 = 1
        env.deploy_reserve_troops(GamePlayId.P1, 1)
        try:
            env.deploy_reserve_troops(GamePlayId.NONE, 1)
            self.fail()
        except Exception as error:
            self.assertEqual(str(error), "Can't deploy troops to unowned country : country owner ("
                             + str(GamePlayId.P1) + ") ,"
                             + "player " + str(GamePlayId.NONE) + ")")

    def test_deploy_2(self):
        env = Environment("map_init.txt", "population_init.txt")
        env.reserve_1 = 1
        env.deploy_reserve_troops(GamePlayId.P1, 1)
        self.assertEqual(env.country_list[0].troops_count, 8)

    def test_march_1(self):
        env = Environment("map_init.txt", "population_init.txt")
        env.march_troops(GamePlayId.P1, 1, 3, 1)
        self.assertEqual(env.country_list[0].troops_count, 6)
        self.assertEqual(env.country_list[2].troops_count, 26)

    def test_march_2(self):
        env = Environment("map_init.txt", "population_init.txt")
        try:
            env.march_troops(GamePlayId.P1, 2, 3, 1)
            self.fail()
        except Exception as error:
            self.assertEqual(str(error),
                             "Can't march troops from unowned country : country owner ("
                             + str(GamePlayId.P2) + ") ,"
                             + "player (" + str(GamePlayId.P1) + ")")

    def test_march_3(self):
        env = Environment("map_init.txt", "population_init.txt")
        try:
            env.march_troops(GamePlayId.P1, 1, 4, 1)
            self.fail()
        except Exception as error:
            self.assertEqual(str(error),
                             "Can't march troops to unowned country : country owner ("
                             + str(GamePlayId.P2) + ") ,"
                             + "player (" + str(GamePlayId.P1) + ")")

    def test_march_4(self):
        env = Environment("map_init.txt", "population_init.txt")
        try:
            env.march_troops(GamePlayId.P1, 1, 3, 13)
            self.fail()
        except Exception as error:
            self.assertEqual(str(error),
                             "Not enough troops to march from ( " + str(1)
                             + " ) to ( " + str(3) + " ) troops are in country are "
                             + str(7))

    def test_march_5(self):
        env = Environment("map_init.txt", "population_init.txt")
        try:
            env.march_troops(GamePlayId.P1, 1, 5, 1)
            self.fail()
        except Exception as error:
            self.assertEqual(str(error),
                             "Can't march no route from ( " + str(1)
                             + " ) to ( " + str(5) + " )")

    def test_invade_1(self):
        env = Environment("map_init.txt", "population_init.txt")
        env.invade(GamePlayId.P2, 2, 3, 6)
        self.assertEqual(env.country_list[1].troops_count, 1)
        self.assertEqual(env.country_list[2].troops_count, 1)
        self.assertEqual(env.country_list[1].owner_id , GamePlayId.P2)

    def test_invade_2(self):
        env = Environment("map_init.txt", "population_init.txt")
        try:
            env.invade(GamePlayId.P2, 2, 4, 1)
        except Exception as error:
            self.assertEqual(str(error),"Can't invade your own country")

    def test_invade_3(self):
        env = Environment("map_init.txt", "population_init.txt")
        try:
            env.invade(GamePlayId.P2, 1, 4, 1)
        except Exception as error:
            self.assertEqual(str(error),
                             "Can't invade no route from ( " + str(1)
                             + " ) to ( " + str(4) + " )")

    def test_copy(self):
        env = Environment("map_init.txt", "population_init.txt")
        env_c = copy.deepcopy(env)
        env_c.country_list[0].owner_id = None
        env_c.border_list[0].country1 = None
        env_c.continent_list[0].owner_id = None
        self.assertNotEqual(env.country_list[0].owner_id, None)
        self.assertNotEqual(env.border_list[0].country1, None)
        self.assertNotEqual(env.continent_list[0].owner_id, None)


if __name__ == '__main__':
    unittest.main()
