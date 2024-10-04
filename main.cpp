#include <iostream>
#include <windows.h>
#include <string>

COORD getCursorPosition(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return csbi.dwCursorPosition;
    }

    // in case of failure
    return {0, 0};
}

void drawHeader() {
    std::cout << "Fri Mar 29 18:42:38 2024\n";
    std::cout << "+-----------------------------------------------------------------------------------------+\n";
    std::cout << "| NVIDIA-SMI 551.86                 Driver Version: 551.86         CUDA Version: 12.4     |\n";
    std::cout << "|-----------------------------------------+------------------------+----------------------+\n";
    std::cout << "| GPU  Name                     TCC/WDDM  | Bus-Id          Disp.A | Volatile Uncorr. ECC |\n";
    std::cout << "| Fan  Temp   Perf          Pwr:Usage/Cap |           Memory-Usage | GPU-Util  Compute M. |\n";
    std::cout << "|                                         |                        |               MIG M. |\n";
    std::cout << "|=========================================+========================+======================|\n";
    std::cout << "|   0  NVIDIA GeForce RTX 1080 ...  WDDM  |   00000000:26:00.0  On |                  N/A |\n";
    std::cout << "| 28%   37C    P8             11W /  180W |     701MiB /   8192MiB |      0%      Default |\n";
    std::cout << "|                                         |                        |                  N/A |\n";
    std::cout << "+-----------------------------------------+------------------------+----------------------+\n";
}

void drawProcesses() {
    std::cout << "+-----------------------------------------------------------------------------------------+\n";
    std::cout << "| Processes:                                                                              |\n";
    std::cout << "|  GPU   GI   CI        PID   Type   Process name                              GPU Memory |\n";
    std::cout << "|        ID   ID                                                               Usage      |\n";
    std::cout << "|=========================================================================================|\n";
    std::cout << "|    0   N/A  N/A       188    C+G   ...al\\Discord\\app-1.0.9164\\Discord.exe      N/A      |\n";
    std::cout << "|    0   N/A  N/A      1372    C+G   ...5n1h2txyewy\\ShellExperienceHost.exe      N/A      |\n";
    std::cout << "|    0   N/A  N/A      6192    C+G   C:\\Windows\\explorer.exe                     N/A      |\n";
    std::cout << "|    0   N/A  N/A      8860    C+G   ...siveControlPanel\\SystemSettings.exe      N/A      |\n";
    std::cout << "|    0   N/A  N/A     10812    C+G   ...334.0_x64__dt26b99r8h8gj\\RtkUWP.exe      N/A      |\n";
    std::cout << "+-----------------------------------------------------------------------------------------+\n";
}

void updateFieldAtPosition(COORD coord, const std::string& field, int maxLength, HANDLE hConsole) {
    SetConsoleCursorPosition(hConsole, coord);
    std::string truncatedField = field.substr(0, maxLength);  // Truncate if needed
    std::cout << truncatedField << std::string(maxLength + 3 - truncatedField.length(), ' ');  // Add padding
}

void updateProcessInfo(int processIndex, const std::string & pid, const std::string & type, const std::string & processName, const std::string & gpuUsage) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Update PID
    std::string newPid = pid.length() > 5 ? "..." + pid.substr(pid.length() - 2, 2) : pid;
    COORD pidCoord = { 22, static_cast<SHORT>(17 + processIndex) };
    updateFieldAtPosition(pidCoord, newPid, 5, hConsole);

    // Update Type
    std::string newType = type.length() > 3 ? ".." + type.substr(type.length() - 1, 1) : type;
    COORD typeCoord = { 31, static_cast<SHORT>(17 + processIndex) };
    updateFieldAtPosition(typeCoord, newType, 5, hConsole);

    // Update Process Name
    std::string newProcessName = processName.length() > 38 ? "..." + processName.substr(processName.length() - 35, 35) : processName;
    COORD processNameCoord = { 37, static_cast<SHORT>(17 + processIndex) };
    updateFieldAtPosition(processNameCoord, newProcessName, 38, hConsole);

    // Update GPU Memory Usage
    std::string newUsage = gpuUsage.length() > 5 ? "..." + gpuUsage.substr(gpuUsage.length() - 2, 2) : gpuUsage;
    COORD usageCoord = { 81, static_cast<SHORT>(17 + processIndex) };
    SetConsoleCursorPosition(hConsole, usageCoord);
    std::string formattedUsage = newUsage.substr(0, 5) + "MiB";
    std::cout << formattedUsage << std::string(8 - formattedUsage.length(), ' ');
}

int main() {
    drawHeader();
    drawProcesses();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD originalCursorPosition = getCursorPosition();

    updateProcessInfo(0,"1234567", "abcdef", R"(E:\games\Phoenix Wright- Ace Attorney Trilogy\Content)", "123456789");

    SetConsoleCursorPosition(hConsole, originalCursorPosition);
    std::cout << "\nPress Enter to exit...";
    std::cin.get();
    return 0;
}
