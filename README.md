# saferc

## Overview

This is a prototype of safer version of C's standard library. To use it,
include the saferc versions of the headers you would ordinarily use. For
example, include `<saferc/stdio>` instead of `<stdio>`.

The saferc versions simplify and unify error handling for the standard
library functions. The saferc versions are macros that expand to a
statement expression that properly checks for errors, uses
`goto cleanup` if an error is found, and returns the function's result
if an error is not found. This means that execution aborts as soon as
an error is encountered, similiar to exceptions in other languages.

## Conventions

To use the saferc versions of standard functions, them, you need to begin
your function will the `SAFER_BEGIN` macro and end them with the
`SAFER_END` macro. Your function also needs to have a `cleanup` label.
Here's a skeleton:

    int my_function(void) {
      SAFER_BEGIN();
      // your code here
      cleanup:
      // your cleanup code here
      SAFER_END();
    }

For a real-world example, see `examples/bak/main.c`, which is a complete
program that copies a file--but with proper error handling.

## Using saferc Conventions In Your Own Libraries

You can apply the same conventions used here for any C library you write.
To do so, simply define a macro in your header file that follows the
conventions.

For example, if your library has a function that only returns an error,
you can just wrap that function call with `TRY`:

    #define foo_init() TRY(foo_init())
    int (foo_init)(void) {
      // ...
    }

Note that in the function's actual definition, we surround the function
name with parentheses to prevent the preprocessor from expanding it.

If your function returns a value as well as an error, you can use a
statement expression to handle the error and return the value:

   #define foo_process(x) ({ int $r; TRY(foo_process(x, &r); $r; })
   int (foo_process)(int x, int *out_result) {
     // ...
   }

That makes the actual function call a bit nicer, because you don't need
to allocate a local for it. Before, the call would look like:

    int result;
    if (foo_process(x, &result) != 0) {
      // handle error
    }

After the conventions, the function call simply becomes:

    int result = foo_process(x);

The saferc form both ensures proper error handling *and* allows you to
compose function calls, like you can in most other languages.

However, you want to avoid doing this if the result of the function is
a pointer. One, you might want to allocate that pointer on the stack.
And two, if your function internally allocates memory for a result
pointer, if you compose that function call, it might allocate memory
that will never be freed (if the outer function of the composition
returns an error.)

In general, applying saferc conventions to your code makes the headers
somewhat harder to read (because each function declaration is now two
lines instead of one) but makes the actual usage of those functions
much easier (because you don't have to worry about error handling, only
proper cleanup; and because you can compose function calls.)
