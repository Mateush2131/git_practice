#include "backup_object.h"

BackupObject::BackupObject(const std::string& path) : path(path) {
    if (path.empty()) {
        throw BackupException("Путь не может быть пустым");
    }
}

std::string BackupObject::getPath() const {
    return path;
}