# IoT-Smart-Agriculture-Monitoring-System
Iot agriculture smart monitoring system with grafana and InfluxDB

Components required:
Soil Moisture Sensor
DHT11
Ultrasonic sensor
Magnetic contact switch

Arduino packages required
ArduinoJson 6+
dht.h

Create online InfluxDB and Grafana accounts
Run Sensor_Readings.ino in the arduino IDE after connections
Log into the rasbperry pi using VNC and in the thorny IDE run python_script_to_influxDB.py
Log into the cloud influxDB and view data coming from the raspberry pi
Log into the cloud Grafana and go to settings and add a data source of influxdb then create a new dashboard
select influxdb on the name of datasource and view data coming from influxdb
