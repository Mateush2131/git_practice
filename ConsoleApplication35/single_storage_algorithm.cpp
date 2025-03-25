#include "single_storage_algorithm.h"
#include <iostream>

void SingleStorageAlgorithm::backup(const std::vector<std::shared_ptr<BackupObject>>& objects) {
    std::cout << "��������� ����������� ���� �������� � ������ ���������" << std::endl;
    for (const auto& obj : objects) {
        std::cout << "��������� �����: " << obj->getPath() << std::endl;
        // ����� ����� �������� �������� � �������� ��������
    }
}