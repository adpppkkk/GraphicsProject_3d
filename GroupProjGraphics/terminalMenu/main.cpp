#include <cstdlib>
#include <iostream>
#include <queue>
#include <string>

#include "TransformOperation.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

void showQueue(queue<TransformOperation> queueParm)
{
    cout << endl;
    queue<TransformOperation> q = queueParm;
    int i = 1;
    while (!q.empty()) {
        TransformOperation transOp = q.front();
        cout << i << ") " << transOp.toString() << endl;
        q.pop();
        i++;
    }
    cout << endl;
}

void doQueue(queue<TransformOperation> queueParm)
{
    cout << endl;
    queue<TransformOperation> q = queueParm;
    while (!q.empty()) {
        TransformOperation transOp = q.front();
        transOp.doTransformation(ct);
        q.pop();
    }
    cout << endl;
}

void removeElementFromQueue(queue<TransformOperation>& queueParm, int index)
{
    queue<TransformOperation> temp;
    int i = 1;
    while (!queueParm.empty()) {
        TransformOperation transOp = queueParm.front();
        queueParm.pop();
        if(i != index)
        {
            cout << "pushing " << transOp.transformName << endl;
            temp.push(transOp);
        }
        else
        {
            cout << "Not pushing " << i << endl;
        }
        i++;
    }
    queueParm = temp;
    cout << endl;
}

void copyArray(double* source, double* destination)
{
    for(int i = 0; i < 4; i++)
    {
        destination[i] = source[i];
    }
}

int main(int argc, char** argv)
{
    if(argc > 1)
    {
        for(int i = 2; i < argc - 2; i += 4)
        {
            double newValues[4] = {stod(argv[i]), stod(argv[i + 1]), stod(argv[i + 2]), stod(argv[i + 3])};
            if(i / 4 == 0)
                copyArray(newValues, ct.topP1);
            else if(i / 4 == 1)
                copyArray(newValues, ct.topP2);
            else if(i / 4 == 2)
                copyArray(newValues, ct.topP3);
            else if(i / 4 == 3)
                copyArray(newValues, ct.topP4);
            else if(i / 4 == 4)
                copyArray(newValues, ct.bottomP1);
            else if(i / 4 == 5)
                copyArray(newValues, ct.bottomP2);
            else if(i / 4 == 6)
                copyArray(newValues, ct.bottomP3);
            else if(i / 4 == 7)
                copyArray(newValues, ct.bottomP4);
            else if(i / 4 == 8)
                copyArray(newValues, ct.frontP1);
            else if(i / 4 == 9)
                copyArray(newValues, ct.frontP2);
            else if(i / 4 == 10)
                copyArray(newValues, ct.frontP3);
            else if(i / 4 == 11)
                copyArray(newValues, ct.frontP4);
            else if(i / 4 == 12)
                copyArray(newValues, ct.backP1);
            else if(i / 4 == 13)
                copyArray(newValues, ct.backP2);
            else if(i / 4 == 14)
                copyArray(newValues, ct.backP3);
            else if(i / 4 == 15)
                copyArray(newValues, ct.backP4);
            else if(i / 4 == 16)
                copyArray(newValues, ct.leftP1);
            else if(i / 4 == 17)
                copyArray(newValues, ct.leftP2);
            else if(i / 4 == 18)
                copyArray(newValues, ct.leftP3);
            else if(i / 4 == 19)
                copyArray(newValues, ct.leftP4);
            else if(i / 4 == 20)
                copyArray(newValues, ct.rightP1);
            else if(i / 4 == 21)
                copyArray(newValues, ct.rightP2);
            else if(i / 4 == 22)
                copyArray(newValues, ct.rightP3);
            else if(i / 4 == 23)
                copyArray(newValues, ct.rightP4);
        }

        cout << endl;

        glutInit(&argc, argv);            // Initialize GLUT
        glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
        glutInitWindowSize(640, 480);   // Set the window's initial width & height
        glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
        glutCreateWindow(title);          // Create window with the given title
        glutDisplayFunc(display);       // Register callback handler for window re-paint event
        glutReshapeFunc(reshape);       // Register callback handler for window re-size event
        initGL();                       // Our own OpenGL initialization
        glutMainLoop();                 // Enter the infinite event-processing loop
    }
    else if(argc == 1)
    {
        setDefault(ct);
        queue<TransformOperation> operations;

        bool showMenu = true;
        while (showMenu)
        {
            string selectedOption = "";

            cout << endl;
            cout << "*****************************************" << endl;
            cout << "* 1) Translate                          *" << endl;
            cout << "* 2) Scale                              *" << endl;
            cout << "* 3) Rotate                             *" << endl;
            cout << "* 4) Show Transformation Queue          *" << endl;
            cout << "* 5) Remove Transformation              *" << endl;
            cout << "* 6) Draw model (resets transformation) *" << endl;
            cout << "* 7) Quit                               *" << endl;
            cout << "*****************************************" << endl;
            cout << "> ";
            cin >> selectedOption;

            double xOffset;
            double yOffset;
            double zOffset;

            if(selectedOption == "1" || selectedOption == "2")
            {
                string x = "";
                string y = "";
                string z = "";

                cout << "X-Axis offset?" << endl;
                cout << "> ";
                cin >> x;
                xOffset = stod(x);

                cout << "Y-Axis offset?" << endl;
                cout << "> ";
                cin >> y;
                yOffset = stod(y);

                cout << "Z-Axis offset?" << endl;
                cout << "> ";
                cin >> z;
                zOffset = stod(z);
            }
            else if(selectedOption == "3")
            {
                string x = "";
                string y = "";
                string z = "";

                cout << "X-Axis Rotation (degrees)?" << endl;
                cout << "> ";
                cin >> x;
                xOffset = stod(x);

                cout << "Y-Axis Rotation (degrees)?" << endl;
                cout << "> ";
                cin >> y;
                yOffset = stod(y);

                cout << "Z-Axis Rotation (degrees)?" << endl;
                cout << "> ";
                cin >> z;
                zOffset = stod(z);
            }

            if(selectedOption == "1")
            {
                TransformOperation operation = TransformOperation(xOffset, yOffset, zOffset);
                operation.transformName = "Translate";
                operations.push(operation);
            }
            else if(selectedOption == "2")
            {
                TransformOperation operation = TransformOperation(xOffset, yOffset, zOffset);
                operation.transformName = "Scale";
                operations.push(operation);
            }
            else if(selectedOption == "3")
            {
                TransformOperation operation = TransformOperation(xOffset, yOffset, zOffset);
                operation.transformName = "Rotate";
                operations.push(operation);
            }
            else if (selectedOption == "4")
            {
                showQueue(operations);
            }
            else if (selectedOption == "5")
            {
                showQueue(operations);
                cout << "Which transformation to remove? (placement)" << endl;
                cout << "> ";
                string removeQueuePlacement = "";
                cin >> removeQueuePlacement;
                removeElementFromQueue(operations, stoi(removeQueuePlacement));
            }
            else if(selectedOption == "6")
            {
                showQueue(operations);
                doQueue(operations);
                cout << "To reset, quit the OpenGL window" << endl;
                string ct_values = ct.toString(false);
                system(("./main.out draw " + ct_values).c_str());
                showMenu = false;
                system("./main.out");
            }
            else if(selectedOption == "7")
            {
                showMenu = false;
                exit(0);
            }
            else
            {
                cout << "Invalid input. Please input either 1, 2, 3, or 4 corresponding to the option you want" << endl << endl << endl;
            }
        }
    }
    return 0;
}