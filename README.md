# VoltWatch

### Embedded Battery Monitoring & Automated System Verification Platform

VoltWatch is a personal engineering project focused on the design, development, and verification of an embedded battery monitoring system.

The project is being developed as a practical exploration of **embedded systems, Battery Management Systems (BMS), automated system verification, hardware validation, test automation, and CI/CD**.

The ultimate goal is to build a small-scale BMS platform and, more importantly, a professional verification environment capable of automatically testing its hardware and software behaviour.

> **Project status:** 🚧 In Development

---

## 🎯 Project Objective

Modern Battery Management Systems are complex safety-critical systems combining hardware, embedded software, communications, sensing, and sophisticated verification processes.

VoltWatch aims to reproduce a simplified version of this development and verification environment on a laboratory bench.

The system will use a microcontroller to monitor simulated battery cells, identify abnormal operating conditions, communicate system status, and expose its behaviour to an automated Python-based verification framework.

Rather than focusing solely on making the BMS work, VoltWatch is being developed with a **verification-first mindset**.

The project will explore questions such as:

* How should system requirements be defined?
* How can requirements be traced to verification tests?
* How can faults be injected in a controlled and repeatable way?
* How can hardware and embedded software be tested automatically?
* How can regression testing be integrated into a CI/CD pipeline?
* How can test results and failures be documented?
* How can an embedded system be verified throughout its development lifecycle?

---

# 🏗️ Planned System

The initial system will consist of a microcontroller-based battery monitoring unit connected to a simulated battery pack.

Potentiometers will initially be used to provide adjustable analogue inputs representing individual battery-cell voltages.

The system will progressively evolve from a simple single-cell measurement system into a multi-cell BMS verification platform.

```text
                    ┌─────────────────────┐
                    │   Simulated Battery │
                    │       Pack          │
                    │                     │
                    │  Cell 1 ─ Potentiometer
                    │  Cell 2 ─ Potentiometer
                    │  Cell 3 ─ Potentiometer
                    │       ...           │
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │      ADuCM320       │
                    │   Embedded System   │
                    │                     │
                    │  ADC Measurement    │
                    │  Fault Detection    │
                    │  State Management   │
                    │  Communications     │
                    └──────────┬──────────┘
                               │
                         UART / CAN
                               │
                               ▼
                    ┌─────────────────────┐
                    │   Python Test       │
                    │     Framework       │
                    │                     │
                    │ Automated Tests     │
                    │ Fault Injection     │
                    │ Regression Testing  │
                    │ Test Reporting      │
                    └──────────┬──────────┘
                               │
                               ▼
                    ┌─────────────────────┐
                    │   CI/CD Pipeline    │
                    │                     │
                    │ Build                │
                    │ Test                │
                    │ Report              │
                    │ Regression          │
                    └─────────────────────┘
```

---

# 🔧 Hardware

The project will initially use:

* **ADuCM320 development board** — primary embedded platform
* Potentiometers — simulated battery-cell voltage inputs
* Breadboard and supporting components
* USB/UART interface
* Multimeter and other bench test equipment where appropriate

Additional hardware may be introduced as the project develops, including:

* Arduino / ESP development boards
* CAN interface hardware
* External sensors
* Hardware-in-the-loop interfaces

The hardware architecture will evolve alongside the software and verification requirements.

---

# 💻 Software

### Embedded

The embedded firmware will be primarily developed in:

* C
* ADuCM320 SDK / peripheral libraries
* ARM Cortex-M development tools

The firmware will progressively implement:

* ADC acquisition
* Voltage measurement
* Signal processing
* Battery-cell monitoring
* Fault detection
* System state management
* Communications
* Diagnostics

---

### Test & Automation

Python will be used to develop an automated system verification framework.

The framework will eventually be capable of:

* Communicating with the embedded system
* Configuring test conditions
* Monitoring system outputs
* Injecting faults
* Validating expected behaviour
* Running regression tests
* Generating test reports
* Recording test logs

