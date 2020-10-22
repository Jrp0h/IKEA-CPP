# Readme aka notes for self

## Value types

VAR_VALUE ($) = the value at the memory address the var is pointing to
VAR (&) = the memory address the var is pointing to
DIRECT (\#) = Index of memory
PLAIN () = Normal number
STR = Text

## Instructions

### Declaration

Declare section

```bash
SEC [STR]:
```

Declare function

```bash
FUN [STR]:
```

> Requires EFUN when the function is done

### Flow Control

Jump to section if value is 0(zero)

```bash
JMPZ [$VAR_VALUE|&VAR|#DIRECT],[SEC_STR]
```

Jump to section if value is 1(one)

```bash
JMPO [$VAR_VALUE|&VAR|#DIRECT],[SEC_STR]
```

Jump to section if value is \<2nd param\>

```bash
JMPT [$VAR_VALUE|&VAR|#DIRECT|PLAIN],[$VAR_VALUE|&VAR|#DIRECT|PLAIN],[SEC_STR]
```

Jump to section if value is NOT \<2nd param\>

```bash
JMPF [$VAR_VALUE|&VAR|#DIRECT|PLAIN],[$VAR_VALUE|&VAR|#DIRECT|PLAIN],[SEC_STR]
```

### Other

Jump to section if value is 0(zero)

```bash
JMP [SEC_STR]
```

Set data at memory address

```bash
MOV [$VAR_VALUE|&VAR|#DIRECT],[$VAR_VALUE|&VAR|#DIRECT|PLAIN]
```

Invoke Function

```bash
CALL [FUN_STR]
```

Return from Function

```bash
RET
```

Assign variable

```bash
VAR [STR],[$VAR_VALUE|&VAR|#DIRECT|PLAIN]
```

### Misc

Print text

```bash
PRNT [STR]
```

Print All variables

```bash
PRNTV
```
