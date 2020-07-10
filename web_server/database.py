import sqlalchemy as db
import pandas as pd


class Database:
    def __init__(self, address):
        self.address = address
        self.engine = db.create_engine(address)

    def insert_to_db(self, df: pd.DataFrame):
        """inserts dataframe to sql table"""
        df.to_sql('sensor_data', self.engine, index=False, if_exists='append')

    def select_days_prior(self, num_days, sensor_type, sensor_id):
        sql_str = f'''SELECT {sensor_type}, date_time FROM sensor_data
            WHERE date_time BETWEEN date_sub(now(),INTERVAL {num_days} DAY) AND now() AND sensor_id = {sensor_id};'''
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

    def get_latest_value(self, sensor_type, sensor_id):
        """gets latest value for selected column"""
        latest_date_sql = f"""SELECT {sensor_type} FROM sensor_data
            WHERE date_time IN (SELECT max(date_time) FROM sensor_data) AND sensor_id = {sensor_id};"""
        latest_value = pd.read_sql_query(latest_date_sql, self.engine)
        return latest_value.iloc[0][0]


if __name__ == '__main__':
    database = Database('mysql://smart-farm-system.covlfra3u7yf.ap-southeast-2.rds.amazonaws.com/smart_farm_system')