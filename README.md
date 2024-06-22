# ScanX

ScanX is a Light-weight TCP Port Scanner. It attempts to connect to a list of ports on a specified host to check which ports are open.

## Features

- Scans a range of ports on a given hostname or IP address.
- Displays open ports.

## Prerequisites

- A C compiler (e.g., `gcc`).

## Installation and Usage

1. Clone the repository or download the source code files.
2. Compile the source code using a C compiler.
3. Run the compiled executable with the hostname/IP address and port range as arguments.

Example command:

```bash
gcc -o ScanX scanx.c && ./ScanX example.com 1 1024
