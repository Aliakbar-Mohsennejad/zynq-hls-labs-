#  Zynq HLS Labs

> A collection of **system-level digital design experiments** implemented using **Vivado HLS** and deployed on **Xilinx Zynq-7000**.  
> These projects were originally developed in **SystemC (Visual Studio)** and later migrated to **HLS-based hardware design** for FPGA/SoC platforms.  

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

---

##  Overview
This repository demonstrates **hardware-software co-design** using High-Level Synthesis (HLS).  
It includes six experiments covering fundamental digital design concepts such as logic gates, ALU, register banks, FSM, and interrupt handling.

- **Platform:** Zynq-7000 (xc7z020clg400-1)  
- **Tools:** Vivado HLS, C++  
- **Skills:** RTL generation, testbench design, hardware/software co-simulation, resource optimization  

📄 Full project report (English): [docs/HLS_Project_Report_English.docx](./docs/HLS_Project_Report_English.docx)  
📄 Original report (Persian): [docs/projectHLS_Alemi_MohsenNejad.pdf](./docs/projectHLS_Alemi_MohsenNejad.pdf)  

---

## Experiments

| #  | Title                | Key Focus                          | Folder |
|----|----------------------|-------------------------------------|--------|
| 01 | XOR Gate             | Simple logic design in HLS         | [lab01-xor](./lab01-xor) |
| 02 | ALU (8-bit)          | Arithmetic & logic ops, flags (C/Z/N/V) | [lab02-alu](./lab02-alu) |
| 03 | Register Bank        | 256×8-bit memory with RW priority  | [lab03-regbank](./lab03-regbank) |
| 04 | FSM                  | IDLE / LOAD / COUNT_UP / COUNT_DOWN | [lab04-fsm](./lab04-fsm) |
| 05 | Single Interrupt     | Interrupt handling with ISR        | [lab05-single-intr](./lab05-single-intr) |
| 06 | Multi Interrupt      | Priority-based interrupt controller | [lab06-multi-intr](./lab06-multi-intr) |

---

## 📊 Key Results
- **Latency:** Most designs operate in **1–2 clock cycles**.  
- **Timing:** Achieved **<5 ns clock period**, much faster than the 10 ns target.  
- **Resources:** Minimal LUT/FF/BRAM usage → efficient and scalable.  
- **Interrupts:** Correct ISR handling and priority enforcement confirmed via testbenches.  

---

##  Repository Structure
```
zynq-hls-labs/
├─ README.md
├─ LICENSE
├─ docs/                         # Reports & diagrams
│  ├─ projectHLS_Alemi_MohsenNejad.pdf
│  └─ HLS_Project_Report_English.docx
├─ lab01-xor/
├─ lab02-alu/
├─ lab03-regbank/
├─ lab04-fsm/
├─ lab05-single-intr/
├─ lab06-multi-intr/
└─ .github/workflows/            # CI for build/test
```

---

##  Build & Run

### Software Simulation
```bash
# Example: build ALU testbench
cd lab02-alu
g++ alu_hls.cpp tb_alu.cpp -o alu_test
./alu_test
```

### Hardware Synthesis (Vivado HLS)
1. Open Vivado HLS.  
2. Set target device: `xc7z020clg400-1`  
3. Import source files from experiment folder.  
4. Run **C Simulation**, **Synthesis**, and **RTL Export**.  

---

##  Related Work
- 🔹 Previous SystemC implementation: [SystemC-Lab-Projects](https://github.com/Aliakbar-Mohsennejad/SystemC-Lab-Projects)  

---

##  License
This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details.

---

##  Authors
- **Mohammad Hossein Alemi Rostami**  
- **Ali Akbar MohsenNejad**  
