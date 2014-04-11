/*
  gramdiag.c

  Utility for finding and diagnosing shift/reduce and reduce/reduce
  conflicts in grammars fed to Bison, by examining the output produced
  with Bison's '-v' switch.

  *****************************************************************
     
  Copyright (C) 1999,2000  Richard P. Curnow
  Copyright (C) 2014  Fabian Schuiki
     
  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
     
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

  *****************************************************************
  
  Compile this software using GCC (the file uses GCC extensions and is
  NOT ANSI/ISO C conformant) :

  gcc -O2 -o gramdiag gramdiag.c

  Run the software as follows :

  bison -v foo.y
  gramdiag foo.output > foo.diag
  more foo.diag

  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*+ Allocate a new dynamic object of type T +*/
#define new(T) (T *) malloc(sizeof(T))

/*+ Allocate an array of dynamic objects of type T +*/
#define new_array(T, n) (T *) malloc((n) * sizeof(T))

/*+ Copy a string and return a pointer to the copy +*/
#define new_string(s) ((s) ? (strcpy((char *) malloc(1+strlen(s)), s)) : NULL)

/** Print a more verbose error. */
#define print_error(...) { fprintf(stderr, "%s: ", __FUNCTION__); fprintf(stderr, __VA_ARGS__); }

/*+ Type used to store information about a rule in the grammar. +*/
typedef struct rule {
  int number;                   /*+ as per bison file, actually always
                                   1 more than array index +*/
  char *lhs;                    /*+ Text of the LHS symbol +*/
  int lindex;                   /*+ Index into symbols array of LHS symbol +*/
  int nrhs;                     /*+ Number of symbols on RHS +*/
  char **rhs;                   /*+ Texts of RHS symbols +*/
  int *rindex;                  /*+ Indices into symbols array for RHS symbols +*/
} Rule;

/*+ Number of rules in the grammar +*/
static int n_rules = 0;

/*+ The rules +*/
static Rule rules[4096]; /* Never that many I hope! */

/*+ Table for mapping rule numbers to the index in the rules array.
  The inverse of the number field in the Rule structure.  This is
  needed to cope with grammars which have redundant rules in them,
  where the grammar section of the Bison output does not run in
  contiguous order of rule numbers - there are jumps, so there is no
  direct relationship between array index in rules[] and the rule
  number.+*/
static int ruleno2idx[4096];

/*+ Type used to hold information about a symbol +*/
typedef struct symbol {
  char *text;                   /*+ The text of the symbol name +*/
  int epsilon_rule;             /*+ Boolean, true if symbol can match empty string +*/
  enum {TERMINAL, NONTERMINAL} type; /*+ Whether symbol is a token or a nonterminal +*/
} Symbol;

/*+ The number of symbols in the table +*/
static int n_symbols;

/*+ The symbol table +*/
static Symbol symbols[4096];

/*+ Table of which symbols can occur at the start of other symbols (directly or indirectly) +*/
static int *at_start;

/*+ Table of which symbols can occur at the end of other symbols (directly or indirectly) +*/
static int *at_end;

/*+ Record used for holding information about which symbols can follow which other symbols +*/
typedef struct {
  int rule;                     /*+ A rule (array index count from 0)
                                   which has X coming before Y (maybe
                                   with epsilons between) +*/
  int index1;                   /*+ The position of X in the rhs (count
                                   from 0) +*/
  int index2;                   /*+ The posn of Y in the rhs +*/
} AfterRec;

static AfterRec *after_records;

static int *flags = NULL;

typedef struct {
  int i;
  int j;
} StackElt;

static StackElt *stack = NULL;
static int stackptr = 0;

/*+ Store details about a rule where the state allows us to shift +*/
typedef struct {
  int ruleno;  /*+ The rule number (1..N) +*/
  int focusat; /*+ Index number of symbol that focus is before (0 for a reduce rule) +*/
  int nextsym; /*+ Code for following symbol +*/
} ShiftCond;

/*++++++++++++++++++++++++++++++
  Return a ref to the rule by which 'a' occurs at the start of 'b'.

  inline static int * ate Pointer to integer giving rule number where symbol 'a' occurs at the start of symbol 'b'.

  int a Symbol array index of first symbol

  int b Symbol array index of containing symbol
  ++++++++++++++++++++++++++++++*/

inline static int *
ats(int a, int b) {
  return &at_start[n_symbols*a + b];
}

/*++++++++++++++++++++++++++++++
  Return a ref to the rule by which 'a' occurs at the end of 'b'.

  inline static int * ate Pointer to integer giving rule number where symbol 'a' occurs at the end of symbol 'b'.

  int a Symbol array index of end symbol

  int b Symbol array index of containing symbol
  ++++++++++++++++++++++++++++++*/

inline static int *
ate(int a, int b) {
  return &at_end[n_symbols*a + b];
}

/*++++++++++++++++++++++++++++++
  Return a ref to the rule by which 'a' occurs at the end of 'b'.

  inline static int * ate Pointer to integer giving rule number where symbol 'a' occurs at the end of symbol 'b'.

  int a Symbol array index of end symbol

  int b Symbol array index of containing symbol
  ++++++++++++++++++++++++++++++*/

inline static int *
flag(int a, int b) {
  return &flags[n_symbols*a + b];
}

/*++++++++++++++++++++++++++++++
  Return information about a rule through which symbol 'a' occurs just
  after symbol 'b' (either in the RHS of that rule, or because 'a' is
  at the end of 'c', 'b' is at the start of 'd', and 'c' follows 'd'
  in the RHS of the rule, maybe with epsilon symbols between.

  inline static AfterRec * aft Pointer to the 'after' record.

  int a Symbol array index for 'a' symbol.

  int b Symbol array index for 'b' symbol.
  ++++++++++++++++++++++++++++++*/

inline static AfterRec *
aft(int a, int b) {
  return &after_records[n_symbols*a + b];
}

/*++++++++++++++++++++++++++++++
  Strip a final line feed from the end of a line.

  char *x Pointer to the line of text.
  ++++++++++++++++++++++++++++++*/

