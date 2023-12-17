#include <iostream>
#include <fstream>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>

class Logger {
public:
    Logger(const std::string& filename) : file(filename, std::ios_base::app) {}

    void writeLog(const std::string& message) {
        std::unique_lock<std::shared_mutex> lock(mutex);
        file << message << "\n";
    }
    std::string readLog() {
        std::shared_lock<std::shared_mutex> lock(mutex);
        std::string line;
        if (file.is_open()) {
            if (std::getline(file, line)) {
                return line;
            }
        }
        return ""; // »ли кака€-то друга€ обработка, если строка не прочитана
    }

    ~Logger() {
        if (file.is_open()) {
            file.close();
        }
    }

private:
    std::ofstream file;
    mutable std::shared_mutex mutex;
};

int main() {
    Logger logger("log.txt");

    // ѕример записи и чтени€ из разных потоков
    std::thread writer([&]() {
        for (int i = 0; i < 5; ++i) {
            logger.writeLog("Message " + std::to_string(i));
        }
        });

    std::thread reader([&]() {
        for (int i = 0; i < 5; ++i) {
            std::string line = logger.readLog();
            std::cout << "Read: " << line << std::endl;
        }
        });

    writer.join();
    reader.join();

    return 0;
}
