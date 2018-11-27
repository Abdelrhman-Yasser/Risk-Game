import os 
from game_server.settings import BASE_DIR


class IOHandler:

    @staticmethod
    def read_file(file_name):
        print("base is ", BASE_DIR + file_name)
        file = open(BASE_DIR + file_name)
        lines = file.read().splitlines()
        file.close()
        return lines
