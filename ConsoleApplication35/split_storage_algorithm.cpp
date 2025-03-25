#include "split_storage_algorithm.h"
#include <iostream>

void SplitStorageAlgorithm::backup(const std::vector<std::shared_ptr<BackupObject>>& objects) {
    for (const auto& obj : objects) {
        std::cout << "��������� ����������� " << obj->getPath()
            << " � ��������� ���������" << std::endl;
      
    }
}