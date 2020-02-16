
# Setup
## 0) Clone:
```
$ git clone https://github.com/rkahani/rectangle_detection.git
$ cd rectangle_detection
```

## 1) Building the Docker image:
`$ sudo docker build -t ubuntu_opencv:1604_420 .`

## 2) Running the container:
`$ sudo docker run -it -v ~/rectangle_detection:/home/workspace --name det ubuntu_opencv:1604_420`

## 3) Building the source code:
```
$ cd /home/workspace
$ cmake .
$ make
```

## 4) Running the detector:
`$ ./detector oriental_picture.png`


