# C++ and Perl HTTP Server

This is a simple HTTP server implemented in C++. It accepts HTTP GET and POST requests and serves web pages. It also provides a simple message service that accepts messages via a POST request and displays the last message received.

## Project Structure
- `src/`: Contains the source code for the server
- `perl/`: Contains the web pages served by the server and contains helper scripts used in building and managing the server

## Build

You can build the project using the provided Makefile:

```bash
make all
```

You can delete the server using the provided Makefile:

```bash
make clean
```

You can stop the server using the provided Makefile:

```bash
make stop
```