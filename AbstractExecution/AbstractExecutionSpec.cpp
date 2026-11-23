// This file defines the specification for an abstract execution engine.
// An abstract execution engine runs a program in an abstract domain enabling
// analysis of the program using a simplified state carrying information for
// the analysis, allowing code to be simulated on alternative platforms (like CPU)
// and to check robustness of the underlying semantics of the actual execution
// including performance and correctness.


// The following spec should be followed by an abstract execution engine:
// 1. An abstract domain that defines the values for variables can be specified by the user.
// 2. The corresponding abstract semantics shall be provided in the framework to support the
//      abstract domain.
// 3. Given the abstract domain and the abstract semantics, the execution engine should be
//      able to simulate the program with the desired abstract semantics.
// 4. The initial abstract state where the execution starts should have minimal assumptions
//       about the actual state, enabling it to represent a large number of actual states.
// 5. The execution engine should populate units of work in the worklist corresponding to
//       the execution in the abstract domain.
// 6. The units might represent the same instruction to be executed for different states,
//       where the states can be merged to reduce the number of states.
// 7. The merged state in case of merge of two units, must represent and encompass both
//       states that were merged together.
// 8. The execution should ensure progress, and for specific analyses, guarantees on
//       termination should be provided.
// 9. The abstract execution of a program should correspond to the actual execution of
//       program via a simple abstraction.
// 10. The trade-offs between the outcome of the abstract execution and the actual execution
//       due to imprecision in libraries, operations and code complexity should be clearly
//       spelled out.
