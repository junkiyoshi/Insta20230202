#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	vector<ofColor> color_list;

	float len = 600;
	vector<glm::vec2> target_list;
	ofColor color;
	for (int i = 0; i < 3; i++) {

		auto noise_param = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.003), 0, 1, 0, 200);
		target_list.push_back(this->make_point(len, noise_param));

		color.setHsb(ofMap(i, 0, 3, 0, 255), 100, 255);
		color_list.push_back(color);
	}

	for (int i = 0; i < target_list.size(); i++) {

		ofSetColor(color_list[i]);
		ofDrawCircle(target_list[i], 8);
	}

	for (int param = 0; param <= 100; param += 2) {

		auto location = this->make_point(len, param);

		auto target = target_list[0];
		auto index = 0;
		auto distance = glm::distance(location, target_list[0]);
		for (int i = 1; i < target_list.size(); i++) {

			if (distance > glm::distance(location, target_list[i])) {

				target = target_list[i];
				index = i;
				distance = glm::distance(location, target_list[i]);
			}
		}

		ofDrawCircle(this->make_point(len, param), 4);
		this->draw_arrow(this->make_point(len, param), target, 16, color_list[index]);
	}
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
void ofApp::draw_arrow(glm::vec2 location, glm::vec2 target, float size, ofColor color) {

	if (glm::distance(location, target) < size) return;

	auto angle = std::atan2(target.y - location.y, target.x - location.x);
	auto translate_location = target - glm::vec2(size * 3 * cos(angle), size * 3 * sin(angle));
	auto distance = glm::distance(translate_location, location);

	ofPushMatrix();
	ofTranslate(translate_location);

	ofSetColor(color);
	ofFill();
	ofBeginShape();
	ofVertex(glm::vec2(size * cos(angle), size * sin(angle)));
	ofVertex(glm::vec2(size * 0.25 * cos(angle + PI * 0.5), size * 0.25 * sin(angle + PI * 0.5)));
	ofVertex(glm::vec2(size * 0.25 * cos(angle - PI * 0.5), size * 0.25 * sin(angle - PI * 0.5)));
	ofEndShape();

	ofBeginShape();
	ofVertex(glm::vec2(size * 0.25 * cos(angle + PI * 0.5), size * 0.25 * sin(angle + PI * 0.5)) * 0.25);
	ofVertex(glm::vec2(size * 0.25 * cos(angle + PI * 0.5), size * 0.25 * sin(angle + PI * 0.5)) * 0.25 - glm::vec2(distance * cos(angle), distance * sin(angle)));
	ofVertex(glm::vec2(size * 0.25 * cos(angle - PI * 0.5), size * 0.25 * sin(angle - PI * 0.5)) * 0.25 - glm::vec2(distance * cos(angle), distance * sin(angle)));
	ofVertex(glm::vec2(size * 0.25 * cos(angle - PI * 0.5), size * 0.25 * sin(angle - PI * 0.5)) * 0.25);
	ofEndShape();

	ofPopMatrix();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}