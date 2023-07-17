# Simple HTTP Server

This is a simple HTTP server implemented in C++. It accepts HTTP GET and POST requests and serves static HTML pages. It also provides a simple message service that accepts messages via a POST request and displays the last message received.

## Project Structure
- `src/`: Contains the source code for the server
- `web/`: Contains static HTML pages served by the server
- `src/perl/`: Contains helper perl scripts used in building and managing the server

## Build

You can build the project using the provided Makefile:

```bash
make all
```