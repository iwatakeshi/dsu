# A3

## Specifications

All files are written in C. Simply have lex generate the scanners for a3.v1.l, a3.v2.l, or a3.v3.l and compile them with gcc.


## Sample Outputs

```bash
# Run verison 1 using the a2s1.in file
./a.v1 < data/a2s1.in
LLLLwDPDwPPwDDw
wwwwLLLLLPwwww
```

```bash
# Run verison 2 using the a2s1.in file
./a.v2 < data/a2s1.in

swnonwownw
wspww
```
**Note**: The output file, a2s1.v2.out, does not seem to be correct. Using `bless` on the file shows that there is a Line Feed (0x0a) at the end of the file.
Thus, the output in this run is correct.




```bash
# Run verison 3 using stdin
./a.v3
0x45 < 234
HEX: 0x45
DEC: 234

0ff 
DEC: 0

0xfff
HEX: 0xfff

sdffsdf

q
```
