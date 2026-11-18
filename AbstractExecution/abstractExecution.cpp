
#include "abstractExecution.hpp"

#include <vector>

abstract_state* merge(abstract_state* s1, abstract_state* s2) {
	// TODO merge states.
	return nullptr;
}

void abstract_execution_engine::run(Instruction* entry) {
	// Use a worklist method to run the analysis.
	std::vector<std::pair<Instruction*, abstract_state*>> worklist;

	if (!current_state) {
		current_state = initializeAbstractState();
	}
	worklist.push_back(std::make_pair(entry, current_state));

	while (!worklist.empty()) {
		// Get the first item in the worklist.
		auto next = worklist[0];
		auto* inst = next.first;
		auto* state = next.second;
		worklist.erase(worklist.begin()); // dequeue.

		ExecuteStatement(inst, *state);

		while (true) {
			auto work = GetNextExecutionUnit();
			if (work.first == nullptr) {break;}
			// Check if the unit can be merged with an existing action item.
			bool merged = false;
			for (auto& w : worklist) {
				if (w.first == work.first) {
					// Merge units.
					w.second = merge(w.second, work.second);
					merged = true;
				}
			}
			if (!merged)
				worklist.push_back(work);
		}
	}
}
