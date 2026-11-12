#include "Process.h"

bool Process::isFileNameValid() {
    if (fileName.empty()) {
        return false;
    }

    string trimmed = fileName;
    while (!trimmed.empty() && (trimmed.front() == ' ' || trimmed.front() == '\t' ||
                                trimmed.front() == '\r' || trimmed.front() == '\n')) {
        trimmed.erase(trimmed.begin());
    }
    while (!trimmed.empty() && (trimmed.back() == ' ' || trimmed.back() == '\t' ||
                                trimmed.back() == '\r' || trimmed.back() == '\n')) {
        trimmed.pop_back();
    }

    if (trimmed.empty()) {
        return false;
    }

    for (char ch : trimmed) {
        if (ch == '\\' || ch == '/' || ch == ':' || ch == '*' || ch == '?' ||
            ch == '"' || ch == '<' || ch == '>' || ch == '|') {
            return false;
        }
    }
    return true;
}