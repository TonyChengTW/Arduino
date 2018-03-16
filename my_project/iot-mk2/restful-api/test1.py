# Tony Cheng <tony.pig@gmail.com>
# Version : 0.1
# Licensed under the Apache License, Version 2.0

import datetime
import time
# import pdb

from flask import Flask, request
from flask_restful import Api, Resource, reqparse

api_bindip = '0.0.0.0'
api_port = 7878
api_debug = True

app = Flask(__name__)
api = Api(app)

parser = reqparse.RequestParser()
parser.add_argument('value1', type=str, required=True)

class Test1(Resource):
    def __init__(self):
        arg = parser.parse_args()
        print "value arg type is:", type(arg)
        print "value is:", arg['value1']
        self.value1 = arg['value1']

    def get(self):
        print "Hello GET user, the arg is ready to GET : "
        print "get_result: ", self.value1
        return (self.value1)
    def post(self):
        print "Hello POST user, the arg is ready to POST : "
        print "post_result: ", self.value1
        return (self.value1)

api.add_resource(Test1, '/test1')

if __name__ == "__main__":
    app.run(host=api_bindip, port=api_port, debug=api_debug)
