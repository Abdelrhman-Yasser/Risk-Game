from environment.GameEnums import *


class Country:

    def __init__(self, id, owner_id,  troops_count):
        self.owner_id = owner_id
        self.id = id
        self.troops_count = troops_count
        self.continent_id = -1

    def reprJson(self):
        return dict(owner_id = self.owner_id.name,
                    id = self.id,
                    troops_count = self.troops_count,
                    continent_id = self.continent_id)            


class Continent:

    def __init__(self, reward, country_list):
        self.reward = reward
        self.owner_id = GamePlayId.NONE
        self.country_list = country_list

    def reprJson(self):
        return dict(reward = self.reward,
                    owner_id = self.owner_id.name,
                    country_list = self.country_list) 


class Border:

    def __init__(self, country1, country2):
        self.country1 = country1
        self.country2 = country2

    def reprJson(self):
        return dict(country1 = self.country1,
                    country2 = self.country2)
