#pragma once
#ifndef BACKUP_ALGORITHM_H
#define BACKUP_ALGORITHM_H

#include <vector>
#include <memory>
#include "backup_object.h"

class BackupAlgorithm {
public:
    virtual void backup(const std::vector<std::shared_ptr<BackupObject>>& objects) = 0;
    virtual ~BackupAlgorithm() = default;
};

#endif 