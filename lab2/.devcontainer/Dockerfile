FROM gcc:14.2.0

RUN apt-get update && apt-get install -y \
    cmake \
    git \
    libgtest-dev \
    && rm -rf /var/lib/apt/lists/*

RUN cd /usr/src/gtest && \
    cmake . && \
    make && \
    mv lib/libgtest*.a /usr/lib

WORKDIR /workspace

COPY ../ /workspace

RUN ls -la /workspace

RUN mkdir build
WORKDIR /workspace/build

RUN cmake .. && make