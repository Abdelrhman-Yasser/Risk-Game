import unittest
from utilities.Parser import *
import re

class MyTestCase(unittest.TestCase):
    def test_map(self):
        mapy = MapFileParser("map_init.txt")
        self.assertEqual(mapy.get_border_count(), 4)
        self.assertEqual(mapy.get_continent_count(), 2)
        self.assertEqual(mapy.get_country_count(), 4)
        border_list = mapy.obtain_border_list()
        self.assertEqual(border_list[0].country1, 1)
        self.assertEqual(border_list[0].country2, 2)
        continent_list = mapy.obtain_continent_list()
        self.assertEqual(continent_list[0].reward, 5)
        self.assertEqual(continent_list[0].country_list, [1 , 2])

    def test_pop(self):
        popy = PopFileParser("population_init.txt")
        country_list = popy.obtain_country_list()
        self.assertEqual(country_list[0].id, 1)
        self.assertEqual(country_list[0].owner_id, GamePlayId.P1)
        self.assertEqual(country_list[0].troops_count, 3)


if __name__ == '__main__':
    unittest.main()
