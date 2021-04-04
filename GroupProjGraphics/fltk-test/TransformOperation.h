#include <string>
#include <iostream>

using namespace std;

class TransformOperation {
    private:
        double x_axis_offset;
        double y_axis_offset;
        double z_axis_offset;

    public:
        string transformName;

        void setOffsets(double x, double y, double z)
        {
            x_axis_offset = x;
            y_axis_offset = y;
            z_axis_offset = z;
        }

        void doTransformation()
        {
            cout << "do something" << endl;
        }
};