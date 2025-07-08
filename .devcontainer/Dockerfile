FROM mdnf1992/cpp-dev AS dev

RUN apt-get update && \
    apt-get install -y \
    libgpiod-dev g++-14 && \
    rm -rf /var/lib/apt/lists/*


FROM dev AS build
COPY . /src

RUN mkdir -p /src/build && \
    cd /src/build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=install && \
    make install


FROM ubuntu:latest AS runtime
ENV LD_LIBRARY_PATH=/usr/local/lib
COPY --from=build /src/build/install /usr/local/
