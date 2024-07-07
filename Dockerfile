FROM gcc:latest
LABEL authors="mahdi"

ENTRYPOINT ["top", "-b"]