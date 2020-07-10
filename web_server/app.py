from flask import Flask, request, render_template, jsonify
import re
import pandas as pd
from database import Database
import password

db = Database(
    f'mysql://admin:{password.password}@smart-farm-system.covlfra3u7yf.ap-southeast-2.rds.amazonaws.com/smart_farm_system')
app = Flask(__name__)

ABBREVIATIONS = {
    'H': 'air_humidity',
    'T': 'air_temperature',
    'A': 'ultraviolet_a',
    'B': 'ultraviolet_b',
    'I': 'ultraviolet_index',
    'M': 'soil_humidity',
    'S': 'soil_temperature',
    'P': 'ph',
    'C': 'battery_percentage'
}


@app.route('/')
def receive_data():
    """route to send sensor data"""
    received_request = request.args.get('data')

    if received_request:
        received_list_raw = re.split(r'(\w-?[\d.]*)', received_request)
        received_list = list(filter(None, received_list_raw))
        values_dict = {}

        for value in received_list:
            key = ABBREVIATIONS[value[0]]
            values_dict[key] = float(value[1:])

        values_df = pd.DataFrame(values_dict, index=[0])
        values_df['date_time'] = pd.to_datetime('now')
        values_df['sensor_id'] = 1  # CHANGE THIS WHEN MULTIPLE SENSORS ARE FUNCTIONAL
        print(values_df)
        db.insert_to_db(values_df)
        # with open('data_read.txt', 'a') as file:
        #     file.write(f'{received_request}\n')
    return 'Hello World!'


@app.route('/dashboard')
def dashboard():
    """routing for dashboard which displays data collected"""
    return render_template('dashboard.html')


@app.route('/api/sensor_data')
def get_sensor_data():
    """fetches sensor data from the database"""
    period = request.args.get('period')
    sensor_type = request.args.get('sensor_type')
    sensor_id = request.args.get('sensor_id')
    if period:
        df = db.select_days_prior(period, sensor_type, sensor_id)
        df['date_time'] = df['date_time'].dt.strftime('%Y-%m-%d')
        data_dict = {'values': df[sensor_type].to_list(), 'date_time': df['date_time'].to_list()}
        return jsonify(data_dict)
    else:
        return jsonify(db.get_latest_value(sensor_type, sensor_id))


@app.route('/api/sensors_geojson')
def sensors_geojson():
    sensor_geodict = db.get_sensor_geodict()
    return jsonify(sensor_geodict)
# if __name__ == 'main':
#     app.run(host='0.0.0.0')
