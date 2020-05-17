FROM ubuntu:18.04

# Setup environment
ENV DEBIAN_FRONTEND noninteractive

# Install development packages
RUN apt-get update && apt-get install -y \
	sudo \
	git \
	mercurial \
	build-essential \
	vim \
	openssh-server \
	software-properties-common \
	bash-completion \
	debian-keyring \
	debian-archive-keyring \
	curl \
	cmake \
	python3 \
	tmux

RUN apt-get update && apt-get install -y \
	clang \
	clang-format \
	clang-tidy \
	python3-pip \
	cppcheck

RUN pip3 install cpplint

RUN mkdir /course
WORKDIR /course
CMD tmux
