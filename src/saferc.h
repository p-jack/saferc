#pragma once
#include <errno.h>

/// \file cthrow.h
/// \brief Simple error handling macros.
///
/// These macros expect your functions to take a certain form.
/// You must begin the function with the SAFER_BEGIN() macro,
/// which declares a variable named `err`. You must include a
/// label named `cleanup` that performs any cleanup your function
/// requires. Finally use the SAFER_END() function to return the
/// error.
///
/// So the skeleton looks like this:
///
///     int my_func(my_struct_t* param) {
///       SAFER_BEGIN();
///       // your code here
///       cleanup:
///       // your cleanup code here
///       SAFER_END();
///     }


/// Start a function.
///
/// Just declars the `err` variable that the other macros use to track errors.
/// Implemented as a macro so you don't have to remember to initialize it,
/// which you will forget to do, leading to woe.
#define SAFER_BEGIN() int err = 0;

/// End a function.
///
/// Just returns `err`. Implemented as a macro so you don't have to remember to
/// do it properly (your instinct will be to return zero, leading to woe.)
#define SAFER_END() return err;

/// Trace an error.
///
/// Does nothing by default. Include `saferc_trace.h` instead
/// of just `saferc.h` to get low-overhead runtime stack traces.
#ifndef TRACE_ERR
  #define TRACE_ERR(err)
#endif

/// "Throw" an error code by tracing it, cleaning up, then returning the error.
#define THROW(x) { err = x; TRACE_ERR(err); goto cleanup; }

/// "Try" an operation by executing `x` then checking that it evaluated to zero.
///
/// If the operation doesn't evaluate to zero, it will throw the error via
/// `THROW`. This is useful for most C APIs that return error codes.
#define TRY(x) { int $err = x; if ($err != 0) THROW($err); }

/// Ensures that a pointer exists. If not, EFAULT is thrown via `THROW`.
/// This is useful for C APIs that return a pointer, but use NULL to indicate
/// failure, such as the *alloc functions.
#define MUST(x) ({ void* $o = x; if ($o == NULL) THROW(EFAULT); $o; })

/// Executes `x` then checks that it evaluated to zero or a positive integer.
///
/// If not, it will throw the result via `THROW`. `POZ` is similar to `TRY`,
/// but is useful for string-like operations that return an index or a negative
/// number to indicate "not found" or such.
#define POZ(x) { int $err = x; if ($err < 0) THROW($err); }

/// Clears `errno`, executes `x`, then checks that `errno` is still zero.
/// If not, the value in `errno` is thrown via `THROW`.
#define ERRNO(x) ({ errno = 0; x; if (errno != 0) THROW(errno); $r; })

/// Evaluates `x` only if an error wasn't thrown. You should only use this
/// in the cleanup block. It's useful for cleanups that should only happen
/// on error. For instance, if your function allocates an object to return,
/// but encounters an error while processing the object, you should free the
/// object in a CATCH. This is a macro just to make it clear what's happening.
#define CATCH(x) { if (err != 0) { x; } }

/// Frees a pointer if it isn't null.
/// This simplifies cleanup logic.
#define FREE(v) if ((v) != NULL) free(v);
