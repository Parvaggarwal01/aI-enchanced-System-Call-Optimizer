# AI-Enhanced System Call Optimization (Process Scheduler)

## Overview
This project implements an **AI-based process scheduler** to optimize system call processing and reduce latency in an OS. The AI-enhanced scheduler prioritizes processes dynamically, improving responsiveness for interactive tasks while managing long-running jobs efficiently.

## Features
- **Process scheduling** using FIFO and AI-based optimization.
- **Dynamic priority assignment** based on execution history.
- **Performance comparison** between traditional FIFO and AI scheduling.
- **Test cases** to measure execution time and latency.

## Installation
### Prerequisites
Ensure you have **GCC** and **Make** installed:
```sh
sudo apt update && sudo apt install build-essential
```

### Clone the Repository
```sh
git clone https://github.com/your-username/ai-process-scheduler.git
cd ai-process-scheduler
```

### Compile the Code
```sh
gcc -Wall scheduler.c ai_module.c -o scheduler
```

## Usage
Run the scheduler with a test case file:
```sh
./scheduler 
```

## Test Case Format
Each test case file contains processes in the format:
```
<Process_ID> <Process_Name> <Arrival_Time> <Execution_Time>
```
Example (`test_cases/test1.txt`):
```
1 editor 0 150
2 browser 2 450
3 compiler 4 800
4 network 6 350
```

## Expected Behavior
### FIFO Execution Order
1. editor → browser → compiler → network
2. Higher total wait time for short tasks

### AI-Based Execution Order
1. editor → network → browser → compiler
2. Improved responsiveness for interactive processes

## Measuring Performance
To analyze performance, run:
```sh
strace -c ./scheduler test_cases/test1.txt
```
This measures system calls and execution time differences between FIFO and AI scheduling.

## Contributions
Contributions are welcome! Fork the repo, make improvements, and submit a PR.

## License
This project is licensed under the MIT License. See `LICENSE` for details.
