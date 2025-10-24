#include <iostream>
#include "SystemManager.h"
#include "UiManager.h"

int main() {
    SystemManager manager;
    UiManager Ui;
    Ui.greeting();

    while (Ui.isRunning) {
        Ui.menu(manager);
    }
    return 0;
}