static void
kill_lf(char *x)
{
  while (*x) x++;
  x--;
  if (*x == '\n') {
    *x = 0;
  }
}

/*++++++++++++++++++++++++++++++
  Read a single space-separated field from a line.

  char **s Pointer to the line.  Modified on exit to point to the next
  field or to the terminating null.

  char *d Pointer to storage where the resulting field should be stored.
  ++++++++++++++++++++++++++++++*/

static void
read_field(char **s, char *d) {
  char *x = *s;
  while (*x && isspace((int) *x)) x++;
  while (*x && !isspace((int) *x)) {
    *d++ = *x++;
  }

  /* Shift over space, so if we're at EOL it shows up after the call */
  while (*x && isspace((int) *x)) x++;

  *s = x;
  *d = 0;
}
 
/*++++++++++++++++++++++++++++++
  Parse the rules portion of the bison output file and store them in
  the rules array.

  FILE *in The file to read the rules from.
  ++++++++++++++++++++++++++++++*/

static void
parse_rules(FILE *in)
{
  char line[2048];
  char *p;
  char buffer[1024];
  char *rhs[256];
  int nrhs;
  int ok = 0;
  int i;
  Rule *r;
  int ruleno;

  while (fgets(line, sizeof(line), in)) {
    kill_lf(line);
    if (!strcmp(line, "Grammar")) {
      ok = 1;
      break;
    }
  }
  
  if (!ok) {
    print_error("Is this a valid bison -v output file?\n");
    exit(1);
  }

  int nb = 0; /* number of subsequent blank lines read */
  do {
    if (!fgets(line, sizeof(line), in)) {
      print_error("Expected another rule?\n");
      exit(1);
    }
    kill_lf(line);

    if (line[0] == 0) {
      if (++nb >= 2)
        break;
      else
        continue;
    } else {
      nb = 0;
    }

    r = rules + n_rules;

    p = line/* + 5*/; /* skip over 'rule ' */
    /* Extract rule number */
    read_field(&p, buffer);
    if (sscanf(buffer, "%d", &ruleno) != 1) {
      print_error("Could not get rule number from rule line [%s]\n", line);
      exit(1);
    }

    read_field(&p, buffer);
    if (!strcmp(buffer, "|")) {
      strcpy(buffer, (rules+n_rules-1)->lhs);
    } else {
      int l = strlen(buffer) - 1;
      if (buffer[l] == ':')
        buffer[l] = 0;
    }
    r->lhs = new_string(buffer);

    /* start parsing the rhs names */
    nrhs = 0;
    do {
      read_field(&p, buffer);
      if (!strcmp(buffer, "/*")) {
        /* epsilon rule */
        break;
      }

      /* Otherwise we have a real token */
      rhs[nrhs] = new_string(buffer);
      nrhs++;
      if (!*p) {
        break;
      }
    } while (1);

    r->nrhs = nrhs;
    r->rhs = new_array(char *, nrhs);
    for (i=0; i<nrhs; i++) {
      r->rhs[i] = rhs[i];
    }
    r->number = ruleno;
    ruleno2idx[ruleno] = r - rules; /* == n_rules */

#if 0
    print_error("Rule %d, %d rhs tokens\n", r->number, nrhs++);
#endif

    n_rules++;

  } while (1);

}

/*++++++++++++++++++++++++++++++
  Parse the part of the 'bison -v' file that contains the definitions
  of the tokens.
  ++++++++++++++++++++++++++++++*/

static void
parse_terminals(FILE *in)
{
  char line[2048];
  char *p;
  char buffer[1024];
  int ok = 0;

  while (fgets(line, sizeof(line), in)) {
    kill_lf(line);
    if (!strncmp(line, "Terminals", 9)) {
      ok = 1;
      break;
    }
  }
  
  if (!ok) {
    print_error("Is this a valid bison -v output file?\n");
    exit(1);
  }
  
  /* skip blank */
  fgets(line, sizeof(line), in);
  while (fgets(line, sizeof(line), in)) {
    kill_lf(line);
    p = line;
    read_field(&p, buffer);
    if (!buffer[0]) {
      break;
    }
    symbols[n_symbols].text = new_string(buffer);
    symbols[n_symbols].type = TERMINAL;
    n_symbols++;
  }

  symbols[n_symbols].text = "$default"; /* Default match symbol */
  symbols[n_symbols].type = TERMINAL;
  n_symbols++;

  symbols[n_symbols].text = "$"; /* End of stream symbol */
  symbols[n_symbols].type = TERMINAL;
  n_symbols++;


}

/*++++++++++++++++++++++++++++++
  Parse the part of the 'bison -v' file that contains the definitions
  of the non-terminals.
  ++++++++++++++++++++++++++++++*/

static void
parse_nonterms(FILE *in)
{
  char line[2048];
  char *p;
  char buffer[1024];
  int ok = 0;

  while (fgets(line, sizeof(line), in)) {
    kill_lf(line);
    if (!strncmp(line, "Nonterminals", 12)) {
      ok = 1;
      break;
    }
  }
  
  if (!ok) {
    print_error("Is this a valid bison -v output file?\n");
    exit(1);
  }
  
  /* skip blank */
  fgets(line, sizeof(line), in);

  while (fgets(line, sizeof(line), in)) {
    kill_lf(line);
    p = line;
    read_field(&p, buffer);
    if (!buffer[0]) {
      break;
    }
    if (line[0] == ' ') continue; /* reject non-blank lines that aren't
                                    a new nonterm definition */

    symbols[n_symbols].text = new_string(buffer);
    symbols[n_symbols].type = NONTERMINAL;
    n_symbols++;
  }

}

/*++++++++++++++++++++++++++++++
  Lookup a symbol by name and return the index into the symbol table.
  Exit if the symbol can't be found.  A simple exhaustive search is
  used.
  ++++++++++++++++++++++++++++++*/

static int
lookup_symbol(char *x)
{
  int i;
  for (i=0; i<n_symbols; i++) {
    if (!strcmp(x, symbols[i].text)) {
      return i;
    }
  }

  print_error("Failed to look up %s, corrupt bison output?\n", x);
  exit(1);

}

