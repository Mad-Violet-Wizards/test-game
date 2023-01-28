FROM fedora:latest

WORKDIR /game-engine

RUN dnf update -y 

# RUN dnf groupinstall "Development Tools" "Development Libraries" -y
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

RUN pip3 install --upgrade pip
COPY ./scripts/requirements.txt /game-engine/requirements.txt
RUN pip3 install -r /game-engine/requirements.txt

COPY . /game-engine/

CMD [ "python3", "/game-engine/scripts/linux/build.py", "install" ]
