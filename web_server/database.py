import sqlalchemy as db
import pandas as pd


class Database:
    def __init__(self, address):
        self.address = address
        self.engine = db.create_engine(address)

    def insert_to_db(self, df: pd.DataFrame):
        """inserts dataframe to sql table"""
        df.to_sql('sensor_data', self.engine, index=False)


if __name__ == '__main__':
    database = Database('mysql://smart-farm-system.covlfra3u7yf.ap-southeast-2.rds.amazonaws.com/smart_farm_system')