import paho.mqtt.client as mqtt
import time
import random
import json


def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker")
    else:
        print(f"Connection failed with code {rc}")


client = mqtt.Client(client_id="53E-mosquito-bridge")
client.on_connect = on_connect

broker_address = "localhost"
port = 1883
client.connect(broker_address, port)

topic = "hello/py"

client.loop_start()

try:
    while True:
        # Generate random data (replace this with your data generation logic)
        d = random.randint(0, 100)

        data = {
            "p": random.randint(0, 100),
            "i": random.randint(0, 100),
            "d": random.randint(0, 100),
        }

        json_data = json.dumps(data)

        # Publish the random data to the topic
        client.publish(topic, json_data)

        # Delay for 5 seconds (adjust the interval as needed)
        time.sleep(0.5)
except KeyboardInterrupt:
    print("Disconnecting from MQTT Broker")
    client.disconnect()
