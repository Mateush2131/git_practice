#include "single_storage_algorithm.h"
#include <iostream>

void SingleStorageAlgorithm::backup(const std::vector<std::shared_ptr<BackupObject>>& objects) {
    std::cout << "Резервное копирование всех объектов в единое хранилище" << std::endl;
    for (const auto& obj : objects) {
        std::cout << "Включение файла: " << obj->getPath() << std::endl;
        // Здесь будут реальные операции с файловой системой
    }
}