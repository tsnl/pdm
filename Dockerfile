FROM ubuntu

WORKDIR /usr/tsnl/
RUN apt update
RUN apt install git llvm make cmake
COPY . .

EXPOSE 8080
