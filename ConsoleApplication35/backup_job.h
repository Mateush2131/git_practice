#ifndef BACKUP_JOB_H
#define BACKUP_JOB_H

#include <vector>
#include <memory>
#include "backup_object.h"
#include "restore_point.h"
#include "backup_algorithm.h"

class BackupJob {
private:
    std::vector<std::shared_ptr<RestorePoint>> restorePoints;
    std::unique_ptr<BackupAlgorithm> algorithm;
public:
    void setAlgorithm(std::unique_ptr<BackupAlgorithm> algo);
    void addObject(const std::shared_ptr<BackupObject>& obj);
    void removeObject(const std::shared_ptr<BackupObject>& obj);
    void createRestorePoint();
};

#endif // BACKUP_JOB_H