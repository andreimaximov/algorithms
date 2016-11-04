#! /bin/bash

BASEDIR=$(dirname "$0")

echo "Testing RangeMap..."
python3 ${BASEDIR}/range_map_test.py

echo "Testing generators..."
python3 ${BASEDIR}/generators_test.py
