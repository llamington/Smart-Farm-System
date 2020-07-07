import sqlalchemy as db
import pandas as pd


class Database:
    def __init__(self, address):
        self.address = address
        self.engine = db.create_engine(address)

    def insert_to_db(self, df: pd.DataFrame):
        """inserts dataframe to sql table"""
        df.to_sql('sensor_data', self.engine, index=False, if_exists='append')

    def select_days_prior(self, num_days):
        sql_str = f'''SELECT * FROM sensor_data
            WHERE date_time BETWEEN date_sub(now(),INTERVAL {num_days} DAY) AND now();'''
        selected_days = pd.read_sql_query(sql_str, self.engine, parse_dates=['date_time'])
        return selected_days

    def get_sensor_geodict(self):
        df = pd.read_sql_table('sensors', self.engine, index_col='sensor_id')
        geodict = {
            "type": "FeatureCollection",
            "features": []
        }
        for index, data in df.iterrows():
            geodict['features'].append({
                'type': 'Feature',
                'properties': {
                    'id': index
                },
                'geometry': {
                    'type': 'Point',
                    'coordinates': [data['longitude'], data['latitude']]
                }
            })
        return geodict


if __name__ == '__main__':
    database = Database('mysql://smart-farm-system.covlfra3u7yf.ap-southeast-2.rds.amazonaws.com/smart_farm_system')