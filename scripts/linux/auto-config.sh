#!/usr/bin/env bash
set -e

# This script is used to install dependencies and build the project


OS=$(cat /etc/os-release | grep -w "ID" | cut -d "=" -f 2)

if [[ "$OS" == "fedora" ]]; then
    packet_manager="dnf"
    elif [[ "$OS" == "ubuntu" || "$OS" == "mint" || "$OS" == "debian" ]]; then
    packet_manager="apt"
else
    echo "Your OS is not supported"
fi


echo -n "Do you agree to install dependencies and update your system? [Y/n] "
read -r answer


if [[ "$answer" == "y" || "$answer" == "" ]]; then
    sudo "$packet_manager" install -y cmake g++ make systemd-devel \
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
    if [[ "$packet_manager" == "dnf" ]]; then
        sudo dnf groupinstall "Development Tools" "Development Libraries" -y
        elif [[ "$packet_manager" == "apt" ]]; then
        sudo apt install build-essential -y
    fi
    elif [[ "$answer" == "n" ]]; then
    echo "Skipping $2"
else
    echo "Invalid parameter"
fi

echo -n "Do you agree to create virtual environment and install pip dependencies? [Y/n] "
read -r answer

if [[ "$answer" == "y" || "$answer" == "" ]]; then
    pip install --upgrade pip
    python3 -m venv venv
    source venv/bin/activate
    if [[ -f "requirements.txt" ]]; then
        pip install -r ../requirements.txt
    else
        echo "requirements.txt not found (possible path test-game/scripts/requirements.txt)"
    fi
    elif [[ "$answer" == "n" ]]; then
    echo "Skipping $2"
else
    echo "Invalid parameter"
fi

echo -n "Do you agree to build the project? [Y/n] "
read -r answer

if [[ "$answer" == "y" || "$answer" == "" ]]; then
    if [[ -x "build.py" && -f "build.py" ]]; then
        chmod +x build.py
    else
        echo "build.py not found (possible path test-game/scripts/linux/build.py)"
    fi
    ./build.py install &&
    ./build.py build &&
    ./build.py release
    elif [[ "$answer" == "n" ]]; then
    exit 0
else
    echo "Invalid parameter"
fi

exit 0


