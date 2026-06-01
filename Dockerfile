FROM gcc:12.2

RUN apt-get update && apt-get install -y \
    make \
    cmake \
    g++ \
    librdkafka-dev \
    libboost-system-dev \
    libboost-thread-dev \
    libboost-dev \
    nlohmann-json3-dev \
    && ln -s /usr/lib/x86_64-linux-gnu/librdkafka++.so /usr/lib/x86_64-linux-gnu/librdkafkacpp.so || true \
    && rm -rf /var/lib/apt/lists/*
WORKDIR /app
COPY . .

RUN make clean && make

CMD ["./test"]