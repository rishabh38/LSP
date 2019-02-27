# Instruction Configuration file structure
This file is used to set the rules for which statements are mapped to which opcodes.

below presents a rule specifying how an instruction can be mapped to opcode

add r{a} r{b} r{c} := [0-4]:[11110] | [5-8]:a | [9-12]:b | [13-16]:c;

when file containing this rule is given to opcgen, then any instruction
in the instructions file like

add r3 r2 r0

will generate opcode 
11110111001011000
in the output file

### what's happening here?
here, add r3 r2 r0 will match with the instruction rule and

3 of r3 will be mapped with a

2 of r2 will be mapped with b

0 of r0 will be mapped with c

and opcode will be calculated according the values in a,b,c and 
specified opcode mapping
