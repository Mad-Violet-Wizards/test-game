FROM fedora:latest

WORKDIR /game-engine

RUN dnf update -y 

RUN dnf group install "Development Tools" -y

# RUN python3 -m venv /home/test-game/venv
COPY ./scripts/requirements.txt /$WORKDIR/requirements.txt
RUN pip3 install -r /game-engine/requirements.txt

COPY . /$WORKDIR/

CMD [ "python3", "/game-engine/scripts/linux/build.py", "build" ]

