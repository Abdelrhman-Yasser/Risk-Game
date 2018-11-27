from environment.GameEnums import *
from utilities.Parser import *


class Environment:

    INVASION_REWARD = 2

    def __init__(self, map_config_file, pop_config_file):
        self.__game_status = GameStatus.ONGOING
        self.__winner = GamePlayId.NONE
        self.__country_list, self.__border_list, self.__continent_list \
            = self.__readconfigfiles__(map_config_file, pop_config_file)
        for i, continent in enumerate(self.continent_list):
            for country_id in continent.country_list:
                self.country_list[country_id - 1].continent_id = i+1

    def reprJson(self):
        return dict(game_status = self.__game_status.name,
                    winner = self.__winner.name,
                    country_list = self.country_list,
                    border_list = self.border_list,
                    continent_list = self.continent_list)

    def __readconfigfiles__(self, map_config_file, pop_config_file):
        read_data_map = MapFileParser(map_config_file)
        read_data_pop = PopFileParser(pop_config_file)
        return read_data_pop.obtain_country_list(), read_data_map.obtain_border_list()\
            , read_data_map.obtain_continent_list()

    def __border_exists(self, country1_id, country2_id):
        for border in self.border_list:
            if(border.country1 == country1_id and border.country2 == country2_id) or (border.country1 == country2_id and border.country2 == country1_id):
                return True
        return False

    def __is_owner(self, test_player_id , country_id):
        return self.country_list[country_id - 1].owner_id == GamePlayId.NONE or self.country_list[country_id - 1].owner_id == test_player_id

    def __game_ended(self,test_player_id):
        for country in self.country_list:
            if country.owner_id != test_player_id:
                return False
        return True

    def __is_continent_new_owner(self,test_player_id , continent_id):
        if self.continent_list[continent_id - 1].owner_id == test_player_id :
            return 0
        for country_id in self.continent_list[continent_id - 1].country_list:
            if self.country_list[country_id].owner_id != test_player_id:
                return 0
        return 1


    @property
    def game_status(self):
        return self.__game_status

    @game_status.setter
    def game_status(self, game_status):
        self.__game_status = game_status


    @property
    def winner(self):
        return self.__winner

    @property
    def country_list(self):
        return self.__country_list

    @property
    def border_list(self):
        return self.__border_list

    @property
    def continent_list(self):
        return self.__continent_list

    def deploy_reserve_troops(self, owner_id, target_country_id, reserve_count):
        if not self.__is_owner(owner_id, target_country_id):
            raise ValueError("Can't deploy troops to unowned country : country owner ("
                             + str(self.country_list[target_country_id - 1].owner_id) + ") ,"
                             + "player " + str(owner_id) + ")")
        self.country_list[target_country_id - 1].troops_count += reserve_count

    def march_troops(self, owner_id, from_country_id, to_country_id, troops_count):
        if not self.__is_owner(owner_id, from_country_id):
            raise ValueError("Can't march troops from unowned country : country owner ("
                             + str(self.country_list[from_country_id - 1].owner_id) + ") ,"
                             + "player (" + str(owner_id) + ")")
        if not self.__is_owner(owner_id, to_country_id):
            raise ValueError("Can't march troops to unowned country : country owner ("
                             + str(self.country_list[to_country_id - 1].owner_id) + ") ,"
                             + "player (" + str(owner_id) + ")")
        if self.country_list[from_country_id - 1].troops_count - troops_count < 1:
            raise ValueError("Not enough troops to march from ( " + str(from_country_id)
                             + " ) to ( " + str(to_country_id) + " ) troops are in country are "
                             + str(self.country_list[from_country_id - 1].troops_count))
        if not self.__border_exists(from_country_id,to_country_id):
            raise ValueError("Can't march no route from ( " + str(from_country_id)
                             + " ) to ( " + str(to_country_id) + " )")

        self.country_list[from_country_id - 1].troops_count -= troops_count
        self.country_list[to_country_id - 1].troops_count += troops_count

    def invade(self, owner_id, from_country_id, to_country_id):
        if self.__is_owner(owner_id, from_country_id) and self.__is_owner(owner_id, to_country_id):
            raise ValueError("Can't invade your own country")
        if not self.__border_exists(from_country_id,to_country_id):
            raise ValueError("Can't invade no route from ( " + str(from_country_id)
                             + " ) to ( " + str(to_country_id) + " )")
        if not self.__is_owner(owner_id, from_country_id):
            raise ValueError("Can't invade from unowned country : country owner ("
                             + str(self.country_list[from_country_id - 1].owner_id) + ") ,"
                             + "player (" + str(owner_id) + ")")

        i = self.country_list[from_country_id - 1].troops_count
        j = self.country_list[to_country_id - 1].troops_count

        if i-j > 1:
            self.country_list[to_country_id - 1].troops_count = 1
            self.country_list[from_country_id - 1].troops_count -= j+1
            self.country_list[to_country_id - 1].owner_id = self.country_list[from_country_id - 1].owner_id

            continent_id = self.country_list[to_country_id - 1].continent_id
            reward = self.INVASION_REWARD
            if self.__is_continent_new_owner(owner_id,continent_id):
                self.continent_list[continent_id -1].owner_id = owner_id
                reward = self.continent_list[continent_id -1].reward

            if self.__game_ended(owner_id):
                self.__game_status = GameStatus.ENDED
                self.__winner = owner_id

            return reward






