#include "backup_job.h"

void BackupJob::setAlgorithm(std::unique_ptr<BackupAlgorithm> algo) {
    algorithm = std::move(algo);
}

void BackupJob::addObject(const std::shared_ptr<BackupObject>& obj) {
    // Объекты будут добавляться при создании точек восстановления
}

void BackupJob::removeObject(const std::shared_ptr<BackupObject>& obj) {
    // Управление объектами при создании точек восстановления
}

void BackupJob::createRestorePoint() {
    auto restorePoint = std::make_shared<RestorePoint>();
    if (algorithm) {
        algorithm->backup(restorePoint->getObjects());
    }
    restorePoints.push_back(restorePoint);
}#include "backup_job.h"

void BackupJob::setAlgorithm(std::unique_ptr<BackupAlgorithm> algo) {
    algorithm = std::move(algo);
}

void BackupJob::addObject(const std::shared_ptr<BackupObject>& obj) {
    // Объекты будут добавляться при создании точек восстановления
}

void BackupJob::removeObject(const std::shared_ptr<BackupObject>& obj) {
    // Управление объектами при создании точек восстановления
}

void BackupJob::createRestorePoint() {
    auto restorePoint = std::make_shared<RestorePoint>();
    if (algorithm) {
        algorithm->backup(restorePoint->getObjects());
    }
    restorePoints.push_back(restorePoint);
}