/*++++++++++++++++++++++++++++++
  
  ++++++++++++++++++++++++++++++*/

static void
index_rules(void)
{
  Rule *r;
  int rr, i;

  for (rr=0; rr<n_rules; rr++) {
    r = rules + rr;
    r->lindex = lookup_symbol(r->lhs);
    
    r->rindex = new_array(int, r->nrhs);
    for (i=0; i<r->nrhs; i++) {
      r->rindex[i] = lookup_symbol(r->rhs[i]);
    }
  }

}

/*++++++++++++++++++++++++++++++
  Identify all nonterminals that can be matched by an empty string 
  ++++++++++++++++++++++++++++++*/

static void
find_epsilons(void)
{
  int i, j;
  int change, all_eps;
  Rule *r;

  for (i=0; i<n_symbols; i++) {
    symbols[i].epsilon_rule = -1; /* meaning no rule */
  }

  do {
    change = 0;
    for (i=0; i<n_rules; i++) {
      r = rules + i;
      if (symbols[r->lindex].epsilon_rule < 0) {
        if (r->nrhs == 0) {
          change = 1;
          symbols[r->lindex].epsilon_rule = i;
        } else {
          all_eps = 1;
          for (j=0; j<r->nrhs; j++) {
            if (symbols[r->rindex[j]].epsilon_rule < 0) {
              all_eps = 0;
              break;
            }
          }
          if (all_eps) { /* all RHS symbols can be reduced to nothing */
            change = 1;
            symbols[r->lindex].epsilon_rule = i;
          }
        }
      }
      
    }
  } while (change);
}

/*++++++++++++++++++++++++++++++
  Print out a rule

  int x The index into the rules array

  int focus The symbol before which the focus '.' is shown, zero to
  not show a focus.
  ++++++++++++++++++++++++++++++*/

static void
print_rule(int x, int focus) {
  Rule *r;
  int i, idx;
  r = rules + x;
  idx = r->lindex;
  printf("%s ->", symbols[idx].text);
  if (r->nrhs > 0) {
    for (i=0; i<r->nrhs; i++) {
      idx = r->rindex[i];
      if (symbols[idx].epsilon_rule >= 0) {
        printf(" [%d:] (%s)", i, symbols[idx].text);
      } else {
        printf(" [%d:] %s", i, symbols[idx].text);
      }
      if ((i + 1) == focus) {
        printf(" .");
      }
    }
  } else {
    printf(" /* empty */");
  }
}


/*++++++++++++++++++++++++++++++
  Clear the work stack.
  ++++++++++++++++++++++++++++++*/

static void
clear_stack(void)
{
  int i;
  int n;
  n = n_symbols * n_symbols;
  if (!flags) {
    flags = new_array(int, n);
  }
  if (!stack) {
    stack = new_array(StackElt, n);
  }
  for (i=0; i<n; i++) {
    flags[i] = 0;
  }
  stackptr = 0;
}

/*++++++++++++++++++++++++++++++
  Push a coordinate pair onto the work stack.
  ++++++++++++++++++++++++++++++*/

static void
push_pair(int i, int j)
{
  if (!*flag(i, j)) {
    *flag(i, j) = 1;
    stack[stackptr++] = (StackElt) {i, j};
  }
}

/*++++++++++++++++++++++++++++++
  Get the next coordinate pair to look at from the work stack.
  ++++++++++++++++++++++++++++++*/

static void
pop_pair(int *i, int *j) {
  if (stackptr > 0) {
    --stackptr;
    *i = stack[stackptr].i;
    *j = stack[stackptr].j;
  }
}

/*++++++++++++++++++++++++++++++
  Return bookean for whether the work stack is empty or not.
  ++++++++++++++++++++++++++++++*/

static int
is_empty(void)
{
  return (stackptr == 0);
}

/*++++++++++++++++++++++++++++++
  Generate a complete table of which symbols can occur at the start of
  other symbols, allowing for nested symbols.
  ++++++++++++++++++++++++++++++*/

static void
compute_at_starts(void)
{
  int i, j, k;
  int change;
  Rule *r;
  int ptr;

  at_start = new_array(int, n_symbols * n_symbols);

  clear_stack();

  /* Clear the tables */
  for (i=0; i<n_symbols; i++) {
    for (j=0; j<n_symbols; j++) {
      *ats(i, j) = -1;
    }
  }

  for (i=0; i<n_rules; i++) {
    r = rules + i;
    for (j=0; j<r->nrhs; j++) {
      if (r->rindex[j] != r->lindex) {
        *ats(r->rindex[j], r->lindex) = i;
        push_pair(r->rindex[j], r->lindex);
      }
      if (symbols[r->rindex[j]].epsilon_rule < 0) {
        /* If the nonterm cannot be reduced to empty string, get out, otherwise try next one */
          break;
      }
    }
  }

  /* Now iterate until no more changes remain.
     If we have 
     rule lhs -> rhs
     1    a   -> b
     2    b   -> c
     3    c   -> d
     4    d   -> e

     We want the 'ats' table to look like
         a  b  c  d  e
     a      1  1  1  1
     b         2  2  2
     c            3  3
     d               4
     e

     So the (a,e) entry allows the intermediate chain to be followed,
     by looking up the LHS symbol of rule (a,e).

     */

  while (!is_empty()) {
    pop_pair(&i, &k);
    for (j=0; j<n_symbols; j++) {
      if ((*ats(i,j) < 0) &&
          (*ats(i,k) >= 0) &&
          (*ats(k,j) >= 0)) {

        *ats(i, j) = *ats(i, k);
        push_pair(i, j);
      }
    }
  }
  
}

/*++++++++++++++++++++++++++++++
  Generate a complete table of which symbols can occur at the end of
  other symbols, allowing for nested symbols.
  ++++++++++++++++++++++++++++++*/

