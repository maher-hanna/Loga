#pragma once

#include <vector>
#include <string>
#include <chrono>
#include "LogaCallable.h"
#include "Interpreter.h"

class clock : public LogaCallable {
	int arity() { return 0; }

	std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*> call(Interpreter interpreter,
		std::vector<std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*>> arguments) {
		auto now = std::chrono::system_clock::now();

		auto seconds = std::chrono::duration_cast<std::chrono::seconds>(
			now.time_since_epoch())
			.count();
		return (double)seconds;
	}

	std::string toString() { return "<native fn>"; }
};