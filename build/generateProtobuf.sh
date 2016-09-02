#!/bin/bash

if md5sum -c protobuf.md5; then
    echo "Protobuf up to date";
else
    echo "Generating protobuf...";
    protoc -I../includes/Ar/Raspi/Messages/ --cpp_out=. ../includes/Ar/Raspi/Messages/RaspiMessages.proto;
    mv RaspiMessages.pb.h ../includes/Ar/Raspi/Messages/
    sed -i "1i/// @date `date`" RaspiMessages.pb.cc
    sed -i 's|include \"RaspiMessages.pb.h\"|include <Ar/Raspi/Messages/RaspiMessages.pb.h>|g' RaspiMessages.pb.cc
    mv RaspiMessages.pb.cc ../sources/Ar/Raspi/Messages/RaspiMessages.pb.cpp
    md5sum ../includes/Ar/Raspi/Messages/RaspiMessages.proto > protobuf.md5
fi
