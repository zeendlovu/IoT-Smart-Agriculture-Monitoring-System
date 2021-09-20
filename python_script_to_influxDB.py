from datetime import datetime
import serial
import json
from influxdb_client import InfluxDBClient, Point, WritePrecision
from influxdb_client.client.write_api import SYNCHRONOUS

token = "gFHe5KW7hhqEGanlZcOyCdCQc0x6jGfmNYgtf4a7ZNqX3FhR3Kz5L2F-KfJoRHHg2I87fL1vQU6RUdul9WlZ4w=="
org = "zeendlovu15@gmail.com"
bucket = "smartagric"

client2 = InfluxDBClient(url="https://eastus-1.azure.cloud2.influxdata.com", token=token, ssl=True, verify_ssl=True)

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.reset_input_buffer()
    ser.flush()

    while True:
        if ser.in_waiting > 0:
            line = ser.readline()           
            try:
                dict_json = json.loads(line)
                moisture = dict_json.get("Moisture Level")
                temperature = dict_json.get("Temperature")
                volume = dict_json.get("Volume of Water")
                humidity = dict_json.get("Humidity")
                door_state = dict_json.get("Door Status")
                print(dict_json)
                
                write_api = client2.write_api(write_options=SYNCHRONOUS)
                data = "greenhouse_conditions,location=harare temperature="+str(temperature)+",humidity="+str(humidity)+",soil_moisture="+str(moisture)+",water_level="+str(volume)+",door_status="+str(door_state)
                write_api.write(bucket, org, data)
                
            except json.JSONDecodeError as e:
                print("JSON:", e)


