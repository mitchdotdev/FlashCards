FROM gcc:4.9
WORKDIR /flashCard
COPY . /flashCard
RUN g++ -std=c++14 -lsqlite3 -lcurses -o flash src/main.cpp src/menus.cpp src/db.cpp
CMD ["./flash"]
