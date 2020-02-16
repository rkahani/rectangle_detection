# Setup using docker
## 1) Build -> image:
`sudo docker build -t ubuntu_opencv:1604_420 .`

## 2) Run -> container:
`sudo docker run -it -v ~/red_rectangle_detector:/home/workspace --name det rkahani/ubuntu_opencv:1604_420`

## 3) Build -> src:
`cd /home/workspace
cmake .
make`

## 4) Run -> detector:
`./detector oriental_picture.png`



