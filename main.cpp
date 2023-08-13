#include <iostream>
#include <fstream>
#include <vector>
#include<string>
#include<algorithm>
#include<cstring>
using namespace std;

struct Header{
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
    struct Pixel{
        unsigned char blueData;
        unsigned char greenData;
        unsigned char redData;
    };
    vector<Pixel> pixels;
};

bool compare(Header &example, Header &output) {
    bool test = true;
    if(example.idLength != output.idLength){
        cout << "idLength does not match" << endl;
        test = false;
    }
    if(example.colorMapType != output.colorMapType){
        cout << "colorMapType does not match" << endl;
        test = false;
    }
    if(example.dataTypeCode != output.dataTypeCode){
        cout << "dataTypeCode does not match" << endl;
        test = false;
    }
    if(example.colorMapOrigin != output.colorMapOrigin){
        cout << "colorMapOrigin does not match" << endl;
        test = false;
    }
    if(example.colorMapLength != output.colorMapLength){
        cout << "colorMapLength does not match" << endl;
        test = false;
    }
    if(example.colorMapDepth != output.colorMapDepth){
        cout << "colorMapDepth does not match" << endl;
        test = false;
    }if(example.xOrigin != output.xOrigin){
        cout << "xOrigin does not match" << endl;
        test = false;
    }
    if(example.yOrigin != output.yOrigin){
        cout << "yOrigin does not match" << endl;
        test = false;
    }
    if(example.width != output.width){
        cout << "width does not match" << endl;
        test = false;
    }
    if(example.height != output.height){
        cout << "height does not match" << endl;
        test = false;
    }
    if(example.bitsPerPixel != output.bitsPerPixel){
        cout << "bitsPerPixel does not match" << endl;
        test = false;
    }
    if(example.imageDescriptor != output.imageDescriptor){
        cout << "imageDescriptor does not match" << endl;
        test = false;
    }
    for (int i = 0; i < output.pixels.size(); ++i) {
        if (example.pixels[i].blueData != output.pixels[i].blueData){
            cout << "Blue pixel " << i << " does not match" << endl;
            test = false;
        }
        if (example.pixels[i].greenData != output.pixels[i].greenData){
            cout << "Green pixel " << i << " does not match" << endl;
            test = false;
        }
        if (example.pixels[i].redData != output.pixels[i].redData){
            cout << "Red pixel " << i << " does not match" << endl;
            test = false;
        }
    }
    return test;
}

void print(Header header){
    cout << "ID Length: " << (int)(header.idLength) << endl;
    cout << "Color Map Type: " << (int)(header.colorMapType)<< endl;
    cout << "Data Type Code: " << (int)(header.dataTypeCode) << endl;
    cout << "Color Map Origin: " << header.colorMapOrigin << endl;
    cout << "Color Map Length: " << header.colorMapLength << endl;
    cout << "Color Map Depth: " << (int)(header.colorMapDepth) << endl;
    cout << "X Origin: " << header.xOrigin << endl;
    cout << "Y Origin: " << header.yOrigin << endl;
    cout << "Width: " << header.width << endl;
    cout << "Height: " << header.height << endl;
    cout << "Bits Per Pixel: " << (int)(header.bitsPerPixel) << endl;
    cout << "Image Descriptor: " << (int)(header.imageDescriptor) << endl;
    cout << "Number of Pixels: " << header.pixels.size() << endl;
//    for (int i = 0; i < header.pixels.size(); ++i) {
//        cout << "Pixel: " << i << endl;
//        cout << "Blue: " << (int)header.pixels[i].blueData << " | ";
//        cout << "Green: " << (int)header.pixels[i].greenData << " | ";
//        cout << "Red: " << (int)header.pixels[i].redData << endl;
//    }
}

