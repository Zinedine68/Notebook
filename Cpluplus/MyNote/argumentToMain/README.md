# argumentToMain

```bash
$ ./a.out hah lll 12
Argument 0 = ./a.out
Argument 1 = hah
Argument 2 = lll
Argument 3 = 12
```

# 0_argumentToMain_OF.C
no difference from the argumentToMain.cpp

# 1_argumentToMain_OF.C
doesn't compile due to namespace Foam not declared.

# 2_argumentToMain_OF.C
the simplist way to have a hello world by using both `std` and `Foam`. Result : they give the exact same output
```bash
Argument 0 = ./argumentToMain_OF
Argument 0 = ./argumentToMain_OF
```

# 3_argumentToMain_OF.C
using args instead of directly acessing argv. Saw difference in output:
```bash
Argument 0 = ./argumentToMain_OF
Argument 0 = "./argumentToMain_OF"
```

# 4_argumentToMain_OF.C
add an valid argument and pass a "float" then convert. Saw difference in output:
```bash
Argument 0 = ./argumentToMain_OF
Argument 1 = 10
Argument 0 = "./argumentToMain_OF"
Argument 1 = "10"
Argument 1 = 10
```
