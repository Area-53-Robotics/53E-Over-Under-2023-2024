from dispatch import *
import paho.mqtt.client as mqtt
import time


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


client.loop_start()

try:
    while True:
        # Generate random data (replace this with your data generation logic)

        # TODO: get this data

        dispatch("0,1,2,3", client)

        # Delay for 5 seconds (adjust the interval as needed)
        time.sleep(0.5)
except KeyboardInterrupt:
    print("Disconnecting from MQTT Broker")
    client.disconnect()
