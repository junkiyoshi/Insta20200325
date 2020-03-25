#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	this->number_of_targets = 65;
	this->shader.load("shader/shader.vert", "shader/shader.frag");
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->location_list.clear();
	this->size_list.clear();

	for (int i = 0; i < this->number_of_targets; i++) {

		auto location = glm::vec4(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, 0, ofGetWidth()), ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, 0, ofGetHeight()), 0, 0);
		this->location_list.push_back(location);
		this->size_list.push_back(0.1);
	}

	for (int i = 0; i < this->number_of_targets; i++) {

		for (int k = i + 1; k < this->number_of_targets; k++) {

			auto distance = glm::distance(this->location_list[i], this->location_list[k]);
			if (distance < 50) {

				this->size_list[i] += 0.25;
				this->size_list[k] += 0.25;
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->shader.begin();

	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniform4fv("targets", &this->location_list[0].x, this->number_of_targets);
	this->shader.setUniform1fv("sizes", &this->size_list[0], this->number_of_targets);
	ofRect(0, 0, ofGetWidth(), ofGetHeight());

	this->shader.end();
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(720, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}