static void
compute_at_ends(void)
{
  int i, j, k;
  int change;
  Rule *r;

  at_end = new_array(int, n_symbols * n_symbols);

  clear_stack();

  /* Clear the tables */
  for (i=0; i<n_symbols; i++) {
    for (j=0; j<n_symbols; j++) {
      *ate(i, j) = -1;
    }
  }

  for (i=0; i<n_rules; i++) {
    r = rules + i;
    for (j=r->nrhs-1; j>=0; j--) {
      if (r->rindex[j] != r->lindex) {
        *ate(r->rindex[j], r->lindex) = i;
        push_pair(r->rindex[j], r->lindex);
      }
      if (symbols[r->rindex[j]].epsilon_rule < 0) {
        /* If the nonterm cannot be reduced to empty string, get out, otherwise try next one */
          break;
      }
    }
  }

  /* Now iterate until no more changes remain.
     If we have 
     rule lhs -> rhs
     1    a   -> b
     2    b   -> c
     3    c   -> d
     4    d   -> e

     We want the 'ate' table to look like
         a  b  c  d  e
     a      1  1  1  1
     b         2  2  2
     c            3  3
     d               4
     e

     So the (a,e) entry allows the intermediate chain to be followed,
     by looking up the LHS symbol of rule (a,e).

     */

  while (!is_empty()) {
    pop_pair(&i, &k);
    for (j=0; j<n_symbols; j++) {
      if ((*ate(i,j) < 0) &&
          (*ate(i,k) >= 0) &&
          (*ate(k,j) >= 0)) {

        *ate(i, j) = *ate(i, k);
        push_pair(i, j);
      }
    }
  }
}

/*++++++++++++++++++++++++++++++
  Generate a complete table of which symbols can occur after another
  symbol.
  ++++++++++++++++++++++++++++++*/

static void
compute_after_records(void)
{
  Rule *r;
  int i, j, k;
  int change;

  after_records = new_array(AfterRec, n_symbols * n_symbols);

  clear_stack();

  /* Initialise table */
  for (i=0; i<n_symbols; i++) {
    for (j=0; j<n_symbols; j++) {
      *aft(i, j) = (AfterRec) {-1, -1, -1};
    }
  }
  
  /* Work out direct mappings */
  for (i=0; i<n_rules; i++) {
    r = rules + i;
    for (j=0; j<r->nrhs - 1; j++) {
      int i1, i2;

      i1 = r->rindex[j];
      k = j + 1;

      do {
        i2 = r->rindex[k];
#if 0
        printf("Looking at [%s],[%s] at positions %d,%d in rule %d (",
               symbols[i1].text, symbols[i2].text,
               j, k, i);
        print_rule(i, 0);
        printf(")\n");
#endif
        if (aft(i1, i2)->rule < 0) {
          *aft(i1, i2) = (AfterRec) {i, j, k};
#if 0
          printf("Set after condition for [%s] before [%s]\n",
                 symbols[i1].text, symbols[i2].text);
#endif
          push_pair(i1, i2);
        }
        if ((symbols[i2].epsilon_rule >= 0) &&
            (k < r->nrhs - 1)) {
          k++;
        } else {
          break;
        }
      } while (1);
    }
  }

  /* Compute indirects, do in two passes to save time. */

  while (!is_empty()) {
    pop_pair(&k, &j);
    for (i=0; i<n_symbols; i++) {
      if (aft(k,j)->rule >= 0) { /* should be unnecessary to check this */

        if (( aft(i, j)->rule < 0) &&
            (*ate(i, k) >= 0)) {
          
          *aft(i, j) = *aft(k, j);
#if 0
          printf("Set after condition for [%s] before [%s]\n",
                 symbols[i].text, symbols[j].text);
#endif
          push_pair(i, j);
        }
        
        if (( aft(k,i)->rule < 0) &&
            (*ats(i,j) >= 0)) {
          *aft(k, i) = *aft(k, j);
#if 0
          printf("Set after condition for [%s] after [%s]\n",
                 symbols[k].text, symbols[i].text);
#endif
          push_pair(k, i);
        }
      }
      
    }
  }

}

/*++++++++++++++++++++++++++++++
  If lo appears at the start of hi by some chain of start symbols,
  show the entire derivation.
  ++++++++++++++++++++++++++++++*/

static void
show_start_derivation(int lo, int hi, int indent)
{
  int i;

  /* Build reverse order list for the start sequence */
  typedef struct {
    int i2;
    int inter;
    int rule;
  } Item;
  Item items[1024];
  int nitems = 0;
  
  while (lo != hi) {
    int rr, inter;
    rr = *ats(lo, hi); /* Index into rules array */
    inter = rules[rr].lindex;
    items[nitems++] = (Item) {lo, inter, rr};
    lo = inter;
  }
  
  nitems--;
  while (nitems >= 0) {
    for (i=0; i<indent; i++) printf(" ");
    printf("[%s] occurs at the start of [%s] (rule %d : ",
           symbols[items[nitems].i2].text,
           symbols[items[nitems].inter].text,
           rules[items[nitems].rule].number);
    print_rule(items[nitems].rule, 0);
    printf(")\n");
    nitems--;
  }
}

/*++++++++++++++++++++++++++++++
  If s2 can occur immediately after s1, show a path in the grammar by
  which this can occur.  This is used to show how the reduce option in
  a shift/reduce conflict can be taken.
  ++++++++++++++++++++++++++++++*/

static void
analyse_shift_reduce(char *s1, char *s2)
{
  int i1, i2;
  int rule, index1, index2;
  int pos1, pos2;

  i1 = lookup_symbol(s1);
  i2 = lookup_symbol(s2);

  if (aft(i1, i2)->rule < 0) {
    printf("[%s] does not occur immediately after [%s] anywhere\n", s2, s1);
  } else {
    rule = aft(i1, i2)->rule;
    pos1 = aft(i1, i2)->index1;
    pos2 = aft(i1, i2)->index2;
    index1 = rules[rule].rindex[pos1];
    index2 = rules[rule].rindex[pos2];

    if (i1 != index1) {
      while (i1 != index1) {
        int rr, inter;
        rr = *ate(i1, index1);
        inter = rules[rr].lindex;
        printf("  [%s] occurs at the end of [%s] (rule %d : ",
               symbols[i1].text, symbols[inter].text, rules[rr].number);
        print_rule(rr, 0);
        printf(")\n");
        i1 = inter;
      }
      printf("\n");
    }

    printf("[%s] follows [%s] at positions (%d,%d) in rule %d : ",
           symbols[index2].text,
           symbols[index1].text,
           pos1, pos2, rules[rule].number);

    print_rule(rule, 0);
    printf("\n\n");

    show_start_derivation(i2, index2, 2);

  }

}

