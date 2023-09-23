import json
import random

types = {
    "pid": ["P", "I", "D"],
    "left_motor_temperature": ["Left 1", "Left 2", "Left 3"],
    "right_motor_temperature": ["Right 1", "Right 2", "Right 3"],
}

routes = [
    {"type": "pid", "topic": "pid/linear"},
    {"type": "pid", "topic": "pid/angular"},
]


def dispatch(data, client):
    raw_data = [int(x) for x in data.split(",")]
    data_dict = {}
    topic = routes[raw_data[0]]["topic"]
    type = routes[raw_data[0]]["type"]
    for index, label in enumerate(types[type]):
        data_dict[label] = raw_data[index + 1]
    json_data = json.dumps(data_dict)

    client.publish(topic, json_data)
