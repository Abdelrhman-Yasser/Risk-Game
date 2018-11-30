from environment.GameEnums import *
import copy

class Country:

    def __init__(self, id, owner_id,  troops_count , continent_id = -1 ):
        self.owner_id = owner_id
        self.id = id
        self.troops_count = troops_count
        self.continent_id = continent_id

    def __deepcopy__(self, memodict={}):
        return Country(id=copy.deepcopy(self.id,memodict),
                       owner_id=copy.deepcopy(self.owner_id,memodict),
                       troops_count=copy.deepcopy(self.troops_count,memodict),
                       continent_id=copy.deepcopy(self.continent_id,memodict))

    def reprJson(self):
        return dict(owner=self.owner_id.name,
                    id=self.id,
                    troops_count=self.troops_count,
                    continent=self.continent_id)


class Continent:

    def __init__(self, reward, country_list, owner_id=GamePlayId.NONE, id=None):
        self.reward = reward
        self.owner_id = owner_id
        self.country_list = country_list
        self.id = id

    def __deepcopy__(self, memodict={}):
        return Continent(reward=copy.deepcopy(self.reward,memodict),
                         id=copy.deepcopy(self.id,memodict))

    def reprJson(self):
        return dict(reward=self.reward,
                    owner_id=self.owner_id.name)


class Border:

    def __init__(self, country1, country2):
        self.country1 = country1
        self.country2 = country2

    def __deepcopy__(self, memodict={}):
        return Border(copy.deepcopy(self.country1,memodict),
                      copy.deepcopy(self.country2,memodict))

    def reprJson(self):
        return dict(country1=self.country1,
                    country2=self.country2)