/*++++++++++++++++++++++++++++++
  User types in pairs of symbols on command line (space separated).
  If s2 can occur after s1 the path through the rules by which this
  happens is shown.  The idea is : if you have a shift/reduce conflict
  where s1 might be reduced when token s2 follows, you want to know
  how this happens.
  ++++++++++++++++++++++++++++++*/

static void
interactive(void)
{
  char line [1024];
  char s1[256], s2[256];

  while (printf("s1 s2> "), fgets(line, sizeof(line), stdin)) {
    if (sscanf(line, "%s%s", s1, s2) == 2) {
      analyse_shift_reduce(s1, s2);
    }
  }

}

/*++++++++++++++++++++++++++++++
  Find the length of the longest RHS of any rule in the grammar.
  ++++++++++++++++++++++++++++++*/

static int
max_nrhs(void)
{
  int i, max, nrhs;
  max = 0;
  for (i=0; i<n_rules; i++) {
    nrhs = rules[i].nrhs;
    if (nrhs > max) max = nrhs;
  }
  return max;
}

/*+ Structure used to hold indices into RHS's of 2 rules which are to
  be tried when looking for a reduce/reduce.  In the simple case this
  is just the 'diagonal' indices of a matrix.  In a more complicated
  case when there are epsilon symbols, there are more entries.  +*/
typedef struct {
  int index1;                   /*+ Index into RHS of rule 1 +*/
  int index2;                   /*+ Index into RHS of rule 2 +*/
  int up_to_tokindex1;          /*+ Index to scan up to (exclusive) to match a token at start for rule 1 +*/
  int up_to_tokindex2;          /*+ Index to scan up to (exclusive) to match a token at start for rule 2 +*/
  int stop_on_no_match;         /*+ If true, means that we halt the rule pair if we fail to get a match on this pair. +*/
} RR_Trial;

/*++++++++++++++++++++++++++++++
  
  ++++++++++++++++++++++++++++++*/

static void
build_trials_vector(Rule *r1, Rule *r2, RR_Trial *trials, int *n_trials)
{
  int nt;
  int min;
  int i, m1, m2, j, k;
  int t1, t2;
  int x1, x2;
  int ee1, ee2;
  int sum;

  nt = 0;

  sum = r1->nrhs + r2->nrhs;

  for (i = 2; i <= sum; i++) {
    for (m1 = 1; m1 < i; m1++) {
      m2 = i - m1;

      if (m1 > r1->nrhs || m2 > r2->nrhs) continue;

      t1 = t2 = 0;

      for (j = 0; j < m1; j++) {
        x1 = r1->rindex[j];
        if (symbols[x1].epsilon_rule < 0) { /* mandatory to match this */
          t1++;
        }
      }
      x1 = r1->rindex[m1-1];
      if (symbols[x1].epsilon_rule >= 0) { /* mandatory to match the last token */
        ee1 = 1;
        t1++;
      } else {
        ee1 = 0;
      }

      for (j = 0; j < m2; j++) {
        x2 = r2->rindex[j];
        if (symbols[x2].epsilon_rule < 0) { /* mandatory to match this */
          t2++;
        }
      }
      x2 = r2->rindex[m2-1];
      if (symbols[x2].epsilon_rule >= 0) { /* mandatory to match the last token */
        ee2 = 1;
        t2++;
      } else {
        ee2 = 0;
      }

#if 0
      printf("i=%d m1=%d m2=%d t1=%d t2=%d\n", i, m1, m2, t1, t2);
#endif

      /* Check conditions */
      if ((t1 > m2) || (t2 > m1)) continue;


      /* Else it's a valid pairing */
      trials[nt].index1 = m1 - 1;
      trials[nt].index2 = m2 - 1;

      if (ee1 || ee2) {
        trials[nt].stop_on_no_match = 0;
      } else {
        trials[nt].stop_on_no_match = 1;
      }
      

      for (k = m1; k < r1->nrhs; k++) {
        x1 = r1->rindex[k];
        if (symbols[x1].epsilon_rule < 0) {
          break;
        }
      }

      if (k >= r1->nrhs) {
        trials[nt].up_to_tokindex1 = r1->nrhs;
      } else {
        trials[nt].up_to_tokindex1 = k;
      }

      for (k = m2; k < r2->nrhs; k++) {
        x2 = r2->rindex[k];
        if (symbols[x2].epsilon_rule < 0) {
          break;
        }
      }

      if (k >= r2->nrhs) {
        trials[nt].up_to_tokindex2 = r2->nrhs;
      } else {
        trials[nt].up_to_tokindex2 = k;
      }

      nt++;
    }
  }

  *n_trials = nt;

}

/*++++++++++++++++++++++++++++++
  Return 0 if no match.
  Return 1 .. nrhs if one of the RHS tokens is matched.
  Return -(ruleno) if the token matches something that can follow the LHS symbol of the rule
  ++++++++++++++++++++++++++++++*/

static int
check_token_match(Rule *r, int tokcode, int first_index, int last_index)
{
  int i;
  int last;
  int ruleno;

#if 0
  printf("Checking match for token [%s] in index range %d through %d for rule (",
         symbols[tokcode].text, first_index, last_index);
  print_rule(r-rules);
  printf(")\n");
#endif

  if (first_index >= r->nrhs) {
#if 0
    printf("Off end - check for after condition [%s] following [%s]\n",
           symbols[tokcode].text, symbols[r->lindex].text);
#endif
    ruleno = aft(r->lindex, tokcode)->rule;
    if (ruleno >= 0) {
      ruleno = rules[ruleno].number;
#if 0
      printf("Matched on rule %d\n", ruleno); 
#endif
      return -(ruleno);
    }
    
  } else {
    if (last_index >= r->nrhs) {
      last = r->nrhs - 1;
    } else {
      last = last_index;
    }

    for (i=first_index; i<=last; i++) {
      if ((tokcode == r->rindex[i]) ||
          (*ats(tokcode, r->rindex[i]) >= 0)) {
        return (1 + i);
      }
    }

  }

  return 0;

}

