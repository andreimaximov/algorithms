#! /bin/bash

BASEDIR=$(dirname "$0")

cpplint $(find ${BASEDIR} -name \*.h -or -name \*.cpp)
pep8 $(find ${BASEDIR} -name \*.py)
