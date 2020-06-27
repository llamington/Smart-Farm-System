from flask import Flask, request

app = Flask(__name__)


@app.route('/')
def receive_data():
    received_request = request.args.get('data')
    with open('data_read.txt', 'a') as file:
        file.write(f'{received_request}\n')
    return 'Hello World!'

