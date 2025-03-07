#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <ctime>
class BackupException : public std::exception {
private:
    std::string message;
public:
    BackupException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};


class BackupObject {
private:
    std::string path;
public:
    BackupObject(const std::string& path) : path(path) {
        if (path.empty()) {
            throw BackupException("Path cannot be empty");
        }
    }
    std::string getPath() const { return path; }
};

class RestorePoint {
private:
    std::time_t time;
    std::vector<std::shared_ptr<BackupObject>> objects;
public:
    RestorePoint() : time(std::time(0)) {}
    void addObject(const std::shared_ptr<BackupObject>& obj) {
        objects.push_back(obj);
    }
    std::vector<std::shared_ptr<BackupObject>> getObjects() const {
        return objects;
    }
    std::time_t getTime() const { return time; }
};


class BackupAlgorithm {
public:
    virtual void backup(const std::vector<std::shared_ptr<BackupObject>>& objects) = 0;
    virtual ~BackupAlgorithm() = default;
};


class SplitStorageAlgorithm : public BackupAlgorithm {
public:
    void backup(const std::vector<std::shared_ptr<BackupObject>>& objects) override {
        for (const auto& obj : objects) {
            std::cout << "Backing up " << obj->getPath() << " to separate storage" << std::endl;
        }
    }
};

class SingleStorageAlgorithm : public BackupAlgorithm {
public:
    void backup(const std::vector<std::shared_ptr<BackupObject>>& objects) override {
        std::cout << "Backing up all objects to single storage" << std::endl;
        for (const auto& obj : objects) {
            std::cout << "Including " << obj->getPath() << std::endl;
        }
    }
};


class BackupJob {
private:
    std::vector<std::shared_ptr<BackupObject>> objects;
    std::vector<std::shared_ptr<RestorePoint>> restorePoints;
    std::unique_ptr<BackupAlgorithm> algorithm;
public:
    void setAlgorithm(std::unique_ptr<BackupAlgorithm> algo) {
        algorithm = std::move(algo);
    }
    void addObject(const std::shared_ptr<BackupObject>& obj) {
        objects.push_back(obj);
    }
    void removeObject(const std::shared_ptr<BackupObject>& obj) {
        objects.erase(std::remove(objects.begin(), objects.end(), obj), objects.end());
    }
    void createRestorePoint() {
        auto restorePoint = std::make_shared<RestorePoint>();
        for (const auto& obj : objects) {
            restorePoint->addObject(obj);
        }
        restorePoints.push_back(restorePoint);
        if (algorithm) {
            algorithm->backup(restorePoint->getObjects());
        }
    }
};

int main() {
    try {
        BackupJob job;
        job.addObject(std::make_shared<BackupObject>("/path/to/file1"));
        job.addObject(std::make_shared<BackupObject>("/path/to/file2"));

        job.setAlgorithm(std::make_unique<SplitStorageAlgorithm>());
        job.createRestorePoint();

        job.setAlgorithm(std::make_unique<SingleStorageAlgorithm>());
        job.createRestorePoint();
    }
    catch (const BackupException& e) {
        std::cerr << "Backup error: " << e.what() << std::endl;
    }

    return 0;
}