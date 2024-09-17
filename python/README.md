# Simple implementation in python of ROFL

## Overview

The project consists of three main Python files:
1. `LFSR.py`: Implements the Linear Feedback Shift Register.
2. `Filter.py`: Implements the Filter generator using CWQ functions.
3. `rofl.py`: The main script to run experiments with different parameters.
4. `test.py`: Test of the correctness of the keystream generated for one example by hand.

## Usage

1. run python3 rofl.py
2. You will be prompted to choose a mode:
- Mode 1: Speed assessment
- Mode 2: User-chosen N with the keystream generated printed

3. For both modes, you'll need to enter:
- The number of variables (n)
- The length of the keystream to generate (in Ko)

4. For Mode 2, you'll also need to enter:
- The LFSR length (N) - choose from 512, 1024, or 2048

## Modes

### Mode 1: Speed Assessment

This mode runs experiments for LFSR lengths of 512, 1024, and 2048 bits, using both 'u' and 't' type quadratic functions (see [MéaOza23] for details). It measures and reports the execution time for generating the specified length of keystream.

### Mode 2: User-Chosen N with Keystream Generation

This mode allows you to choose a specific LFSR length and generates a sample of the keystream. It displays the first 64 bits of the generated keystream for both 'u' and 't' type quadratic functions.

## File Descriptions

### LFSR.py

Implements the Linear Feedback Shift Register class. It includes methods for initializing the LFSR, performing clock cycles, and generating output bits.

### Filter.py

Implements the Filter class, which uses an LFSR and applies a CWQ function to generate the keystream. It includes methods for initializing the filter, generating taps, and producing output bits and bytes.

### rofl.py

The main script that sets up and runs the experiments. It includes functions for:
- Generating primitive polynomials
- Creating quadratic functions
- Running speed assessment experiments
- Generating keystream samples for user-chosen parameters

## Parameters

- `N`: LFSR length (512, 1024, or 2048 bits)
- `n`: Number of variables in the filter function
- `l`: Length of the keystream to generate (in Ko)

## Output

- For Mode 1: The script outputs the execution time for generating the specified length of keystream for each combination of LFSR length and quadratic function type.
- For Mode 2: The script displays the first 64 bits of the generated keystream for both 'u' and 't' type functions.

