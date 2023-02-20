FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y gcc && \
    rm -rf /var/lib/apt/lists/*

COPY ./app

WORKDIR /app

RUN gcc -o manager pid.c manager.c -lpthread

CMD ["./manager"]
