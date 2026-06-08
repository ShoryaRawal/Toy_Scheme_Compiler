FROM debian:bookworm-slim

RUN apt-get update && \
    apt-get install -y \
        build-essential \
        clang \
        gcc \
        gdb \
        cmake \
        make \
        git && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /src
