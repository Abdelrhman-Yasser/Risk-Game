import os 
from game_server.settings import BASE_DIR


class IOHandler:

    @staticmethod
    def read_file(file_name):
        print("base is ", BASE_DIR + "/server_files/" + file_name)
        test_dir = BASE_DIR + "/server_files/" + file_name
        server_dir = BASE_DIR + file_name
        file = open(server_dir)
        lines = file.read().splitlines()
        file.close()
        return lines