The objective is to move testing away from manual observation towards **repeatable, automated verification**.

---

### Version Control & CI/CD

Git will be used throughout the project.

The repository will eventually incorporate automated CI/CD processes to:

1. Build the firmware
2. Execute software tests
3. Execute automated verification tests where possible
4. Generate test results
5. Store test artefacts
6. Detect regressions

The project will use meaningful commits and maintain a clear development history.

---

# 🧪 Verification Strategy

VoltWatch will be developed using a requirements-driven verification approach.

Rather than developing features first and testing them afterwards, requirements will be defined and mapped to verification activities.

For example:

```text
Requirement
    │
    ▼
REQ-BMS-002

"The system shall detect cell
undervoltage below 3.00 V."
    │
    ▼
Verification Test
    │
    ▼
TEST-BMS-014

Set simulated cell voltage to 2.80 V
    │
    ▼
Expected Result
    │
    ▼
Undervoltage fault asserted
    │
    ▼
PASS / FAIL
```

A requirements traceability matrix will be maintained as the project develops.

---

# ⚠️ Planned Fault Injection

A major component of VoltWatch will be controlled fault injection.

The system will eventually be tested against conditions such as:

* Cell undervoltage
* Cell overvoltage
* Excessive temperature
* Sensor failures
* Invalid measurements
* Communication loss
* Corrupted data
* Missing messages
* Startup failures
* Unexpected resets
* Recovery from fault conditions

The objective is not simply to demonstrate that the system works under normal conditions.

The objective is to determine **how the system behaves when things go wrong**.

---

# 📊 Planned Test Framework

The Python verification framework will eventually provide automated tests similar to:

```text
TEST-BMS-001   Normal Cell Voltage
TEST-BMS-002   Cell Undervoltage
TEST-BMS-003   Cell Overvoltage
TEST-BMS-004   Voltage Recovery
TEST-BMS-005   ADC Measurement Accuracy
TEST-BMS-006   Communication Timeout
TEST-BMS-007   Invalid Measurement
TEST-BMS-008   System Reset Recovery
```

Example future test output:

```text
VoltWatch System Verification
=============================

TEST-BMS-001  Normal Voltage       PASS
TEST-BMS-002  Undervoltage         PASS
TEST-BMS-003  Overvoltage          PASS
TEST-BMS-004  Voltage Recovery     PASS
TEST-BMS-005  ADC Accuracy         PASS
TEST-BMS-006  Communication Loss   PASS

---------------------------------
Tests: 6
Passed: 6
Failed: 0
Result: PASS
```

---

# 📋 Requirements & Traceability

Requirements will be assigned unique identifiers and linked to their corresponding verification tests.

Example:

| Requirement | Description                       | Verification |
| ----------- | --------------------------------- | ------------ |
| REQ-BMS-001 | Measure cell voltage periodically | TEST-BMS-001 |
| REQ-BMS-002 | Detect cell undervoltage          | TEST-BMS-002 |
| REQ-BMS-003 | Detect cell overvoltage           | TEST-BMS-003 |
| REQ-BMS-004 | Report detected faults            | TEST-BMS-004 |

This approach will allow the project to demonstrate traceability from:

**Requirement → Implementation → Test → Result**

---

# 🚀 Development Roadmap

## Phase 1 — Embedded Foundations

* [ ] Set up ADuCM320 development environment
* [ ] Create initial firmware project
* [ ] Configure ADC
* [ ] Read analogue input
* [ ] Output raw ADC measurements
* [ ] Convert ADC measurements to voltage
* [ ] Establish UART communication
* [ ] Create initial firmware architecture

---

## Phase 2 — Battery Cell Monitoring

* [ ] Implement single-cell monitoring
* [ ] Define voltage operating limits
* [ ] Implement undervoltage detection
* [ ] Implement overvoltage detection
* [ ] Implement basic fault states
* [ ] Expand to multiple simulated cells
* [ ] Implement measurement filtering
* [ ] Investigate ADC accuracy and noise

