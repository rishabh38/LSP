OpGen: Machine Code generator:
-----------------------------

OpGen is a system which takes two input files, A and B

file A is of the form of
---------------------
x0 := B0
x1 := B1
x2 := B2
x3 := B3
.
.
.
---------------------
here Xi represents a string, 
Bi represents a bitstring

file B is of the form of 
-------------------
X2
X0
X1
X4
.
.
.
-------------------
it contains the strings present in 'file A' in newline separated form

giving OpGen these two files will make it generate an output file 'output',
which will be of the form of
-------------------
B2
B0
B1
B4
.
.
.
-------------------
This gives a sense of what OpGen does, but there is more

here Xi can be represented in the form of
------------------
W0 W1 W2 W3 ...
------------------
where Wi are strings containing non-space characters

Bi can be represented in the form of
------------------
[r0-r1]:[bits0]
[r2-r3]:[bits1]
.
.
[rn-rm]:[bitsk];
-----------------
where ri is a non-negative integer,
bitsi is a string of 0/1 with length = r(i+1) - ri + 1
here, r(i+1) should be >= ri

the structure Bi defines how the complete bitstring Bi will look like,
e.g.
----------------
[0-4]:[0011]
[5-8]:[0101];
---------------
is equivalent to bistring
--------------
00110101
--------------


for our earlier input of file A and file B,
thats how OpGen will process the inputs:

it will first convert the data of file A into an internal structure, in the form of map between instruction format and bistring formats,
which will be used to identify the instructions present in 'file B', and for each line in 'file B', OpGen will generate a bitstring in
output


Variable

We can use variables holding integers,
which can generate bitstring based on the input given in 'file B'.
-------------------------------------
add r4 {imm1} {imm2} := [0-3]:[1110]
                        [4-5]:[11]
                        [6-9]:imm1
                        [10-13]:imm2;
-------------------------------------

so, when 'file B' contains this
-------------------------------------
add r4 3 3
-------------------------------------
OpGen will generate bitstring
------------------------------------
11101100110011
------------------------------------
here,
111011.0011.0011.
digits between the periods represent 3s that we gave in 'file B'.


OpGen can be used to convert assembly instructions to machine code at low scale for different ISAs.

for example

for 'file A':
-------------------------------------
add r{a} r{b} r{c} := [0-3]:[1110]
                      [4-7]:a
                      [8-11]:b
                      [12-15]:c;

add r{a} r{b} r{c} := [0-3]:[1111]
                      [4-7]:a
                      [8-11]:b
                      [12-15]:c;

ldi r{a} {imm}  := [0-1]:[10]
                   [2-5]:a
                   [6-15]:imm;

stop := [0-15]:[000000000000000];
-------------------------------------

for 'file B':
-------------------------------------
rm r2 r3 r1
rm r3 r2 r1
add r2 r3 r4
ldi r2 1000
stop
-------------------------------------

it will generate output:
-------------------------------------
1111001000110001
1111001100100001
1110001000110100
1000101111101000
0000000000000000
-------------------------------------
