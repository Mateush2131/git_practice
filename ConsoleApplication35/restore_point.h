#ifndef RESTORE_POINT_H
#define RESTORE_POINT_H

#include <vector>
#include <memory>
#include <ctime>
#include "backup_object.h"

class RestorePoint {
private:
    std::time_t time;
    std::vector<std::shared_ptr<BackupObject>> objects;
public:
    RestorePoint();
    void addObject(const std::shared_ptr<BackupObject>& obj);
    std::vector<std::shared_ptr<BackupObject>> getObjects() const;
    std::time_t getTime() const;
};

#endif 