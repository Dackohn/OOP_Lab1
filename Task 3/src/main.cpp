#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Display {
private:
    int width;
    int height;
    float ppi;
    string model;

public:
    Display(int w, int h, float p, string m) : width(w), height(h), ppi(p), model(m) {}

    void displayInfo() const {
        cout << "Model: " << model << ", Width: " << width << ", Height: " << height
             << ", PPI: " << ppi << endl;
    }

    string getModel() const {
        return model;
    }
};

class Assistant {
private:
    string assistantName;
    vector<Display> assignedDisplays;

public:
    Assistant(string name) : assistantName(name) {}

    void assignDisplay(Display d) {
        assignedDisplays.push_back(d);
        cout << "Assigned display: " << d.getModel() << " to assistant " << assistantName << endl;
    }

    void assist() const {
        cout << "Assistant " << assistantName << " has the following displays:\n";
        for (size_t i = 0; i < assignedDisplays.size(); ++i) {
            cout << i + 1 << ". ";
            assignedDisplays[i].displayInfo();
        }
    }

    void buyDisplay() {
        if (assignedDisplays.empty()) {
            cout << "No displays assigned to buy." << endl;
            return;
        }

        int choice;
        cout << "Enter the number of the display you want to buy: ";
        cin >> choice;

        if (choice < 1 || choice > assignedDisplays.size()) {
            cout << "Invalid choice. Please select a valid display number." << endl;
            return;
        }

        Display chosenDisplay = assignedDisplays[choice - 1];
        cout << "You chose to buy the display: " << chosenDisplay.getModel() << endl;
    }
};

int main() {
    Display display1(1920, 1080, 401.5, "Monitor A");
    Display display2(2560, 1440, 326.0, "Monitor B");
    Display display3(3840, 2160, 530.0, "Monitor C");

    Assistant assistant("Keivin");

    assistant.assignDisplay(display1);
    assistant.assignDisplay(display2);
    assistant.assignDisplay(display3);

    cout << endl;
    assistant.assist();

    cout << endl;
    assistant.buyDisplay();

    return 0;
}
