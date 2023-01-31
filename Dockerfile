FROM fedora:latest

# Changing the working directory to /game-engine
WORKDIR /game-engine

# Installing the dependencies
RUN dnf update -y

RUN dnf groupinstall "Development Tools" "Development Libraries" -y

RUN dnf install cmake g++ make systemd-devel \
    glew-devel SDL2-devel SDL2_image-devel \
    glm-devel freetype-devel \
    libfontenc-devel libXaw-devel \
    libXcomposite-devel libXcursor-devel \
    libXdmcp-devel libXtst-devel \
    libXinerama-devel libxkbfile-devel\
    libXrandr-devel libXres-devel \
    libXScrnSaver-devel libXvMC-devel\
    xcb-util-wm-devel xcb-util-image-devel\
    xcb-util-keysyms-devel xcb-util-renderutil-devel\
    libXdamage-devel libXxf86vm-devel \
    libXv-devel xcb-util-devel libuuid-devel -y
RUN dnf install python3-pip -y


# Installing the python dependencies
RUN pip3 install --upgrade pip
COPY ./scripts/requirements.txt /game-engine/requirements.txt
RUN pip3 install -r /game-engine/requirements.txt

# Copying the source code
COPY ./assets_raw /game-engine/assets_raw
COPY ./build /game-engine/build
COPY ./external /game-engine/external
COPY ./src /game-engine/src
COPY ./tools /game-engine/tools
COPY ./CMakeLists.txt ./conanfile.txt  /game-engine/
COPY ./scripts/linux/utility /game-engine/scripts/linux/utility



COPY ./scripts/linux/build.py /game-engine/scripts/linux/build.py
# Building the game engine
RUN python3 /game-engine/scripts/linux/build.py install
RUN python3 /game-engine/scripts/linux/build.py build
RUN python3 /game-engine/scripts/linux/build.py release