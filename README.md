Compiler Construction - Phase 1: Lexical Analyzer

This repository contains the solution to Phase 1 of the Compiler Construction course project. It includes the design and implementation of a lexical analyzer (scanner) for a custom programming language using the table-driven method.

📑 Assignment Description

The goal of this phase was to implement a lexical analyzer (scanner) that performs the following:

Tasks:

Regular Definitions for:

Identifiers (must start with underscore/letter and contain at least one underscore)

Numbers (signed, unsigned, floating point, exponential)

Punctuations: [ , { , ( , ) , } , ], ::

Operators: < , > , <>, :=, ==, + , -, ++, +=, <=, >=, %, ||, &&, !=, *, ", ” , /, <<, >>

Keywords: (includes C++-like and custom e.g. Adadi, Wapas, Agar, Mantiqi, Ashriya, etc.)

Regular Expressions and DFA Diagrams created manually and included in a separate PDF file.

Single Transition Diagram (manually constructed from all token categories).

Table-Driven DFA Implementation in C++ (no STL; use of own data structures like linked list, hash tables encouraged).

Output Requirements:

Token classification with types and values

Output stored in symbols.txt and literals.txt

Invalid tokens reported with error handling

📂 Repository Structure

File

Description

lexical_analyzer.cpp

Main implementation of the table-driven lexical analyzer

symbols.txt

Stores all unique identifiers with their index

literals.txt

Stores string literals (between quotes) with index

keywords.txt

Empty/placeholder file used for consistency

transition_table.xlsx

DFA transition table with state mappings and transitions

assignment_description.pdf

Original assignment problem statement and sample code

dfa_and_regex.pdf

Handwritten or diagrammed regular expressions and DFA used in phase 1

⚙️ How It Works

Lexical Analyzer Logic

Uses a 2D map (unordered_map<int, unordered_map<char, int>>) as a transition table

Accepts input string and tokenizes using buffer chunks of 25 characters

DFA states are changed based on transitions defined in the Excel sheet

Identifiers, literals, keywords, numbers, and operators are all identified and stored

Keyword Matching

Keywords are matched via a manual list

Special attention to input-> and output<- which are compound keywords

Token Output

Console output color-coded using windows.h

Tokens printed as <TokenType, Index>

Indexes maintained for reuse (symbol table simulation)

📌 Notes

Implemented in C++ using standard input for testing.

Custom buffer and character queue used for lexeme construction.

Requires windows.h for colored console output (Windows only).

DFA and transitions were manually derived based on assignment and the dfa_and_regex.pdf reference.

🧪 Sample Keywords Used

asm, Wagarna, new, this, auto, enum, operator, throw, Mantiqi, explicit, private, True,
break, export, protected, try, case, extern, public, typedef, catch, False, register,
typeid, Harf, Ashriya, typename, Adadi, class, for, Wapas, union, const, dost, short,
unsigned, goto, signed, using, continue, Agar, sizeof, virtual, default, inline, static,
Khali, delete, volatile, do, long, struct, double, mutable, switch, while, namespace,
template, Marqazi, Matn, input->, output<-

🔧 Tools & Constraints

Language: C++

Development Approach: Table-driven DFA

STL containers not used; basic arrays and manual structures used instead

🏁 Status

✅ Phase 1 implemented successfully and integrated with the assignment's transition table, DFA diagrams, and rules.

🧾 License

This project is for academic use as part of Compiler Construction coursework.

