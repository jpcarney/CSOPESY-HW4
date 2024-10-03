#include <iostream>

void drawHeader() {
    std::cout << "+-----------------------------------------------------------------------------------------+\n";
    std::cout << "| NVIDIA-SMI 565.90                 Driver Version: 565.90         CUDA Version: 12.7     |\n";
    std::cout << "|-----------------------------------------+------------------------+----------------------+\n";
    std::cout << "| GPU  Name                  Driver-Model | Bus-Id          Disp.A | Volatile Uncorr. ECC |\n";
    std::cout << "| Fan  Temp   Perf          Pwr:Usage/Cap |           Memory-Usage | GPU-Util  Compute M. |\n";
    std::cout << "|                                         |                        |               MIG M. |\n";
    std::cout << "|=========================================+========================+======================|\n";
    std::cout << "|   0  NVIDIA GeForce RTX 3060 ...  WDDM  |   00000000:01:00.0  On |                  N/A |\n";
    std::cout << "| N/A   47C    P0             26W /  130W |    1329MiB /   6144MiB |      0%      Default |\n";
    std::cout << "|                                         |                        |                  N/A |\n";
    std::cout << "+-----------------------------------------+------------------------+----------------------+\n";

    std::cout << "Press Enter to exit...";
    std::cin.get();  // Waits for you to press Enter

}

int main() {
    drawHeader();

    return 0;
}
