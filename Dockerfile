FROM ubuntu:xenial
RUN apt-get update && apt-get install build-essential -y \
    wget \
    cmake \
    git \
    libgtk2.0-dev \
    pkg-config \
    libavcodec-dev \
    libavformat-dev \
    libswscale-dev \
    libtbb2 \
    libtbb-dev \
    libjpeg-dev \
    libpng-dev \
    libtiff-dev \
    libjasper-dev \
    libdc1394-22-dev
RUN apt-get install -y unzip && \
	wget https://github.com/opencv/opencv/archive/4.2.0.zip && \
	unzip 4.2.0.zip && \
    cd opencv-4.2.0
RUN cd opencv-4.2.0 && \
	mkdir build && \
    cd build && \
    cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local .. && \
	make -j7 && \
    make install



