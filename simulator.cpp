#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#endif

void simulateDevice(const std::string& port) {
#ifdef _WIN32
    HANDLE hSerial = CreateFile(port.c_str(), GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Ошибка открытия порта!" << std::endl;
        return;
    }
#else
    int fd = open(port.c_str(), O_WRONLY);
    if (fd < 0) {
        std::cerr << "Ошибка открытия порта!" << std::endl;
        return;
    }
#endif

    std::srand(std::time(nullptr));

    while (true) {
        float temperature = 20.0f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 10.0f));
        std::string data = std::to_string(temperature) + "\n";

#ifdef _WIN32
        DWORD bytesWritten;
        WriteFile(hSerial, data.c_str(), data.size(), &bytesWritten, NULL);
#else
        write(fd, data.c_str(), data.size());
#endif

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

#ifdef _WIN32
    CloseHandle(hSerial);
#else
    close(fd);
#endif
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Использование: " << argv[0] << " <порт>" << std::endl;
        return 1;
    }

    std::string port = argv[1]; 
    simulateDevice(port);
    return 0;
}
