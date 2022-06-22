
#ifndef __UTILS_H__
#define __UTILS_H__

// Macro that offers run-time and preprocessor-time checks to know if some macros are defined
// Assumption: When existing, macros are defined to be 1
//
// Compiles and works both under GCC and MSVC (and expected to work under most other environments)
//
// Response to Linus Torvalds' G+ challenge: https://plus.google.com/u/0/102150693225130002912/posts/9gntjh57dXt
//
// from David Ramos
// kudos to Jean-Noel Avila for simplifying my initial implementation
// example:
// #define CONFIG_EXISTS 1
//   if(isPreprocessorEnabled(CONFIG_DOESNT_EXIST))
//      printf("Enabled! RUNTIME\n");
// #if isPreprocessorEnabled(CONFIG_EXISTS)
//   printf("Enabled! PREPROCESSOR\n");
// #endif

#define internal_preproc_donothing(...)
#define internal_preproc___open (
#define internal_preproc_close__ )
/* This macro below is so it works on GCC. In MSVC it would be enough with just
   doing "#define is_enabled1(x) (donothing __open helper_##x close__) + 0)" */
#define internal_preproc_macro_caller(macro, args) macro args
#define internal_preproc_helper_1 internal_preproc_close__ internal_preproc___open 1
#define internal_preproc_is_enabled1(x) (internal_preproc_macro_caller(internal_preproc_donothing, internal_preproc___open internal_preproc_helper_##x internal_preproc_close__) + 0)
#define isPreprocessorEnabled(x) internal_preproc_is_enabled1(x) 

#endif

