# Raspberry gRPC LED Controller
Simple C++ GPIO(LED) controller for raspberry pi 5 using docker


## Build

This will build and save an image to an archive. Copy the archive to the target and use `docker load < blinky.tar.gz`

 - `docker build --platform linux/arm64 -t blinky -f .devcontainer/Dockerfile . && docker save blinky > blinky.tar.gz`

## Use

After copying and loading the image, run `docker run --device /dev/gpiochip0 -p 50051:50051 --init --rm -it blinky blinky gpiochip0`.

Via gRPC, use the given grpc/blinky.proto to control the LED via any client.


## Resources

- ![Pinout](https://www.hackatronic.com/wp-content/uploads/2024/03/Raspberry-Pi-5-Pinout-.jpg)