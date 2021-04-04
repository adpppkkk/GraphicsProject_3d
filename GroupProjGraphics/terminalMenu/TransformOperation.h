#include <string>
#include <iostream>
#include "OpenGLWindow.h"

using namespace std;

class TransformOperation {
    private:
        double x_axis_offset;
        double y_axis_offset;
        double z_axis_offset;

    public:
        string transformName;

        TransformOperation(double x, double y, double z)
        {
            x_axis_offset = x;
            y_axis_offset = y;
            z_axis_offset = z;
        }

        void doTransformation(CubeTransform ct)
        {
            if(transformName == "Translate")
            {
                Translation(ct, x_axis_offset, y_axis_offset, z_axis_offset);
            }
            else if(transformName == "Scale")
            {
                Scaling(ct, x_axis_offset, y_axis_offset, z_axis_offset);
            }
            else if(transformName == "Rotate")
            {
                Rotation(ct, 1, x_axis_offset);
                Rotation(ct, 2, y_axis_offset);
                Rotation(ct, 3, z_axis_offset);
            }
        }

        string toString()
        {
            return transformName + "   (" + to_string(x_axis_offset) + ", " + to_string(y_axis_offset) + ", " + to_string(z_axis_offset) +")";
        }
};