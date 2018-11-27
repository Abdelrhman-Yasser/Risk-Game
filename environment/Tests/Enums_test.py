import unittest
from environment.GameEnums import *


class TestAgentType(unittest.TestCase):
    def test_1(self):
        player = AgentType.HUMAN
        print(player)
        self.assertEqual(player, AgentType.HUMAN)

    def test_2(self):
        player = GamePlayId.P1
        print(player)
        self.assertNotEqual(player, GamePlayId.P2)


if __name__ == '__main__':
    unittest.main()
