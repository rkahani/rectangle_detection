
# Setup
## 1) Building the docker image:
`$ sudo docker build -t ubuntu_opencv:1604_420 .`

## 2) Running the container:
`$ sudo docker run -it -v ~/red_rectangle_detector:/home/workspace --name det ubuntu_opencv:1604_420`

## 3) Building the source code:
```
$ cd /home/workspace
$ cmake .
$ make
```

## 4) Running the detector:
`$ ./detector oriental_picture.png`


