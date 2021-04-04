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
    while (!q.empty()) {
        TransformOperation transOp = q.front();
        cout << transOp.toString() << endl;
        q.pop();
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

int main(int argc, char** argv)
{
    cout << "before reading passed in values " << ct.backP1[2] << endl;
    if(argc > 1)
    {
        for(int i = 2; i < argc - 2; i += 4)
        {
            double newValues[4] = {stod(argv[i]), stod(argv[i + 1]), stod(argv[i + 2]), stod(argv[i + 3])};
            if(i / 4 == 0)
                ct.topP1 = newValues;
            else if(i / 4 == 1)
                ct.topP2 = newValues;
            else if(i / 4 == 2)
                ct.topP3 = newValues;
            else if(i / 4 == 3)
                ct.topP4 = newValues;
            else if(i / 4 == 4)
                ct.bottomP1 = newValues;
            else if(i / 4 == 5)
                ct.bottomP2 = newValues;
            else if(i / 4 == 6)
                ct.bottomP3 = newValues;
            else if(i / 4 == 7)
                ct.bottomP4 = newValues;
            else if(i / 4 == 8)
                ct.frontP1 = newValues;
            else if(i / 4 == 9)
                ct.frontP2 = newValues;
            else if(i / 4 == 10)
                ct.frontP3 = newValues;
            else if(i / 4 == 11)
                ct.frontP4 = newValues;
            else if(i / 4 == 12)
                ct.backP1 = newValues;
            else if(i / 4 == 13)
                ct.backP2 = newValues;
            else if(i / 4 == 14)
                ct.backP3 = newValues;
            else if(i / 4 == 15)
                ct.backP4 = newValues;
            else if(i / 4 == 8)
                ct.leftP1 = newValues;
            else if(i / 4 == 9)
                ct.leftP2 = newValues;
            else if(i / 4 == 10)
                ct.leftP3 = newValues;
            else if(i / 4 == 11)
                ct.leftP4 = newValues;
            else if(i / 4 == 12)
                ct.rightP1 = newValues;
            else if(i / 4 == 13)
                ct.rightP2 = newValues;
            else if(i / 4 == 14)
                ct.rightP3 = newValues;
            else if(i / 4 == 15)
                ct.rightP4 = newValues;
        }

        cout << "after reading in passed in values " << ct.backP1[2] << endl;
        cout << "values in h file after reading passed in values ";
        printCTValue();
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
        cout << "Before setDefault call " << ct.backP1[0] << endl;
        setDefault(ct);
        cout << "After setDefault call " << ct.backP1[0] << endl;
        queue<TransformOperation> operations;

        bool showMenu = true;
        while (showMenu)
        {
            string selectedOption = "";

            cout << endl;
            cout << "********************" << endl;
            cout << "* 1) Translate     *" << endl;
            cout << "* 2) Scale         *" << endl;
            cout << "* 3) Rotate        *" << endl;
            cout << "* 4) Draw model    *" << endl;
            cout << "* 5) Quit          *" << endl;
            cout << "********************" << endl;
            cout << "> ";
            cin >> selectedOption;

            double xOffset;
            double yOffset;
            double zOffset;

            if(selectedOption == "1" || selectedOption == "2" || selectedOption == "3")
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
            else if(selectedOption == "4")
            {
                showQueue(operations);
                doQueue(operations);
                cout << "To reset, quit the OpenGL window" << endl;
                string ct_values = ct.toString();
                system(("./main.out draw " + ct_values).c_str());
                showMenu = false;
                system("./main.out");
            }
            else if(selectedOption == "5")
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