---

## Phase 3 — Automated Verification

* [ ] Create Python test framework
* [ ] Establish communication with embedded system
* [ ] Implement automated voltage tests
* [ ] Implement fault verification
* [ ] Implement automated regression tests
* [ ] Generate test reports
* [ ] Store test logs and results

---

## Phase 4 — Automotive Communications

* [ ] Introduce CAN communication
* [ ] Define CAN message structure
* [ ] Implement CAN transmission
* [ ] Implement CAN reception
* [ ] Develop automated CAN verification
* [ ] Test communication failures
* [ ] Implement communication diagnostics

---

## Phase 5 — CI/CD

* [ ] Configure Git-based CI/CD
* [ ] Automate firmware builds
* [ ] Execute software tests automatically
* [ ] Generate automated test reports
* [ ] Implement regression testing
* [ ] Store build and test artefacts

---

## Phase 6 — Advanced Verification

* [ ] Automated fault injection
* [ ] Hardware-in-the-loop testing
* [ ] Requirements traceability
* [ ] Test coverage analysis
* [ ] System-level stress testing
* [ ] Long-duration reliability testing

---

## Phase 7 — Security & Wireless

Future investigation areas include:

* [ ] Wireless communication
* [ ] Wireless fault testing
* [ ] Firmware update mechanisms
* [ ] Firmware integrity verification
* [ ] Digital firmware signing
* [ ] Secure boot concepts
* [ ] OTA update security testing

---

# 📁 Repository Structure

The repository will evolve as the project develops.

The planned structure is:

```text
VoltWatch/
│
├── firmware/
│   ├── src/
│   ├── include/
│   └── tests/
│
├── verification/
│   ├── tests/
│   ├── test_data/
│   └── reports/
│
├── hardware/
│   ├── schematics/
│   ├── datasheets/
│   └── photos/
│
├── requirements/
│
├── docs/
│
├── ci/
│
└── README.md
```

---

# 🧠 Engineering Approach

VoltWatch is being developed with an emphasis on **engineering process as well as implementation**.

Key principles include:

### Requirements-driven development

Features should originate from clearly defined requirements.

### Verification from the beginning

Testing should be considered during system design rather than after implementation.

### Automation

Where a test can be automated, the long-term objective is to automate it.

### Reproducibility

Tests should produce repeatable results and preserve relevant logs and data.

### Traceability

Requirements, implementation, tests, and results should be linked.

### Fault-focused testing

A system should be tested not only for what it is expected to do, but also for how it behaves when exposed to unexpected conditions.

### Continuous improvement

The project will evolve through incremental development, testing, measurement, and documentation.

---

# 🎓 Learning Objectives

VoltWatch is intended to provide practical experience in:

* Embedded C development
* ARM microcontroller programming
* ADCs and analogue measurement
* Battery monitoring systems
* Embedded system architecture
* Hardware/software integration
* Automated system verification
* Python test automation
* Fault injection
* Regression testing
* CAN communications
* Git and version control
* CI/CD
* Requirements management
* Requirements traceability
* Hardware-in-the-loop testing
* System-level debugging
* Technical documentation

---

# 📈 Project Philosophy

> **Don't just build a system. Build a system that can prove it works.**

VoltWatch is ultimately an experiment in applying professional system verification principles to a small-scale embedded platform.

The project will intentionally grow in complexity over time, starting with a single analogue measurement and progressing towards automated system-level verification.

The goal is not to reproduce a production automotive BMS.

The goal is to develop the **engineering skills, verification methodology, automation, and system-level thinking required to work on one.**

---

## Project Status

**Current stage:** Project setup

**Current focus:** ADuCM320 ADC bring-up and analogue voltage measurement

**Next milestone:** Read a potentiometer using the ADuCM320 ADC and report the measured voltage over UART.

---

## Author

**George Boyhan**

Personal engineering project focused on embedded systems, hardware validation, software automation, and system verification.

---
