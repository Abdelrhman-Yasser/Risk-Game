from environment.Environment import Environment
from environment.Encoders import Encoder
import json

class EnvState:

    def __init__(self, env, parent):
        self.env = env
        self.parent = parent

    def __eq__(self, other):
        if isinstance(other, EnvState):
            return json.dumps(self.env.reprJson(), cls=Encoder) == json.dumps(other.env.reprJson(), cls=Encoder)
        else:
            return False

    def __hash__(self):
        return hash(json.dumps(self.env.reprJson(), cls=Encoder))
