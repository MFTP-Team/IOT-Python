from flask import Flask, jsonify, request
from flask_restful import Resource, Api, reqparse
import json

import sendUtil

app = Flask(__name__)
api = Api(app)

class AlertReceive(Resource):
    def post(self):
        json_data = request.get_json(force=True)
        lat = json_data['latitude']
        long = json_data['longitude']
        intensity = json_data['intensity']
        print(type(json_data))
        sendUtil.sendUARTMessage(json.dumps(json_data))
        return jsonify(latitude=lat, longitude=long, intensity=intensity)

api.add_resource(AlertReceive, '/alert')

def startAPI():
    app.run(debug=True)