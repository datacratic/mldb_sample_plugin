FROM quay.io/datacratic/mldb_sdk:jeremy_latest

COPY . /build
RUN cd /build && make -j2 -k
