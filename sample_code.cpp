#include <fstream>
#include <iostream>
using namespace std;

class Feature
{
public:
    enum FeatureType {eUnknown, eCircle, eTriangle, eSquare};
    
    Feature() : type(eUnknown), points(0) {}
    
    ~Feature()
    {
        if (points)
            delete points;
    }
    
    bool isValid()
    {
        return type != eUnknown;
    }
    
    bool read(ifstream* file)
    {
        int ft_in;
        
        if( !(*file >> ft_in))
            return false;
        
        short n = 0;
        
        type = static_cast<FeatureType>(ft_in);
        
        switch (type)
        {
            case eCircle: n = 3; break;
            case eTriangle: n = 6; break;
            case eSquare: n = 8; break;
            default: type = eUnknown; return false;
        }
        points = new double[n];
        if (!points)
            return false;

        int i = 0;
        
        while( i < n )
            if( !(*file >> points[i++]))
                return false;
        
        file->ignore(2);
        
        /*if (!(file->eof()))
            cout << "Some input in file being ignored!" << endl;*/
            
        return true;

    }
    void draw()
    {
        switch (type)
        {
            case eCircle: drawCircle(points[0], points[1], points[2]); break;
            case eTriangle: drawPolygon(points, 6); break;
            case eSquare: drawPolygon(points, 8); break;
        }
    }
    
protected:
    void drawCircle(double centerX, double centerY, double radius);
    void drawPolygon(double* points, int size);
    
    double* points;
    FeatureType type;
};

void Feature::drawCircle(double centerX, double centerY, double radius){
    
    cout << "Drawing circle..." << endl;
}

void Feature::drawPolygon(double* points, int size){
    
    cout << "Drawing polygon with " << (size >> 1) << " corners..." << endl;
}

int main(int argc, char* argv[])
{
    Feature feature;
    ifstream file;
    file.open("features.dat");
    if(!file)
        return 1;
    
    bool read_success = feature.read(&file);
    
    if(!feature.isValid()){
        cout << "Unkown type!" << endl;
        return 1;
    }
    
    if (!read_success){
        cout << "Something went wrong while reading input!" << endl;
        return 1;
    }
    
    feature.draw();
    
    return 0;
}