Header readHeader(string fileName){
    Header headerObject;
    ifstream file(fileName, ios_base::binary);

//    if (file.is_open())
//        cout << fileName << " is open" << endl;

    file.read(&headerObject.idLength, sizeof(headerObject.idLength));
    file.read(&headerObject.colorMapType, sizeof(headerObject.colorMapType));
    file.read(&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
    file.read((char*)(&headerObject.colorMapOrigin), sizeof(headerObject.colorMapOrigin));
    file.read((char*)(&headerObject.colorMapLength), sizeof(headerObject.colorMapLength));
    file.read((char*)(&headerObject.colorMapDepth), sizeof(headerObject.colorMapDepth));
    file.read((char*)(&headerObject.xOrigin), sizeof(headerObject.xOrigin));
    file.read((char*)(&headerObject.yOrigin), sizeof(headerObject.yOrigin));
    file.read((char*)(&headerObject.width), sizeof(headerObject.width));
    file.read((char*)(&headerObject.height), sizeof(headerObject.height));
    file.read((char*)(&headerObject.bitsPerPixel), sizeof(headerObject.bitsPerPixel));
    file.read((char*)(&headerObject.imageDescriptor), sizeof(headerObject.imageDescriptor));

    for (int i = 0; i < (headerObject.height * headerObject.width); ++i) {
        Header::Pixel temp;
        file.read((char*)(&temp.blueData), sizeof(temp.blueData));
        file.read((char*)(&temp.greenData), sizeof(temp.greenData));
        file.read((char*)(&temp.redData), sizeof(temp.redData));
        headerObject.pixels.push_back(temp);
    }
    //cout << fileName << " " << headerObject.pixels.size() << endl;
    file.close();
    return headerObject;
}

void writeHeader(string fileName, Header header) {
    ofstream file(fileName, ios_base::binary);

    if(file.is_open()){
        file.write((char*)(&header.idLength), 1);
        file.write((char*)(&header.colorMapType), 1);
        file.write((char*)(&header.dataTypeCode), 1);
        file.write((char*)(&header.colorMapOrigin), 2);
        file.write((char*)(&header.colorMapLength), 2);
        file.write((char*)(&header.colorMapDepth), 1);
        file.write((char*)(&header.xOrigin), 2);
        file.write((char*)(&header.yOrigin), 2);
        file.write((char*)(&header.width), 2);
        file.write((char*)(&header.height), 2);
        file.write((char*)(&header.bitsPerPixel), 1);
        file.write((char*)(&header.imageDescriptor), 1);
        for (int i = 0; i < header.pixels.size(); ++i) {
            file.write((char*)(&header.pixels[i].blueData), 1);
            file.write((char*)(&header.pixels[i].greenData), 1);
            file.write((char*)(&header.pixels[i].redData), 1);
        }
    }
}

void multiply(Header &top, Header &bottom){
    //cout << top.pixels.size() << endl;
    for (int i = 0; i < top.pixels.size(); ++i) {
        unsigned char multBlue = (char)(((((float)(top.pixels[i].blueData) / 255) * ((float)(bottom.pixels[i].blueData)) / 255) * 255) + 0.5f);
        top.pixels[i].blueData = multBlue;
        unsigned char multGreen = (char)(((((float)(top.pixels[i].greenData) / 255) * ((float)(bottom.pixels[i].greenData)) / 255) * 255) + 0.5f);
        top.pixels[i].greenData = multGreen;
        unsigned char multRed = (char)(((((float)(top.pixels[i].redData) / 255) * ((float)(bottom.pixels[i].redData)) / 255) * 255) + 0.5f);
        top.pixels[i].redData = multRed;
        }
}

void multiplyColor(Header &layer, float valueMult, string color) {
    if (color == "R") {
        for (int i = 0; i < layer.pixels.size(); ++i) {
            float multRed = layer.pixels[i].redData * valueMult;
            if (multRed > 255) {
                layer.pixels[i].redData = 255;
            } else {
                layer.pixels[i].redData = multRed;
            }
        }
    } else if (color == "G") {
        for (int i = 0; i < layer.pixels.size(); ++i) {
            float multGreen = layer.pixels[i].greenData * valueMult;
            if (multGreen > 255) {
                layer.pixels[i].greenData = 255;
            } else {
                layer.pixels[i].greenData = multGreen;
            }
        }
    } else if (color == "B") {
        for (int i = 0; i < layer.pixels.size(); ++i) {
            float multBlue = layer.pixels[i].blueData * valueMult;
            if (multBlue > 255) {
                layer.pixels[i].blueData = 255;
            } else {
                layer.pixels[i].blueData = multBlue;
            }
        }
    }
}

void subtract(Header &top, Header &bottom) {
    for (int i = 0; i < top.pixels.size(); ++i) {
        int topBlue = (int) top.pixels[i].blueData;
        int botBlue = (int) bottom.pixels[i].blueData;

        if (topBlue - botBlue < 0) {
            top.pixels[i].blueData = (char) 0;
        } else if (topBlue - botBlue > 255) {
            top.pixels[i].blueData = (char) 255;
        } else {
            top.pixels[i].blueData = (char) (topBlue - botBlue);
        }

        int topGreen = (int) top.pixels[i].greenData;
        int botGreen = (int) bottom.pixels[i].greenData;

        if (topGreen - botGreen < 0) {
            top.pixels[i].greenData = (char) 0;
        } else if (topGreen - botGreen > 255) {
            top.pixels[i].greenData = (char) 255;
        } else {
            top.pixels[i].greenData = (char) (topGreen - botGreen);
        }
        int topRed = (int) top.pixels[i].redData;
        int botRed = (int) bottom.pixels[i].redData;

        if (topRed - botRed < 0) {
            top.pixels[i].redData = (char) 0;
        } else if (topBlue - botRed > 255) {
            top.pixels[i].redData = (char) 255;
        } else {
            top.pixels[i].redData = (char) (topRed - botRed);
        }
    }
}

void addition(Header &top, Header &bottom) {
    for (int i = 0; i < top.pixels.size(); ++i) {
        int topBlue = (int) top.pixels[i].blueData;
        int botBlue = (int) bottom.pixels[i].blueData;

        if (topBlue + botBlue < 0) {
            top.pixels[i].blueData = (char) 0;
        } else if (topBlue + botBlue > 255) {
            top.pixels[i].blueData = (char) 255;
        } else {
            top.pixels[i].blueData = (char) (topBlue + botBlue);
        }

        int topGreen = (int) top.pixels[i].greenData;
        int botGreen = (int) bottom.pixels[i].greenData;

        if (topGreen + botGreen < 0) {
            top.pixels[i].greenData = (char) 0;
        } else if (topGreen + botGreen > 255) {
            top.pixels[i].greenData = (char) 255;
        } else {
            top.pixels[i].greenData = (char) (topGreen + botGreen);
        }
        int topRed = (int) top.pixels[i].redData;
        int botRed = (int) bottom.pixels[i].redData;

        if (topRed + botRed < 0) {
            top.pixels[i].redData = (char) 0;
        } else if (topBlue + botRed > 255) {
            top.pixels[i].redData = (char) 255;
        } else {
            top.pixels[i].redData = (char) (topRed + botRed);
        }
    }
}

void additionColor(Header &layer, int valueAdd, string color) {
    if (color == "R") {
        for (int i = 0; i < layer.pixels.size(); ++i) {
            int layerGreen = (int)(layer.pixels[i].redData);
            if (layerGreen + valueAdd < 0) {
                layer.pixels[i].redData= (char) 0;
            } else if (layerGreen + valueAdd > 255) {
                layer.pixels[i].redData = (char) 255;
            } else {
                layer.pixels[i].redData = (char)(layerGreen + valueAdd);
            }
        }
    } else if (color == "G") {
        for (int i = 0; i < layer.pixels.size(); ++i) {
            int layerGreen = (int)(layer.pixels[i].greenData);
            if (layerGreen + valueAdd < 0) {
                layer.pixels[i].greenData = (char) 0;
            } else if (layerGreen + valueAdd > 255) {
                layer.pixels[i].greenData = (char) 255;
            } else {
                layer.pixels[i].greenData = (char)(layerGreen + valueAdd);
            }
        }
    } else if (color == "B") {
        for (int i = 0; i < layer.pixels.size(); ++i) {
            int layerGreen = (int)(layer.pixels[i].blueData);
            if (layerGreen + valueAdd < 0) {
                layer.pixels[i].blueData = (char) 0;
            } else if (layerGreen + valueAdd > 255) {
                layer.pixels[i].blueData = (char) 255;
            } else {
                layer.pixels[i].blueData = (char)(layerGreen + valueAdd);
            }
        }
    }
}

void screen(Header &top, Header &bottom) {
    for (int i = 0; i < top.pixels.size(); ++i) {
        float topBlue = ((float) (top.pixels[i].blueData) / 255);
        float botBlue = ((float) (bottom.pixels[i].blueData) / 255);
        top.pixels[i].blueData = (unsigned char)((1 - ((1 - (float)(topBlue)) * (1 - (float)(botBlue)))) * 255 +0.5f);

        float topGreen = ((float) (top.pixels[i].greenData) / 255);
        float botGreen = ((float) (bottom.pixels[i].greenData) / 255);
        top.pixels[i].greenData = (unsigned char)((1 - ((1 - (float)(topGreen)) * (1 - (float)(botGreen)))) * 255 +0.5f);

        float topRed = ((float) (top.pixels[i].redData) / 255);
        float botRed = ((float) (bottom.pixels[i].redData) / 255);
        top.pixels[i].redData = (unsigned char)((1 - ((1 - (float)(topRed)) * (1 - (float)(botRed)))) * 255 +0.5f);
    }
}

void overlay(Header &top, Header &bottom){
    for (int i = 0; i < top.pixels.size(); ++i) {
        float topBlue = ((float) (top.pixels[i].blueData) / 255);
        float botBlue = ((float) (bottom.pixels[i].blueData) / 255);

        // cout << botBlue << endl;

        if (botBlue <= 0.5){
            top.pixels[i].blueData = (unsigned char)(2 * topBlue * botBlue * 255 + 0.5f);
        }else{
            top.pixels[i].blueData = (unsigned char)((1 - (2 * (1 - topBlue) * (1 - botBlue))) * 255 + 0.5f);
        }

        float topGreen = ((float) (top.pixels[i].greenData) / 255);
        float botGreen = ((float) (bottom.pixels[i].greenData) / 255);
        if (botGreen <= 0.5){
            top.pixels[i].greenData = (unsigned char)(2 * topGreen * botGreen * 255 + 0.5f);
        }else{
            top.pixels[i].greenData = (unsigned char)((1 - (2 * (1 - topGreen) * (1 - botGreen))) * 255 + 0.5f);
        }

        float topRed = ((float) (top.pixels[i].redData) / 255);
        float botRed = ((float) (bottom.pixels[i].redData) / 255);
        if (botRed <= 0.5){
            top.pixels[i].redData = (unsigned char)(2 * topRed * botRed * 255 + 0.5f);
        }else{
            top.pixels[i].redData = (unsigned char)((1 - (2 * (1 - topRed) * (1 - botRed))) * 255 + 0.5f);
        }
    }
}

void separateColors(Header &layer, string color){
    if (color == "R"){
        for (int i = 0; i < layer.pixels.size(); ++i) {
            layer.pixels[i].blueData= layer.pixels[i].redData;
            layer.pixels[i].greenData = layer.pixels[i].redData;
            layer.pixels[i].redData = layer.pixels[i].redData;
        }
    } else if (color == "G"){
        for (int i = 0; i < layer.pixels.size(); ++i) {
            layer.pixels[i].blueData= layer.pixels[i].greenData;
            layer.pixels[i].greenData = layer.pixels[i].greenData;
            layer.pixels[i].redData = layer.pixels[i].greenData;
        }
    } else if (color == "B"){
        for (int i = 0; i < layer.pixels.size(); ++i) {
            layer.pixels[i].blueData= layer.pixels[i].blueData;
            layer.pixels[i].greenData = layer.pixels[i].blueData;
            layer.pixels[i].redData = layer.pixels[i].blueData;
        }
    }
}

void combineColors(Header& red, Header& green, Header& blue){
    for (int i = 0; i < red.pixels.size(); ++i) {
        red.pixels[i].blueData = blue.pixels[i].blueData;
        red.pixels[i].greenData = green.pixels[i].greenData;
        red.pixels[i].redData = red.pixels[i].redData;
    }
}

void rotate(Header& image) {
    vector<Header::Pixel> reversePixels;
    for (int i = image.pixels.size()-1; i >= 0; i--) {
        reversePixels.push_back(image.pixels[i]);
    }
    for (int i = 0; i < reversePixels.size(); ++i) {
        image.pixels[i].blueData = reversePixels[i].blueData;
        image.pixels[i].greenData = reversePixels[i].greenData;
        image.pixels[i].redData = reversePixels[i].redData;
    }
}

int main(int argc, char* argv[]) {
//    cout << "Argc: " << argc << endl;
//    for (int i = 0; i < argc; ++i) {
//        cout << "Argv: " << i << " " << argv[i] << endl;
//    }

    // Initial Conditions
    if (argc < 2 or strcmp(argv[1], "--help") == 0) {
        cout << "Project 2: Image Processing, Spring 2023\n\nUsage:\n\t./project2.out [output] [firstImage] [method] [...]" << endl;
        return 0;
    }
    if (argc < 2 or (((string) argv[1]).find(".tga")) == -1) {
        cout << "Invalid file name." << endl;
        return 1;
    }
    if (argc < 3 or (((string) argv[2]).find(".tga")) == -1) {
        cout << "Invalid file name." << endl;
        return 2;
    }

    ifstream testFile;
    testFile.open((string)argv[2], ios_base::binary);
    if (!testFile) {
        cout << "File does not exist." << endl;
        return 3;
    }

    // Methods
    int argIndex = 3;
    Header track = readHeader((string) argv[2]);
    while (argc > argIndex) {
        vector<string> methods = {"combine", "screen", "multiply", "subtract", "overlay",
                                  "addred", "addgreen", "addblue", "scalered", "scalegreen",
                                  "scaleblue", "onlyred", "onlygreen", "onlyblue", "flip"};

        if (argc < 4 or (find(methods.begin(), methods.end(), argv[argIndex]) == methods.end())) {
            cout << "Invalid method name." << endl;
            return 4;
        }

        string twoImages = "combine";
        vector<string> oneImage = {"screen", "multiply", "subtract", "overlay"};
        vector<string> oneNumber = {"addred", "addgreen", "addblue", "scalered", "scalegreen",
                                    "scaleblue"};
        vector<string> noArg = {"onlyred", "onlygreen", "onlyblue", "flip"};

//        cout << argIndex << ": " << argv[argIndex] << endl;
//        cout << argIndex + 1 << ": " << argv[argIndex + 1] << endl;
//        cout << argIndex + 2 << ": " << argv[argIndex + 2] << endl;

        if (strcmp(argv[argIndex], "combine") == 0) { // Combine
            if (argc < 6) {
                cout << "Missing argument." << endl;
                return 2;
            } else if ((((string) argv[argIndex + 1]).find(".tga")) == -1) {
                cout << "Invalid argument, invalid file name." << endl;
                return 2;
            } else if ((((string) argv[argIndex + 2]).find(".tga")) == -1) {
                cout << "Invalid argument, invalid file name." << endl;
                return 2;
            } else {
                ifstream testFile;
                testFile.open((string) argv[argIndex + 1], ios_base::binary);
                if (!testFile.is_open()) {
                    cout << "Invalid argument, file does not exist." << endl;
                    return 3;
                } else {
                    ifstream testFile2;
                    testFile2.open((string) argv[argIndex + 2], ios_base::binary);
                    if (!testFile2.is_open()) {
                        cout << "Invalid argument, file does not exist." << endl;
                        return 3;
                    }
                }
            }
            //Header combine1 = readHeader( (string)argv[2]);
            Header combine2 = readHeader((string) argv[argIndex + 1]);
            Header combine3 = readHeader((string) argv[argIndex + 2]);
            cout << "Combining" << endl;
            combineColors(track, combine2, combine3);
            writeHeader(argv[1], track);
            cout << "... and saving output to " << argv[1] << "!" << endl;
            argIndex += 3;
        } else if (find(oneImage.begin(), oneImage.end(), argv[argIndex]) != oneImage.end()) { // Combine
            if (argc < 5) {
                cout << "Missing argument." << endl;
                return 2;
            } else if ((((string) argv[argIndex + 1]).find(".tga")) == -1) {
                cout << "Invalid argument, invalid file name." << endl;
                return 2;
            } else {
                ifstream testFile;
                testFile.open((string) argv[argIndex + 1], ios_base::binary);
                if (!testFile.is_open()) {
                    cout << "Invalid argument, file does not exist." << endl;
                    return 3;
                }
            }
            if (strcmp(argv[argIndex], "screen") == 0) {
                Header screenVar = readHeader((string) argv[argIndex + 1]);
                cout << "Screening" << endl;
                screen(track, screenVar);
                writeHeader(argv[1], track);
                cout << "... and saving output to " << argv[1] << "!" << endl;
                argIndex += 2;
            } else if (strcmp(argv[argIndex], "multiply") == 0) {
                Header multVar = readHeader((string) argv[argIndex + 1]);
                cout << "Multiplying" << endl;
                multiply(track, multVar);
                writeHeader(argv[1], track);
                cout << "... and saving output to " << argv[1] << "!" << endl;
                argIndex += 2;
            } else if (strcmp(argv[argIndex], "subtract") == 0) {
                Header subtractVar = readHeader((string) argv[argIndex + 1]);
                cout << "Subtracting" << endl;
                subtract(track, subtractVar);
                writeHeader(argv[1], track);
                cout << "... and saving output to " << argv[1] << "!" << endl;
                argIndex += 2;
            } else if (strcmp(argv[argIndex], "overlay") == 0) {
                Header overlayVar = readHeader((string) argv[argIndex + 1]);
                cout << "Overlaying" << endl;
                overlay(track, overlayVar);
                writeHeader(argv[1], track);
                cout << "... and saving output to " << argv[1] << "!" << endl;
                argIndex += 2;
            }
        } else if (find(oneNumber.begin(), oneNumber.end(), argv[argIndex]) != oneNumber.end()) { // Combine
            if (argc < 5 or (argc-argIndex < 2)) {
                cout << "Missing argument." << endl;
                return 2;
            } else {
                try {
                    int num = stoi(argv[argIndex + 1]);
                } catch (invalid_argument) {
                    cout << "Invalid argument, expected number." << endl;
                    return 2;
                }
            }
            if (strcmp(argv[argIndex], "addred") == 0) {
                int addVal = stoi(argv[argIndex + 1]);
                cout << "Adding to Red" << endl;
                additionColor(track, addVal, "R");
                writeHeader(argv[1], track);
                cout << "... and saving output to " << argv[1] << "!" << endl;
                argIndex += 2;
            } else if (strcmp(argv[argIndex], "addgreen") == 0) {
                int addVal = stoi(argv[argIndex + 1]);
                cout << "Adding to Green" << endl;
                additionColor(track, addVal, "G");
                writeHeader(argv[1], track);
                cout << "... and saving output to " << argv[1] << "!" << endl;
                argIndex += 2;
            } else if (strcmp(argv[argIndex], "addblue") == 0) {
                int addVal = stoi(argv[argIndex + 1]);
                cout << "Adding to Blue" << endl;
                additionColor(track, addVal, "B");
                writeHeader(argv[1], track);
                cout << "... and saving output to " << argv[1] << "!" << endl;
                argIndex += 2;
            } else if (strcmp(argv[argIndex], "scalered") == 0) {
                float scaleVal = stof(argv[argIndex + 1]);
                cout << "Scaling Red by " << scaleVal << endl;
                multiplyColor(track, scaleVal, "R");
                writeHeader(argv[1], track);
                cout << "... and saving output to " << argv[1] << "!" << endl;
                argIndex += 2;
            } else if (strcmp(argv[argIndex], "scalegreen") == 0) {
                float scaleVal = stof(argv[argIndex + 1]);
                cout << "Scaling Green" << endl;
                multiplyColor(track, scaleVal, "G");
                writeHeader(argv[1], track);
                cout << "... and saving output to " << argv[1] << "!" << endl;
                argIndex += 2;
            } else if (strcmp(argv[argIndex], "scaleblue") == 0) {
                float scaleVal = stof(argv[argIndex + 1]);
                cout << "Scaling Blue by " << scaleVal << endl;
                multiplyColor(track, scaleVal, "B");
                writeHeader(argv[1], track);
                cout << "... and saving output to " << argv[1] << "!" << endl;
                argIndex += 2;
            }
        } else if (find(noArg.begin(), noArg.end(), argv[argIndex]) != noArg.end()) { // Combine
            if (strcmp(argv[argIndex], "onlyred") == 0) {
                cout << "Separating Red" << endl;
                separateColors(track, "R");
                writeHeader(argv[1], track);
                cout << "... and saving output to " << argv[1] << "!" << endl;
                argIndex += 1;
            } else if (strcmp(argv[argIndex], "onlygreen") == 0) {
                cout << "Separating Green" << endl;
                separateColors(track, "G");
                writeHeader(argv[1], track);
                cout << "... and saving output to " << argv[1] << "!" << endl;
                argIndex += 1;
            } else if (strcmp(argv[argIndex], "onlyblue") == 0) {
                cout << "Separating Blue" << endl;
                separateColors(track, "B");
                writeHeader(argv[1], track);
                cout << "... and saving output to " << argv[1] << "!" << endl;
                argIndex += 1;
            } else if (strcmp(argv[argIndex], "flip") == 0) {
                cout << "Flipping" << endl;
                rotate(track);
                writeHeader(argv[1], track);
                cout << "... and saving output to " << argv[1] << "!" << endl;
                argIndex += 1;
            }
        }
    }


        // Import inputs
        Header car = readHeader("input/car.tga");
        Header circles = readHeader("input/circles.tga");
        Header layer1 = readHeader("input/layer1.tga");
        Header layer2 = readHeader("input/layer2.tga");
        Header layer_blue = readHeader("input/layer_blue.tga");
        Header layer_green = readHeader("input/layer_green.tga");
        Header layer_red = readHeader("input/layer_red.tga");
        Header pattern1 = readHeader("input/pattern1.tga");
        Header pattern2 = readHeader("input/pattern2.tga");
        Header text = readHeader("input/text.tga");
        Header text2 = readHeader("input/text2.tga");

        // Import examples
        Header part1 = readHeader("examples/EXAMPLE_part1.tga");
        Header part2 = readHeader("examples/EXAMPLE_part2.tga");
        Header part3 = readHeader("examples/EXAMPLE_part3.tga");
        Header part4 = readHeader("examples/EXAMPLE_part4.tga");
        Header part5 = readHeader("examples/EXAMPLE_part5.tga");
        Header part6 = readHeader("examples/EXAMPLE_part6.tga");
        Header part7 = readHeader("examples/EXAMPLE_part7.tga");
        Header part8r = readHeader("examples/EXAMPLE_part8_r.tga");
        Header part8g = readHeader("examples/EXAMPLE_part8_g.tga");
        Header part8b = readHeader("examples/EXAMPLE_part8_b.tga");
        Header part9 = readHeader("examples/EXAMPLE_part9.tga");
        Header part10 = readHeader("examples/EXAMPLE_part10.tga");

//    // Part 1
//    cout << "Part 1" << endl;
//    multiply(layer1, pattern1);
//    cout << "Multiplied" << endl;
//    writeHeader("output/part1.tga", layer1);
//    cout << "Output: part1.tga" << endl;
//        // Compare
//        Header output1 = readHeader("output/part1.tga");
//        if(compare(part1, output1)){
//            cout << "Part 1: Files match" << endl;
//        }else{
//            cout << "Part 1: Files do not match" << endl;
//        }
//
//    // Part 2
//    cout << "\nPart 2" << endl;
//    subtract(car, layer2);
//    cout << "Subtracted" << endl;
//    writeHeader("output/part2.tga", car);
//    cout << "Output: part2.tga" << endl;
//        // Compare
//        Header output2 = readHeader("output/part2.tga");
//        if(compare(part2, output2)){
//            cout << "Part 2: Files match" << endl;
//        }else{
//            cout << "Part 2: Files do not match" << endl;
//        }
//
//    // Part 3
//    layer1 = readHeader("input/layer1.tga"); // reset image
//    cout << "\nPart 3" << endl;
//    multiply(layer1, pattern2);
//    cout << "Multiplied" << endl;
//    writeHeader("output/part3.tga", layer1);
//
//    screen(text, layer1);
//    cout << "Screened" << endl;
//    writeHeader("output/part3.tga", text);
//    cout << "Output: Part3.tga" << endl;
//          // Compare
//            Header output3 = readHeader("output/part3.tga");
//            if(compare(part3, output3)){
//                cout << "Part 3: Files match" << endl;
//            }else{
//                cout << "Part 3: Files do not match" << endl;
//            }
//
//    // Part 4
//    cout << "\nPart 4" << endl;
//    multiply(layer2, circles);
//    cout << "Multiplied" << endl;
//    subtract(layer2, pattern2);
//    cout << "Subtracted" << endl;
//    writeHeader("output/part4.tga", layer2);
//    cout << "Output: Part4.tga" << endl;
//    // Compare
//    Header output4 = readHeader("output/part4.tga");
//    if(compare(part4, output4)){
//        cout << "Part 4: Files match" << endl;
//    }else{
//        cout << "Part 4: Files do not match" << endl;
//    }
//
//    // Part 5
//    layer1 = readHeader("input/layer1.tga");
//    pattern1 = readHeader("input/pattern1.tga");
//    cout << "\nPart 5" << endl;
//    overlay(layer1, pattern1);
//    cout << "Overlayed Layer1 and Pattern1" << endl;
//    writeHeader("output/part5.tga", layer1);
//    cout << "Output: part5.tga" << endl;
//        // Compare
//        Header output5 = readHeader("output/part5.tga");
//        if(compare(part5, output5)){
//            cout << "Part 5: Files match" << endl;
//        }else{
//            cout << "Part 5: Files do not match" << endl;
//        }
//
//    // Part 6
//    car = readHeader("input/car.tga"); // reset car file after Part 2
//    cout << "\nPart 6" << endl;
//    additionColor(car, 200, "G");
//    cout << "Added 200 to Green" << endl;
//    writeHeader("output/part6.tga", car);
//    cout << "Output: part6.tga" << endl;
//    // Compare
//        Header output6 = readHeader("output/part6.tga");
//        if(compare(part6, output6)){
//            cout << "Part 6: Files match" << endl;
//        }else{
//            cout << "Part 6: Files do not match" << endl;
//        }
//
//    // Part 7
//    car = readHeader("input/car.tga"); // reset car file after Part 6
//    cout << "\nPart 7" << endl;
//    multiplyColor(car, 4, "R");
//    cout << "Multiplied Red by 4" << endl;
//    multiplyColor(car, 0, "B");
//    cout << "Multiplied Blue by 0" << endl;
//    writeHeader("output/part7.tga", car);
//    cout << "Output: part7.tga" << endl;
//        // Compare
//        Header output7 = readHeader("output/part7.tga");
//        if(compare(part7, output7)){
//            cout << "Part 7: Files match" << endl;
//        }else{
//            cout << "Part 7: Files do not match" << endl;
//        }
//
//    // Part 8
//    cout << "\nPart 8" << endl;
//    car = readHeader("input/car.tga"); // reset car file after Part 7
//    separateColors(car, "R");
//    writeHeader("output/part8_r.tga", car);
//    cout << "Output car.tga with red channel" << endl;
//        // Compare Red
//        Header output8r = readHeader("output/part8_r.tga");
//        if(compare(part8r, output8r)){
//            cout << "Part 8 Red: Files match" << endl;
//        }else{
//            cout << "Part 8 Red: Files do not match" << endl;
//        }
//
//    car = readHeader("input/car.tga"); // reset car file after Part 7
//    separateColors(car, "B");
//    writeHeader("output/part8_b.tga", car);
//    cout << "Output car.tga with blue channel" << endl;
//        // Compare Blue
//            Header output8b = readHeader("output/part8_b.tga");
//            if(compare(part8b, output8b)){
//                cout << "Part 8 Blue: Files match" << endl;
//            }else{
//                cout << "Part 8 Blue: Files do not match" << endl;
//            }
//
//    car = readHeader("input/car.tga"); // reset car file after Part 7
//    separateColors(car, "G");
//    writeHeader("output/part8_g.tga", car);
//    cout << "Output car.tga with green channel" << endl;
//        // Compare Green
//        Header output8g = readHeader("output/part8_g.tga");
//        if(compare(part8g, output8g)){
//            cout << "Part 8 Green: Files match" << endl;
//        }else{
//            cout << "Part 8 Green: Files do not match" << endl;
//        }
//
//    // Task 9
//    cout << "\nPart 9" << endl;
//    combineColors(layer_red, layer_green, layer_blue);
//    cout << "Combined colors" << endl;
//    writeHeader("output/part9.tga", layer_red);
//    cout << "Output layer_red.tga with colors from other files" << endl;
//        // Compare
//        Header output9 = readHeader("output/part9.tga");
//        if(compare(part9, output9)){
//            cout << "Part 9: Files match" << endl;
//        }else{
//            cout << "Part 9: Files do not match" << endl;
//        }
//
//    // Task 10
//    cout << "\nPart 10" << endl;
//    rotate(text2);
//    cout << "Rotated text2.tga" << endl;
//    writeHeader("output/part10.tga", text2);
//    cout << "Output rotated text2.tga" << endl;
//        // Compare
//        Header output10 = readHeader("output/part10.tga");
//        if(compare(part10, output10)){
//            cout << "Part 10: Files match" << endl;
//        }else{
//            cout << "Part 10: Files do not match" << endl;
//        }

        return 0;

}