/*++++++++++++++++++++++++++++++
  For reduce/reduce conflict, show how the conflict token arises
  following the two reducible symbols.
  ++++++++++++++++++++++++++++++*/

static void
show_token_chain(int okstat, int ruleno, int tokindex)
{
  int a1, a2;
  if (okstat < 0) {
    /* I don't think this branch is ever being taken, for some reason */

    int x1, rr;
    x1 = rules[ruleno].lindex;
    rr = aft(x1, tokindex)->rule;
    a1 = aft(x1, tokindex)->index1;
    a2 = aft(x1, tokindex)->index2;
    printf("  [%s] occurs after [%s] at positions (%d,%d) in rule %d (",
           symbols[tokindex].text,
           symbols[x1].text,
           a1, a2, rules[rr].number);
    print_rule(rr, 0);
    printf(")\n");
    if (tokindex != rules[rr].rindex[a2]) {
      show_start_derivation(tokindex, rules[rr].rindex[a2], 4);
    }
  } else {
    int x1, rr;
    x1 = rules[ruleno].rindex[okstat-1];
    if (x1 == tokindex) {
      /* Nothing to do - obvious in printout */
    } else {
      show_start_derivation(tokindex, x1, 4);
    }
  }
}

/*++++++++++++++++++++++++++++++
  
  ++++++++++++++++++++++++++++++*/

static void
analyse_reduce_reduce(char *nt1, char *nt2, char *tok)
{
  int s1, s2;
  int tokindex;
  int r1, r2;
  int i;
  int a1, a2;
  int ss1, ss2;
  int b1, b2;
  int ok1, ok2;
  RR_Trial *trials;
  int n_trials;
  int max_rhs;
  
  /* Special handling required for tok == '$' || tok == '$default' */

  s1 = lookup_symbol(nt1);
  s2 = lookup_symbol(nt2);
  tokindex = lookup_symbol(tok);

  max_rhs = max_nrhs();
  trials = new_array(RR_Trial, max_rhs);

  for (r1 = 0; r1 < n_rules; r1++) {
    for (r2 = 0; r2 < n_rules; r2++) {

      if (rules[r1].lindex != rules[r2].lindex) continue;
      
#if 1
      if (r1 == r2) continue; /* is this right?? */
#endif

      build_trials_vector(rules+r1, rules+r2, trials, &n_trials);

#if 0
      printf("Checking rule1 = (");
      print_rule(r1, 0);
      printf(")\n");
      printf("         rule2 = (");
      print_rule(r2, 0);
      printf(")\n");
      printf("%d trials generated\n", n_trials);
#endif

      for (i = 0; i<n_trials; i++) {
        a1 = trials[i].index1;
        a2 = trials[i].index2;

        ss1 = rules[r1].rindex[a1];
        ss2 = rules[r2].rindex[a2];

#if 0
        printf("Checking posn %d [%s] against %d [%s]\n", 
               a1, symbols[ss1].text, a2, symbols[ss2].text);
#endif

        /* Check whether the conflicting nonterminals occur at the
           ends of the nonterminals we find in the rules we are
           correlating.  Really, we have to check whether the rest of
           'ss1' and 'ss2' would be matched by the same token
           sequence, but I don't have a clean way to do this yet. */

        if (((*ate(s1, ss1) >= 0) ||
             (s1 == ss1)) &&
            ((*ate(s2, ss2) >= 0) ||
             (s2 == ss2))) {

          /* Found it provisionally, check look-ahead token */
          b1 = a1 + 1;
          b2 = a2 + 1;
          ok1 = ok2 = 0;

          ok1 = check_token_match(rules + r1, tokindex, a1 + 1, trials[i].up_to_tokindex1);
          ok2 = check_token_match(rules + r2, tokindex, a2 + 1, trials[i].up_to_tokindex2);

          if (ok1 && ok2) {

            /* Found it!! */

            printf("------------------------------\n\n");

            printf("[%s] can occur at end of [%s] at position %d in rule %d : ",
                   symbols[s1].text, symbols[ss1].text, a1, rules[r1].number);
            print_rule(r1, 0);
            printf("\n");
            if (s1 != ss1) {
              /* Show end derivation chain */
              int si, rr, stemp;
              stemp = s1;
              do {
                rr = *ate(stemp, ss1);
                si = rules[rr].lindex;
                printf("  [%s] occurs at end of [%s] (rule %d : ",
                       symbols[stemp].text, symbols[si].text, rules[rr].number);
                print_rule(rr, 0);
                printf(")\n");
                stemp = si;
              } while (stemp != ss1);
            }                      

            show_token_chain(ok1, r1, tokindex);
            printf("\n");

            printf("[%s] can occur at end of [%s] at position %d in rule %d : ",
                   symbols[s2].text, symbols[ss2].text, a2, rules[r2].number);
            print_rule(r2, 0);
            printf("\n");
            if (s2 != ss2) {
              /* Show end derivation chain */
              int si, rr, stemp;
              stemp = s2;
              do {
                rr = *ate(stemp, ss2);
                si = rules[rr].lindex;
                printf("  [%s] occurs at end of [%s] (rule %d : ",
                       symbols[stemp].text, symbols[si].text, rules[rr].number);
                print_rule(rr, 0);
                printf(")\n");
                stemp = si;
              } while (stemp != ss2);
            }                      

            show_token_chain(ok2, r2, tokindex);
            printf("\n\n");
          }
        }

        /* Advance to next symbol pair to check */
        
        if ((ss1 != ss2) && trials[i].stop_on_no_match) {
          break;
        }

      }
    }
  }  

  free(trials);

}

/*++++++++++++++++++++++++++++++
  Show the possible shifts we have for a particular token in the state
  we're analysing a conflict for.  (As opposed to the shifts that can
  occur if we reduce something in the state and look at what can be
  shifted then, which is what 'analyse_shift_reduce' does.
  ++++++++++++++++++++++++++++++*/

