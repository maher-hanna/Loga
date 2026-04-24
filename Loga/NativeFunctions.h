#pragma once

#include <vector>
#include <string>
#include <chrono>
#include "LogaCallable.h"
#include "Interpreter.h"
#include "Value.h"

class clock : public LogaCallable {
	int arity() { return 0; }

	Value call(Interpreter interpreter,
		std::vector<Value> arguments) {
		auto now = std::chrono::system_clock::now();

		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(
			now.time_since_epoch())
			.count();
		return (double)seconds;
	}

	std::string toString() { return "<native fn>"; }
};