#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxGui.h"
//#include "notes.h"

class Circle;
class ofApp : public ofBaseApp{
    
public:
    void setup() override;
    void update() override;
    void draw() override;
    
    void keyPressed(int key) override;
    void keyReleased(int key) override;
    void mouseMoved(int x, int y ) override;
    void mouseDragged(int x, int y, int button) override;
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(int x, int y, int button) override;
    void mouseEntered(int x, int y) override;
    void mouseExited(int x, int y) override;
    void windowResized(int w, int h) override;
    void dragEvent(ofDragInfo dragInfo) override;
    void gotMessage(ofMessage msg) override;
    ofPolyline poly;
    void clearButtonPressed();
    void takeScreenshot();
    int noteQuantity;
    maxiEnv envelope;
    
    ofSoundStream soundStream;
    
    /* ofxMaxi*/
    void audioIn(ofSoundBuffer& input) override; // not used in this example
    void audioOut(ofSoundBuffer& output) override;
    maxiOsc Chord1, Chord2;
    maxiEnv myEnv;
    maxiClock myClock;
    int bufferSize, sampleRate;

    float pianoFreq[108] = {
        16.35, 17.32, 18.35, 19.45, 20.6, 21.83, 23.12, 24.5, 25.96, 27.5, 29.14, 30.87,
        32.7, 34.65, 36.71, 38.89, 41.2, 43.65, 46.25, 49, 51.91, 55, 58.27, 61.74,
        65.41, 69.3, 73.42, 77.78, 82.41, 87.31, 92.5, 98, 103.83, 110, 116.54, 123.47,
        130.81, 138.59, 146.83, 155.56, 164.81, 174.61, 185, 196, 207.65, 220, 233.08, 246.94,
        261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392, 415.3, 440, 466.16, 493.88,
        523.25, 554.37, 587.33, 622.25, 659.26, 698.46, 739.99, 783.99, 830.61, 880, 932.33, 987.77,
        1046.5, 1108.73, 1174.66, 1244.51, 1318.51, 1396.91, 1479.98, 1567.98, 1661.22, 1760, 1864.66, 1975.53,
        2093, 2217.46, 2349.32, 2489.02, 2637.02, 2793.83, 2959.96, 3135.96, 3322.44, 3520, 3729.31, 3951.07,
        4186.01, 4434.92, 4698.63, 4978.03, 5274.04, 5587.65, 5919.91, 6271.93, 6644.88, 7040, 7458.62, 7902.13
    };
    
    float d_scale_frequencies[56] = {
        73.416, 77.782, 82.407, 87.307, 92.499, 97.999, 103.826, // D1 - D2
        110.000, 116.541, 123.471, 130.813, 138.591, 146.832, 155.563, // D2 - D3
        164.814, 174.614, 184.997, 195.998, 207.652, 220.000, 233.082, // D3 - D4
        246.942, 261.626, 277.183, 293.665, 311.127, 329.628, 349.228, // D4 - D5
        369.994, 391.995, 415.305, 440.000, 466.164, 493.883, 523.251, // D5 - D6
        554.365, 587.330, 622.254, 659.255, 698.456, 739.989, 783.991, // D6 - D7
        830.609, 880.000, 932.328, 987.767, 1046.502, 1108.731, 1174.659, // D7 - D8
        1244.508, 1318.510, 1396.913, 1479.978, 1567.982, 1661.219, 1760.000, // D8 - D9
    };
    
    float d_minor_scale_freq[49] = {
        73.42, 77.78, 82.41, 87.31, 92.5, 98, 103.83,
        110, 116.54, 123.47, 130.81, 138.59, 146.83, 155.56,
        164.81, 174.61, 185, 196, 207.65, 220, 233.08,
        246.94, 261.63, 277.18, 293.66, 311.13, 329.63, 349.23,
        369.99, 392, 415.3, 440, 466.16, 493.88, 523.25,
        554.37, 587.33, 622.25, 659.26, 698.46, 739.99, 783.99,
        830.61, 880, 932.33, 987.77, 1046.5, 1108.73, 1174.66,
    };
    
    float d_pentatonic_scale[15] = {
        36.708, 46.249, 55.000, 73.416,
        92.499, 110.000, 146.832, 184.997,
        220.000, 293.665, 369.994, 440.000,
        587.330, 739.989, 880.000
    };
    
    //this is the scale I ended up using
    float d_minor_pentatonic_scale[25] = {
        61.735, 65.406, 73.416, 82.407, 87.307,
        97.999, 110.000, 130.813, 146.832, 164.814,
        174.614, 195.998, 220.000, 261.626, 293.665,
        329.628, 349.228, 391.995, 440.000, 523.251,
        587.330, 659.255, 698.456, 783.991, 880.000
    };
    
    ofxPanel gui;

private:
    //drawing line
    ofPolyline line;
    //holds value of colour which changes over time
    ofColor color = ofColor(0);
    //counter to hold how much time has passed which is used to determine colour
    int startTime = 0;
    bool mouseIsPressed = false;
    int fadeDuration = 5000;
    //vector to hold lines
    vector<ofPolyline> lines;
    vector<ofColor> lineColors;
    //to clear drawing
    ofxButton clearButton;
    bool ignoreFading = false;
    //to take a screenshot
    ofImage screenshot;
    ofxButton screenshotButton;
    //to play a sound when right clicked on mouse 
    bool playRightSound;
};


