from flask import Flask, jsonify
from flask_cors import CORS, cross_origin
import os, sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from dbConnector import *
from models.Electricity import * 


app = Flask(__name__)
cors = CORS(app)
app.config['CORS_HEADERS'] = 'Content-Type'

data={
    "voltage":230,
    "amps":3,
    "power":2300,
    "enery":23.0,
    "frequency":50.0,
    "power factor":1,
}

@app.route('/readlatest')
@cross_origin()
def get_incomes():
  obj =get_Latest_Record()
  return jsonify(obj)


@app.route('/incomes', methods=['POST'])
def add_income():

  return "", 204


@app.route('/expenses')
def get_expenses():

  return jsonify("expenses.data")


@app.route('/expenses', methods=['POST'])
def add_expense():
  return "", 204


if __name__ == "__main__":
    app.run()