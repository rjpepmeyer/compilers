* ----------------------------------------------------------
* SIMULATOR FILES
* ----------------------------------------------------------

*  This directory contains five versions of the TM simulator
   for the TM ("Tiny Machine") computer defined in Kenneth C.
   Louden's "Compiler Construction: Principles and Practice".
   Each version extends the previous.

** tm.c

   The original tm.c by Louden published in the book, with
   one change:  All uses of the gets() function are replaced
   with calls to fgets(), which is safer.  This eliminates
   an annoying run-time warning.

** tm-cli.c

   This simulator accepts 0 or more command-line arguments,
   placing them at locations [1..n] in the DMEM.  "true" and
   "false" are stored as 1 and 0, respectively.

** tm-cli-go.c

   This simulator executes the TM program immediately, rather
   than interacting with the user through the simulator's
   original menu interface.

** tm-cli-go-timed.c

   This simulator reports a rudimentary value for the execution
   time of the TM program, in terms of clock ticks consume.

** tm-cli-go-timed-ext.c

   This simulator has all the features of the preceding VM but
   offers IMEM and DMEM of 1 megabyte each.

* ----------------------------------------------------------
* SAMPLE TM FILES
* ----------------------------------------------------------

*  This directory also contains two versions of a factorial
   program written in TM assembly language.

** factorial.tm

   The original version by Louden published in the book.  It
   reads its argument from standard input using the primitive
   TM instruction IN.

** factorial-cli.tm

   This version takes its argument on the command line.

* ----------------------------------------------------------
* COMPILING THE VIRTUAL MACHINE
* ----------------------------------------------------------

  $ gcc tm.c -o tm

  The same will work for the other three versions of the
  machine.

  $ tm factorial.tm

* ----------------------------------------------------------
* LIMITATIONS
* ----------------------------------------------------------

* The virtual machine limits the names of TM source files to
  20 characters.  You can change this limit by changing the
  FILE[20] declaration.  This occurs on line 123 of the tm.c
  source file.

* ----------------------------------------------------------
