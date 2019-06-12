#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	auto len = 20;
	auto noise_param = ofGetFrameNum() * 0.01;
	for (int radius = 50; radius < 300; radius += 30) {

		auto rotate = 0.f;
		auto noise_value = ofNoise(noise_param += 0.08);
		if (noise_value < 0.45) {

			rotate = ofMap(noise_value, 0, 0.45, -90, 0);
		}
		else if (noise_value > 0.55) {

			rotate = ofMap(noise_value, 0.55, 1, 0, 90);
		}

		ofPushMatrix();
		ofRotateY(rotate);

		vector<glm::vec2> outer, inner;
		for (int deg = 0; deg < 360; deg++) {

			outer.push_back(glm::vec2((radius + len * 0.5) * cos(deg * DEG_TO_RAD), (radius + len * 0.5) * sin(deg * DEG_TO_RAD)));
			inner.push_back(glm::vec2((radius - len * 0.5) * cos(deg * DEG_TO_RAD), (radius - len * 0.5) * sin(deg * DEG_TO_RAD)));
		}

		ofFill();
		ofSetColor(239);
		ofBeginShape();
		ofVertices(outer);
		ofNextContour(true);
		ofVertices(inner);
		ofEndShape(true);

		ofNoFill();
		ofSetColor(39);
		ofBeginShape();
		ofVertices(outer);
		ofNextContour(true);
		ofVertices(inner);
		ofEndShape(true);

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}