static void
show_possible_shifts(ShiftCond *sc, int nsc, char *token)
{
  int i;
  int toksym;

  toksym = lookup_symbol(token);
  for (i=0; i<nsc; i++) {
    if ((toksym == sc[i].nextsym) ||
        (*ats(toksym, sc[i].nextsym) >= 0)) {
      printf("[%s] can be shifted next in rule %d (",
             token, sc[i].ruleno);
      print_rule(ruleno2idx[sc[i].ruleno], sc[i].focusat);
      printf(")\n");
      if (toksym != sc[i].nextsym) {
        show_start_derivation(toksym, sc[i].nextsym, 4);
      }
      printf("\n");
    }
  }
}


/*++++++++++++++++++++++++++++++++++++++
  Given a rule, a focus symbol in the RHS, and a token code, find
  whether the token can start a symbol following the focussed one.
  Any intervening symbol must be an epsilon.

  static int token_starts_later_symbol Return the RHS index in the
  rule which the token starts, or 0 if none.  (Can't ever be the first
  symbol).

  int toksym The symbols[] index for the token

  int ruleno The rule number.

  int focus The focus position in the RHS, i.e. points to the epsilon
  symbol in the RHS which the grammar wants to reduce where there is
  an S/R conflict.
  ++++++++++++++++++++++++++++++++++++++*/

static int
token_starts_later_symbol(int toksym, int ruleno, int focus)
{
  Rule *r;
  int i;

  r = rules + ruleno2idx[ruleno];

  /* If the focussed symbol is not an epsilon, fail immediately */
  if (symbols[r->rindex[focus]].epsilon_rule < 0) {
    return 0;
  }

  for (i = focus+1; i < r->nrhs; i++) {
    if (*ats(toksym, r->rindex[i]) >= 0) {
      return i;
    }
    /* Otherwise must be an epsilon symbol for loop to continue */
    if (symbols[r->rindex[i]].epsilon_rule < 0) {
      return 0;
      /* Failure */
    }
  }
  
  return 0; /* Failure if we fall out of loop */
}

/*++++++++++++++++++++++++++++++++++++++

  In a situation where the grammar wants to reduce a 'nonterm' when a
  'token' follows, examine how this happens.  There are two cases.  In
  the first, the nonterm is always the LHS of 'redrule'; if this rule
  is active in the state with the focus at the end, we want to show a
  case where the nonterm occurs before something that can start with
  the token elsewhere in the grammar.  In the second case, the nonterm
  is an 'epsilon', i.e. can reduce to the empty string, and the token
  can start the following symbol (or a later one with several
  intervening epsilon symbols.)

  ShiftCond *sc The table of active rules in this state

  int nsc How many active rules

  char *nonterm The nonterminal that the grammar wants to reduce

  char *token The token for which the conflict occurs

  int redrule The rule number that the grammar wants to reduce.
  ++++++++++++++++++++++++++++++++++++++*/

static void
examine_reduction_method(ShiftCond *sc, int nsc, char *nonterm, char *token, int redrule)
{
  int i;
  int matched;

  /* Check whether the rule to be reduced is any of the active ones */
  matched = 0;
  for (i=0; i<nsc; i++) {
    if (redrule == sc[i].ruleno) {
      matched = 1;
      break;
    }
  }

  if (matched) {
    /* The grammar wants to reduce one of the active rules, so we need
       to know where the LHS of that rule occurs before the token
       elsewhere in the grammar. */
    analyse_shift_reduce(nonterm, token);
    printf("\n");
  } else {
    int ntsym;
    int toksym;
    int pos;
    int ssym;

    ntsym = lookup_symbol(nonterm);
    toksym = lookup_symbol(token);

    /* The nonterm must be an epsilon */
    if (symbols[ntsym].epsilon_rule < 0) {
      print_error("Wierd shift/reduce conflict on [%s] which can't reduce to the empty string\n", nonterm);
      return;
    }

    /* Find the active rules where this symbol would be reduced next */
    for (i=0; i<nsc; i++) {
      if (sc[i].focusat) {
        if (ntsym == sc[i].nextsym) {
          /* Got one.  Check whether the offending token can occur at
             the start of the following symbol (or subsequent if there
             are intervening epsilon symbols.) */
          pos = token_starts_later_symbol(toksym, sc[i].ruleno, sc[i].focusat);
          if (pos) {
            printf("Option to reduce epsilon symbol [%s] in rule %d (", nonterm, sc[i].ruleno);
            print_rule(ruleno2idx[sc[i].ruleno], sc[i].focusat);
            printf(")\n");
            ssym = rules[ruleno2idx[sc[i].ruleno]].rindex[pos];
            printf("  Token [%s] starts later symbol [%s] at position %d in rule %d\n",
                   token, symbols[ssym].text, pos, sc[i].ruleno);
            if (ssym != toksym) {
              show_start_derivation(toksym, ssym, 4);
            }
            printf("\n");
          }
        }
      }
    }
  }
}


/*++++++++++++++++++++++++++++++
  Print the report for a shift/reduce conflict
  ++++++++++++++++++++++++++++++*/

static void
handle_shift_reduce_conflict(int state, char *nonterm, char *token, int redrule, ShiftCond *sc, int nsc)
{
  printf("**********************************************************************\n");
  printf("Shift/reduce conflict in state %d when [%s] follows [%s] :\n\n", state, token, nonterm);

  printf("Option to reduce [%s] using rule %d (", nonterm, redrule);
  print_rule(ruleno2idx[redrule], 0);
  printf(")\n  with token [%s] occurring afterwards :\n\n", token);

  examine_reduction_method(sc, nsc, nonterm, token, redrule);

  /* Show which rules we want to shift in in this state */
  printf("Options to shift token [%s] :\n\n", token);
  show_possible_shifts(sc, nsc, token);
}

/*++++++++++++++++++++++++++++++
  
  ++++++++++++++++++++++++++++++*/

