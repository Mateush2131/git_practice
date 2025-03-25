#include "restore_point.h"

RestorePoint::RestorePoint() : time(std::time(nullptr)) {}

void RestorePoint::addObject(const std::shared_ptr<BackupObject>& obj) {
    objects.push_back(obj);
}

std::vector<std::shared_ptr<BackupObject>> RestorePoint::getObjects() const {
    return objects;
}

std::time_t RestorePoint::getTime() const {
    return time;
}