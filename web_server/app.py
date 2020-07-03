from flask import Flask, request
import re
import pandas as pd

app = Flask(__name__)

ABBREVIATIONS = {
    'H': 'Air Humidity',
    'T': 'Air Temperature',
    'A': 'Ultraviolet A',
    'B': 'Ultraviolet B',
    'I': 'Ultraviolet Index',
    'M': 'Soil Humidity',
    'S': 'Soil Temperature',
    'P': 'pH',
    'C': 'Battery Percentage'
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
        print(values_df)

        with open('data_read.txt', 'a') as file:
            file.write(f'{received_request}\n')
    return 'Hello World!'


# if __name__ == 'main':
#     app.run(host='0.0.0.0')
