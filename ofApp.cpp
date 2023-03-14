#include "ofApp.h"
#include "ofxGui.h"
#include <cstdlib>
using namespace std;

//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------The Visual Theremin-----------------------
//--------------------------------------------------------------
//-----------------Creative Coding 2 2023 ----------------------
//------------------Project by Mae Horak -----------------------
//--------------------------------------------------------------

void ofApp::setup(){
    ofBackground(0);
    //line width to draw
    ofSetLineWidth(3);
    
    sampleRate = 44100;
    bufferSize = 512;
    //ofSoundStreamSetup(2, 0, sampleRate, bufferSize, 4);
    
    int mouseX = ofGetMouseX(); // get the x position of the mouse
    //int number = ofMap(mouseX, 0, ofGetWidth(), 0, 100); // map the x position to a range from 0 to 100

    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    myClock.setTempo(120);
    myClock.setTicksPerBeat(1);
    
    // Setup ofSound
    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
    
    // Initialize envelope parameters
    envelope.setAttack(100); // Attack time in milliseconds
    envelope.setDecay(50); // Decay time in milliseconds
    envelope.setSustain(0.5); // Sustain level (0.0 to 1.0)
    envelope.setRelease(500); // Release time in milliseconds
    
    gui.setup();
    
    //Button to Clear Drawing
    clearButton.setup("Clear Drawing");  // initialize the button object
   // clearButton.setPosition(ofGetWidth() - 200, ofGetHeight() - 50);  // set the position of the button
    clearButton.setPosition(ofGetWidth() * 0.8, ofGetHeight() * 0.9);
    clearButton.addListener(this, &ofApp::clearButtonPressed);  // add a listener for when the button is pressed
    
    
    //button to take a screenshot of drawing
    screenshotButton.setup("Take Screenshot");
    //screenshotButton.setPosition(ofGetWidth() - 400, ofGetHeight() - 50);
    screenshotButton.setPosition(ofGetWidth() * 0.6, ofGetHeight() * 0.9);
    screenshotButton.addListener(this, &ofApp::takeScreenshot);
    
    playRightSound = false;
    noteQuantity = 25;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //-----------------------------------draw lines based on where mouse is held down-----------------------------------
    // Calculate the duration that the mouse has been held down for
    int duration = ofGetElapsedTimeMillis() - startTime;
    
    if (!mouseIsPressed) {
        // If the mouse is not pressed, decrease the alpha value of the color over time
        int elapsedTime = ofGetElapsedTimeMillis() - startTime;
        int alpha = ofMap(elapsedTime, 0, fadeDuration, 255, 0, true);
        color.a = alpha;
    } else {
        // If the mouse is pressed, calculate the color based on the duration that the mouse has been held down for
        int duration = ofGetElapsedTimeMillis() - startTime;
        int maxDuration = 2000;
        int maxHue = 50;
        int hue = ofMap(duration, 0, maxDuration, 0, maxHue);
        color = ofColor::fromHsb(hue, 250, 150);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    int mouseX = ofGetMouseX(); // get the x position of the mouse
    
    // draw the current line if the mouse is pressed
    if (!mouseIsPressed && !ignoreFading) {
        for (int i = 0; i < lines.size(); i++) {
            ofColor fadedColor = lineColors[i];
            fadedColor.a = ofMap(ofGetElapsedTimeMillis() - startTime, 0, fadeDuration, 255, 0, true);
            ofSetColor(fadedColor);
            lines[i].draw();
        }
    }
    else {
        ofSetColor(color);
        line.draw();
        for (int i = 0; i < lines.size(); i++) {
            ofSetColor(lineColors[i]);
            lines[i].draw();
        }
    }
   
    screenshotButton.draw();
    clearButton.draw();  // draw the button on the screen
    gui.draw();
    
    //take a screenshot
    if (screenshotButton) {
        screenshot.draw(0, 0);
    }

}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer& input){
    std::size_t nChannels = input.getNumChannels();
    for (size_t i = 0; i < input.getNumFrames(); i++)
    {

    }

}
//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer& output){

    //play sound based on mouse position
    if (playRightSound == false){
        for (int i = 0; i < bufferSize; i++){
            int number = ofMap(mouseX, 0, ofGetWidth(), 0, noteQuantity);
            //mouse movement controls pitch of oscillator on x axis
            float chord1 = Chord1.sinewave(d_minor_pentatonic_scale[number]);
            float mixedSine = chord1;
            for (int j = 0; j < maxiSettings::channels; j++){
                output[i * maxiSettings::channels + j] = mixedSine;
            }
        }
    }
    else{
        //if mouse is right clicked, add a second note to create harmonics with the first note
        for (int i = 0; i < bufferSize; i++){
            int number = ofMap(mouseX, 0, ofGetWidth(), 0, noteQuantity);
            int number1 = ofMap(mouseY, 0, ofGetWidth(), 0, noteQuantity);
            //mouse movement controls pitch of oscillator
            float chord1 = Chord1.sinewave(d_minor_pentatonic_scale[number]);
            //when you hold down the right mouse key, play another note which is controlled by moving mouse on y axis
            float chord2 = Chord2.sinewave(d_minor_pentatonic_scale[noteQuantity-number1]);
            float mixedSine = (chord1 + chord2)/ 2;
            for (int j = 0; j < maxiSettings::channels; j++){
                output[i * maxiSettings::channels + j] = mixedSine;
            }
        }

    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

    line.addVertex(x, y); // Add each subsequent point to the line

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
  
     line.clear();
     line.addVertex(x, y);
    //counts time elipsed in order to change colour
     startTime = ofGetElapsedTimeMillis();
     mouseIsPressed = true;
    ignoreFading = false;
    
    if(button == OF_MOUSE_BUTTON_RIGHT){
         playRightSound = true;
     }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

    if(button == OF_MOUSE_BUTTON_LEFT){
        //when released, save line that has been drawn
         lines.push_back(line);
         lineColors.push_back(color);
         mouseIsPressed = false;
         ignoreFading = true;
     }
    
    if(button == OF_MOUSE_BUTTON_RIGHT){
         playRightSound = false;
        lines.push_back(line);
        lineColors.push_back(color);
     }

}
//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    clearButton.setPosition(ofGetWidth() * 0.8, ofGetHeight() * 0.9);
    screenshotButton.setPosition(ofGetWidth() * 0.6, ofGetHeight() * 0.9);
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}

void ofApp::clearButtonPressed() {
    lines.clear();  // clear the lines vector
}

void ofApp::takeScreenshot() {
    //when screenshot button is clicked save drawing
    screenshot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    string filename = "theramin_" + ofGetTimestampString() + ".png";
    screenshot.save(filename);
    cout << "Screenshot saved to " << filename << endl;
}
