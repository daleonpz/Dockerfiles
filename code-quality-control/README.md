# code-quality-control

"Quality Control" for C projects.

This scripts perform:

# Style Analysis
- [Astyle](http://astyle.sourceforge.net/astyle.html) is used for this task.
- Compliant with our [style guide](https://git.infra.cospace.de/guidelines/readme). 


# Cyclomatic Complexity Calculation
- [Lizard](https://github.com/terryyin/lizard) is used for this task.
- The code will be rejected if there is a module with a complexity is higher then 15. **Lower than 10 should be the goal**

Here are some useful links to understand better what code complexity is: 
- [Code complextiy explained](https://blog.feabhas.com/2018/07/code-quality-cyclomatic-complexity/)
- [How code complexity is calculated](https://www.aivosto.com/project/help/pm-complexity.html)
- [Rules of thumbs for code complexity](https://betterembsw.blogspot.com/2017/08/the-spaghetti-factor-software.html)

# Static Code Analysis
- [CppCheck]( http://cppcheck.sourceforge.net/) is used for this task.
- It won't pass if the code has **errors** or **warnings**. 

## **IMPORTANT**
- The analysis currently ignores messages related to possible Interrupt Service Routines (ISR).  That means that function written in uppercase will be ignored. **Note**: Usually ISR are written in uppercase.
For example, the following ISR will be ignored:

```c
void __attribute__ ( ( interrupt( USCI_A1_VECTOR ) ) )
    USCI_A1_ISR ( void )
```


- CppCheck won't detect missing semi-colons. For example:

```c
int main ( )
{
    int x = 10
    x = 5
    return x
}
```

This type of erros will be overlooked


