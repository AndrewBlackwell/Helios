# Base image: Ubuntu 20.04
FROM ubuntu:20.04

# Set environment variables
ENV HOME /root

# Update and install dependencies
RUN apt-get update && apt-get upgrade -y
RUN apt-get install -y build-essential cmake

# Create a working directory
RUN mkdir $HOME/Helios
WORKDIR $HOME/Helios

# Copy all project files into the container
COPY ./ $HOME/Helios

# Run CMake to configure and build the project
RUN cmake -B build
RUN cmake --build build

# Set up a directory for output images
WORKDIR /output

# Default command to run the compiled binary
ENTRYPOINT ["/root/Helios/build/helios"]

# To run: 
#     docker build -t heliosrt .
#     docker run -v $(pwd)/images:/output heliosrt > images/output.ppm

# Mounts the local images/ directory to the container’s /output folder.
# The output.ppm file will be saved in the local images/ directory.