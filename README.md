# Console Chat

This is simple client-server chat, which can accept several users at time.

For asynchronous interaction this program use asio framework.

## Build

For build this program, use next instruction:

- create directory "build" and move to it
```bash
mkdir build
cd build
```

- run cmake
```bash
cmake ..
```

- compile executable files for create server and client parts
```bash
make Client
make Server
```

- run server, using free port
```bash
./Server <port>
```

- run client, using ip and port
```bash
./Client <ip> <port>
```