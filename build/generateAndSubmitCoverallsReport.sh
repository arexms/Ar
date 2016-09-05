#!/bin/bash

lcov --directory . --capture --output-file coverage.info
lcov --remove coverage.info 'tests/*' '/usr/include/*' 'protobuf-3.0.0-bin/*' 'googletest/*' 'googlemock/*' --output-file coverage.info
lcov --list coverage.info
coveralls-lcov --repo-token $COVERALLS_TOKEN coverage.info