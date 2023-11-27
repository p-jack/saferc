# saferc

This is a prototype of safer version of C's standard library. To use it,
include the saferc versions of the headers you would ordinarily use. For
example, include `<saferc/stdio>` instead of `<stdio>`.

The saferc versions simplify and unify error handling for the standard
library functions. The saferc versions are macros that expand to a
statement expression that properly checks for errors, uses 
`goto cleanup` if an error is found, and returns the function's result
if an error is not found. This means that execution aborts as soon as
an error is encountered, similiar to exceptions in other languages.

To use them, you need to begin your function will the `SAFER_BEGIN` macro
and end them with the `SAFER_END` macro. Your function also needs to have
a `cleanup` label. Here's a skeleton:

    int my_function(void) {
      SAFER_BEGIN();
      // your code here
      cleanup:
      // your cleanup code here
      SAFER_END();
    }

For a real-world example, see `tests/bak_test/main.c`, which is a complete
program that copies a file--but with proper error handling.
