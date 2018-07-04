# command-line argument

## 0_args_1Argument.C
Parse one argument to an typical OpenFOAM main function
### How
./argumentInput 30

## 0_args_2Arguments.C
Parse two arguments to an typical OpenFOAM main function
### How
./argumentInput 20 hah

## 1_argumentInput.C
A more complicated example
### How
./argumentInput 30

## 2_argumentInput.C
Left out the big include "fvCFD.H"
### How
./argumentInput 30

## 3_argumentInput.C
Omit creating object `args`. 这样main函数(其实是`class argList`的函数)就不再check每次传进的参数个数

## 4_argumentInput.C
用argv的时候需要强制转换为string才能c_str()，才能转换成double

## 5_argumentInput.C
用args，因为本来是一个stringList，所以不再要求args[1]是一个string?

## Note
OpenFOAM's main seems to be the same as cplusplus standard : `int main( int argc, char *argv[] )`
but if you don't add `argList::validArgs.append("someTime");` to the main function it will throw
out error 
```bash
--> FOAM FATAL ERROR: 
Wrong number of arguments, expected 0 found 1
```
Why?
When `args` is instantiated the constructor is called. In the end of constructor call function
`parse` has several lines:
```cpp
    // Print the usage message and exit if the number of arguments is incorrect
    if (!check(checkArgs, checkOpts))
    {
        FatalError.exit();
    }
```
So openfoam's main if `args` is instantiated then the number of argments will be
checked and when it's not consistent program will throw FatalError and exit. In 
other words : you need to add explicitely a fixed number of parameters parsing 
through the program and parse every time the right parameters.   
一句话总结：要在args构造函数(class argList)之前用`argList::validArgs.append()`来完成对command-line argument list
大小的预设，实际执行的时候argument不能多也不能少.
