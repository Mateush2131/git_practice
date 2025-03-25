#pragma once
#ifndef BACKUP_OBJECT_H
#define BACKUP_OBJECT_H

#include <string>
#include "backup_exception.h"

class BackupObject {
private:
    std::string path;
public:
    explicit BackupObject(const std::string& path);
    std::string getPath() const;
};

#endif 