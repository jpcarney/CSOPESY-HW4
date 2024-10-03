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

void updateGpuMemoryUsage(int processIndex, const std::string& newUsage) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (newUsage.length() > 5) {
        throw std::runtime_error("Error: GPU memory usage exceeds maximum length of 5 characters.");
    }

    COORD coord = { 81, static_cast<SHORT>(17 + processIndex) };  // change y value based on the line number
    SetConsoleCursorPosition(hConsole, coord);
    std::string truncatedUsage = newUsage.substr(0, 5); // Take up to 5 characters
    std::string formattedUsage = truncatedUsage + "MiB";
    std::cout << formattedUsage << std::string(8 - formattedUsage.length(), ' ');
}


int main() {
    drawHeader();
    drawProcesses();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD originalCursorPosition = getCursorPosition();

    try { // catches errors that would cause layout issues
        updateGpuMemoryUsage(0, "12345");
    } catch (const std::runtime_error& e) {
        system("cls");
        std::cerr << e.what() << std::endl; // Print the error message to the console
        std::cout << "\nPress Enter to exit...";
        std::cin.get();
        return 0;
    }

    SetConsoleCursorPosition(hConsole, originalCursorPosition);
    std::cout << "\nPress Enter to exit...";
    std::cin.get();
    return 0;
}
