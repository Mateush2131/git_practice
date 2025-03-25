#pragma once
#ifndef BACKUP_EXCEPTION_H
#define BACKUP_EXCEPTION_H

#include <string>
#include <stdexcept>

class BackupException : public std::runtime_error {
public:
    explicit BackupException(const std::string& msg)
        : std::runtime_error(msg) {}
};

#endif 