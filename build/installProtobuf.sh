if [ -d 'protobuf-3.0.0' ]; then
    echo "protobuf already installed"
else
    echo "Downloading protobuf..."
    wget https://github.com/google/protobuf/releases/download/v3.0.0/protobuf-cpp-3.0.0.tar.gz
    tar xvfz protobuf-cpp-3.0.0.tar.gz
    rm protobuf-cpp-3.0.0.tar.gz
    ( cd protobuf-3.0.0 && ./configure --prefix=$HOME/protobuf-3.0.0-bin && make -j2 && make install )
fi
