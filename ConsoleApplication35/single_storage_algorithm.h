#ifndef SINGLE_STORAGE_ALGORITHM_H
#define SINGLE_STORAGE_ALGORITHM_H

#include "backup_algorithm.h"

class SingleStorageAlgorithm : public BackupAlgorithm {
public:
    void backup(const std::vector<std::shared_ptr<BackupObject>>& objects) override;
};

#endif 