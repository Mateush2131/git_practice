#pragma once
#ifndef SPLIT_STORAGE_ALGORITHM_H
#define SPLIT_STORAGE_ALGORITHM_H

#include "backup_algorithm.h"

class SplitStorageAlgorithm : public BackupAlgorithm {
public:
    void backup(const std::vector<std::shared_ptr<BackupObject>>& objects) override;
};

#endif 