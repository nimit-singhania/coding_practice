// This file defines an abstract execution framework that enables abstract analysis for programs
// enabling light-weight analysis to be defined for reasoning about programs / code / software.
//
// The abstract execution framework provides the following entities:
// * abstract_state: this is a simplified state that tracks necessary information for the analysis,
//     ex. whether a pointer is null, stride for consecutive threads, etc.
// * abstract_domain: this is the abstraction that is applied on the values in the program enabling
//     abstract state to be defined from concrete state ( dependence of a scalar variable on a
//     parameter for example).
// * abstract_execution_engine: this runs the execution of the program in the abstract domain, to
//     obtain the necessary results for the analysis.

// The execution engine relies on the availability of the following underlying interfaces:
// * Instruction* - this presents the instruction that is executed by the program.
// * Value* - this represents the values that are either instructions or variables. When the
//     values have a unique definitions, then each value corresponds to the instruction defining
//     the value. When more than one instructions can update a value, then the value is not
//     necessarily represented by a single instruction. An abstract state usually consists of
//     variables mapped to their abstract values.

// The abstract execution engine further assumes the availability of the following
// * ExecuteStatement(Instruction*, abstract_state& st): this executes a statement on the abstract
//     state input to the statement. This must be defined by the analysis.
// * MergeValues(value* v1, value* v2, abstract_state& st): this allows merging values in an abstract
//     state.
// * GetNextExecutionUnit(): this returns the next instruction to be executed in the abstract engine.


struct abstract_state;

struct abstract_domain;

class Instruction;

class Value;

abstract_state* initializeAbstractState();

void ExecuteStatement(Instruction* I, abstract_state& st); // updates state in-place.

void MergeValues(Value* v1, Value* v2, abstract_state& st); // TODO

Instruction* GetNextExecutionUnit();

class abstract_execution_engine {
	abstract_state* current_state;

public:
	void run(Instruction* entry);
};
