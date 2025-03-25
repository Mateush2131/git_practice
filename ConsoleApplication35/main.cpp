#include <iostream>
#include <memory>
#include "backup_job.h"
#include "backup_object.h"
#include "split_storage_algorithm.h"
#include "single_storage_algorithm.h"
#include "backup_exception.h"

int main() {
    try {
        BackupJob job;

        job.setAlgorithm(std::make_unique<SplitStorageAlgorithm>());
        job.createRestorePoint();

        job.setAlgorithm(std::make_unique<SingleStorageAlgorithm>());
        job.createRestorePoint();
    }
    catch (const BackupException& e) {
        std::cerr << "Ошибка резервного копирования: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}