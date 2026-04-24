// Loga/typedefs.h
#pragma once

#include <variant>
#include <string>
#include <cstddef> // for std::nullptr_t (optional but safe)

class LogaCallable;
class LogaClass;
class LogaInstance;

using Value = std::variant<double, int, std::string, std::nullptr_t, bool, LogaCallable*, LogaInstance*>;