static void
handle_reduce_reduce_conflict(int state, char *nonterm, char *token,
                              char *other_nonterm,
                              int ruleno, int other_ruleno)
{
  printf("**********************************************************************\n");
  printf("Reduce/reduce conflict in state %d when [%s] follows [%s] or [%s] :\n\n",
         state, token, nonterm, other_nonterm);

  printf("  1st reducible rule (%4d) : ", other_ruleno);
  print_rule(ruleno2idx[ruleno], 0);
  printf("\n");
  printf("  2nd reducible rule (%4d) : ", ruleno);
  print_rule(ruleno2idx[other_ruleno], 0);
  printf("\n\n");

  analyse_reduce_reduce(nonterm, other_nonterm, token);
  
  printf("\n");
}

/*++++++++++++++++++++++++++++++
  Grab the reduce nonterminal from a suitable line
  ++++++++++++++++++++++++++++++*/

static char *
get_reduce_nonterm(char *line)
{
  char *p, *q;
  static char nt[256];
  q = nt;
  p = strstr(line, "reduce using rule");
  while (*p != '(') p++;
  p++;
  while (*p != ')') {
    *q++ = *p++;
  }
  *q = 0;
  return nt;
}

/*++++++++++++++++++++++++++++++
  
  ++++++++++++++++++++++++++++++*/

static int
get_reduce_ruleno(char *line)
{
  char *p;
  char *marker = "reduce using rule ";
  int result;

  p = strstr(line, marker);
  if (sscanf(p + strlen(marker), "%d", &result) != 1) {
    print_error("Could not read rule number from reduce line [%s]\n", line);
    exit(1);
  } else {
    return result;
  }
}

/*++++++++++++++++++++++++++++++
  
  ++++++++++++++++++++++++++++++*/

static void
parse_state_rule_line(char *line, ShiftCond *sc, int *nsc)
{
  char *p;
  char field[256];
  int pos = 0, focus;
  int ruleno;

  p = strstr(line, " -> ");
  p += 4; /* Advance over -> to start looking at RHS */
  do {
    read_field(&p, field);
    if (!strncmp(field, "(rule", 5)) {
      break;
    }
    if (!strcmp(field, ".")) {
      focus = pos;
    } else {
      pos++;
    }
  } while (1);

  if (focus == pos) {
    /* Only happens if the focus is at the end of the RHS symbols,
       i.e. a state where the parser wants to reduce.  Change focus to
       zero, which cannot normally happen. */
    focus = 0;
  }
  
  read_field(&p, field);
  if (sscanf(field, "%d", &ruleno) == 1) {
    sc[*nsc] = (ShiftCond) {ruleno, focus, rules[ruleno2idx[ruleno]].rindex[focus]};
    ++*nsc;
  } else {
    print_error("Could not read rule number from line [%s]\n", line);
    exit(1);
  }
}

/*++++++++++++++++++++++++++++++
  Scan each of the states.  Look for shift/reduce and reduce/reduce conflicts in the table.
  For each, print out a report of how it arises.
  ++++++++++++++++++++++++++++++*/

static void
scan_state_table(FILE *in)
{
  typedef struct {
    enum {UNKNOWN, SHIFT, REDUCE} type;
    char red_as[64]; /* The nonterminal that would be reduced */
    int rule;
  } Action;

  Action actions[n_symbols];

  ShiftCond shiftconds[n_rules];
  int nsc; /* number of coditions found */

  char line[2048];
  char token[256];
  int cur_state = -1;
  int i;
  int sym;
  int ruleno;
  char *red;
  char *red_nt;

  while (fgets(line, sizeof(line), in)) {

    line[strlen(line) - 1] = 0; /* Remove lf */

    if (!strncmp(line, "state", 5)) {
      cur_state = atoi(line+6);
      for (i=0; i<n_symbols; i++) {
        actions[i] = (Action) {UNKNOWN} ;
      }

      nsc = 0; /* Reset shift conditions */

    } else {
      if (strstr(line, " -> ")) {
        /* This is a line showing the position where we are within a rule */
        parse_state_rule_line(line, shiftconds, &nsc);
      }

      if (strstr(line, "shift, and go to state")) {
        if (sscanf(line, "%s", token) != 1) {
          print_error("Unexpected error scanning shift token in [%s]\n", line);
          exit(1);
        }

        sym = lookup_symbol(token);
        if (actions[sym].type != UNKNOWN) {
          print_error("Action type is known for shift?!\n");
          exit(1);
        }
        actions[sym].type = SHIFT;
      }

      red = strstr(line, "reduce using rule");
      if (red) {
        red_nt = get_reduce_nonterm(line);
        ruleno = get_reduce_ruleno(line);

        if (sscanf(line, "%s", token) != 1) {
          print_error("Unexpected error scanning shift token in [%s]\n", line);
          exit(1);
        }

        sym = lookup_symbol(token);

        if (*(red - 1) == '[') {
          /* conflict occurred - a reduction that is not taken */
          switch (actions[sym].type) {
            case SHIFT:
              /* Shift/reduce conflict */
              handle_shift_reduce_conflict(cur_state, red_nt, token, ruleno, shiftconds, nsc);
              break;
              
            case REDUCE:
              /* Reduce/reduce conflict */
              handle_reduce_reduce_conflict(cur_state, red_nt, token, actions[sym].red_as, ruleno, actions[sym].rule);
              break;

            case UNKNOWN:
              break;
          }


        } else {
          /* not conflict */
          if (actions[sym].type != UNKNOWN) {
            print_error("Action type is known for reduce?!\n");
            exit(1);
          }
          actions[sym].type = REDUCE;
          strcpy(actions[sym].red_as, red_nt);
          actions[sym].rule = ruleno;
        }
      }
      
    }
  }

}



/*++++++++++++++++++++++++++++++
  
  ++++++++++++++++++++++++++++++*/

int main (int argc, char **argv)
{
  FILE *in;

  if (argc < 2) {
    print_error("Supply a .output file as argument\n");
    exit(1);
  }

  in = fopen(argv[1], "r");
  if (!in) {
    print_error("Can't open .output file?\n");
    exit(1);
  }

  parse_rules(in);
  parse_terminals(in);
  parse_nonterms(in);

  index_rules();
  find_epsilons();

  compute_at_starts();
  compute_at_ends();
  compute_after_records();

  scan_state_table(in);
  fclose(in);

  return 0;

}
