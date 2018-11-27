from environment import *
import json 


class Encoder(json.JSONEncoder):
    def default(self, o):
        if hasattr(o,'reprJson'):
          return o.reprJson()
        else:
          return json.JSONEncoder.default(self,o)
