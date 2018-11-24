from enviroment.GameEnums import *


class Enviroment():

    def __init__(self):
        self.gameStatus = GameStatus.ONGOING
        self.winner = GamePlayId.NONE
        self.countryList = []
        self.borderList = []
        self.continList = []