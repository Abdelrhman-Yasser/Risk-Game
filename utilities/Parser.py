from environment.Structures import *
from utilities.IoHandler import IOHandler
import re


class MapFileParser:

    def __init__(self, map_config_file):
        self.__bufferedFile = IOHandler.read_file(map_config_file)
        self.__countryCount = self.__parse_count(0)
        self.__borderCount = self.__parse_count(1)
        index = self.__borderCount + 2
        self.__continentCount = self.__parse_count(index)

    def __tokenize(self, target_line, delimiter='\s|\t|\n|\r|\)|\(|;'):
        tokens = re.split(delimiter,target_line)
        return [x for x in tokens if x != '']

    def __parse_count(self, line_number):
        line = self.__bufferedFile[line_number]
        tokens = self.__tokenize(line)
        return int(tokens[1])

    def obtain_border_list(self):
        border_list = []
        line_number = 2
        count = self.__borderCount
        while count > 0:
            line = self.__bufferedFile[line_number]
            tokens = self.__tokenize(line)
            country1 = int(tokens[0])
            country2 = int(tokens[1])
            border_list.append(Border(country1,country2))
            line_number += 1
            count -= 1
        return border_list

    def obtain_continent_list(self):
        continent_list = []
        line_number = 1 + self.__borderCount + 2
        count = self.__continentCount
        continent_no = 1
        while count > 0:
            line = self.__bufferedFile[line_number]
            tokens = self.__tokenize(line)
            reward = int(tokens[0])
            country_list = []
            for i in range(1, len(tokens)):
                if not tokens[i].isnumeric():
                    break
                country_list.append(int(tokens[i]))
            continent_list.append(Continent(reward, country_list, id=continent_no))
            continent_no += 1
            line_number += 1
            count -= 1
        return continent_list

    def get_country_count(self):
        return self.__countryCount

    def get_border_count(self):
        return self.__borderCount

    def get_continent_count(self):
        return self.__continentCount


class PopFileParser:

    def __init__(self , pop_config_file):
        self.__buffered_file = IOHandler.read_file(pop_config_file)


    def __tokenize(self, target_line, delimiter='\s|\t|\n|\r|\)|\(|;'):
        tokens = re.split(delimiter,target_line)
        return [x for x in tokens if x != '']

    def obtain_country_list(self):
        country_list = []
        for line in self.__buffered_file:
            tokens = self.__tokenize(line)
            country_id = int(tokens[0])
            owner_id = GamePlayId(int(tokens[1]))
            troops_count = int(tokens[2])
            country_list.append(Country(country_id,owner_id,troops_count))
        return country_list

