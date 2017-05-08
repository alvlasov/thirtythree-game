/*!
    @file ScriptingUnit.cpp
    @brief Реализация простого ассемблера и CPU
    @author Власов Александр, Татьяна Мамонтова, Алена Бескровная
    @date Май 2017
*/

#include "ScriptingUnit.h"

namespace thirtythree {

ScriptingUnit::ScriptingUnit(size_t registersCount)
    : registers_ (registersCount) {
    LOG_DEBUG("ScriptingUnit: Constructor " << __PRETTY_FUNCTION__);
    LOG_DEV("ScriptingUnit: Registers count = " << registers_.size());
}


ScriptingUnit::ScriptingUnit(std::vector<double> registers)
    : registers_ (registers) {
    LOG_DEBUG("ScriptingUnit: Constructor " << __PRETTY_FUNCTION__);
    LOG_DEV("ScriptingUnit: Registers count = " << registers_.size());
}

ScriptingUnit::ScriptingUnit(std::string filename, size_t registersCount)
    : registers_ (registersCount) {
    LOG_DEBUG("ScriptingUnit: Constructor " << __PRETTY_FUNCTION__);
    LOG_DEV("ScriptingUnit: Registers count = " << registers_.size());
    Assemble(filename);
}

ScriptingUnit::ScriptingUnit(std::string filename, std::vector<double> registers)
    : registers_ (registers) {
    LOG_DEBUG("ScriptingUnit: Constructor " << __PRETTY_FUNCTION__);
    LOG_DEV("ScriptingUnit: Registers count = " << registers_.size());
    Assemble(filename);
}

ScriptingUnit::ScriptingUnit(std::vector<ScriptingUnit::Command> code, size_t registersCount)
    : code_ (code), registers_ (registersCount) {
    LOG_DEBUG("ScriptingUnit: Constructor " << __PRETTY_FUNCTION__);
    LOG_DEV("ScriptingUnit: Registers count = " << registers_.size());
}

ScriptingUnit::ScriptingUnit(std::vector<ScriptingUnit::Command> code, std::vector<double> registers)
    : code_ (code), registers_ (registers) {
    LOG_DEBUG("ScriptingUnit: Constructor " << __PRETTY_FUNCTION__);
    LOG_DEV("ScriptingUnit: Registers count = " << registers_.size());
}

ScriptingUnit::~ScriptingUnit() {
    LOG_DEBUG("ScriptingUnit: Destructor " << __PRETTY_FUNCTION__);
}

void ScriptingUnit::Assemble(std::string filename) {
    std::string buff;
    std::ifstream fin(filename);
    LOG_DEBUG("ScriptingUnit: Reading code from " << filename);
    while (true) {
        if (!(fin >> buff)) {
            break;
        }
        auto it = available_commands_.begin();
        while (it != available_commands_.end()) {
            if (it->name_ == buff) {
                code_.push_back(*it);
                if (code_.back().has_argument_) {
                    fin >> buff;
                    LOG_DEV("ScriptingUnit: reading " << code_.back().name_ << " " << buff);
                    code_.back().argument_ = std::stoi(buff);
                } else {
                    LOG_DEV("ScriptingUnit: reading " << buff);
                }
                break;
            }
            it++;
        }
        if (it == available_commands_.end()) {
            LOG_ERROR("ScriptingUnit: Unknown command in file " << filename);
            throw std::runtime_error("ScriptingUnit: Unknown command in file");
        }
    }
    fin.close();
}

void ScriptingUnit::Execute() {
    collectMarks();
    LOG_DEBUG("ScriptingUnit: Executing script...");
    auto it = code_.begin();
    while (it != code_.end()) {
        it->Execute(it);
    }
}

void ScriptingUnit::collectMarks() {
    LOG_DEBUG("ScriptingUnit: Collecting marks...");
    for (auto it = code_.begin(); it != code_.end(); it++) {
        if (it->name_ == "mark") {
            marks_.insert({it->argument_, it + 1});
            LOG_DEV("ScriptingUnit: Mark :" << it->argument_ << " found");
        }
    }
}

}
