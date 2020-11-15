/*
 * MathUtils.cpp
 *
 *  Created on: 5 lis 2020
 *      Author: Krzysztof
 */

#include "MathUtils.h"
#include "../debugging/Logger.h"

#include <glm/glm.hpp> // glm::ivec2, glm:mat4
#include <vector> //std::vector

namespace logger = base_game::logger;

using std::vector;
using std::stringstream;

namespace base_game {

//
// Math::PointInPoly - Chapter X, page Y
//
bool MathUtils::pointInPoly(glm::vec2 const &test,
		const vector<glm::vec2> &polygon) {

	stringstream ss;

	glm::vec2 newPoint, oldPoint;
	glm::vec2 left, right;

	bool inside = false;

	size_t points = polygon.size();

	// The polygon must at least be a triangle
	if (points < 3)
		return false;

	oldPoint = polygon[points - 1];

	ss << "test.x: (" << test.x << "," << test.y << ")";
	logger::info(ss);

	for (unsigned int i = 0; i < points; i++) {
		newPoint = polygon[i];
		if (newPoint.x > oldPoint.x) {
			left = oldPoint;
			right = newPoint;
		} else {
			left = newPoint;
			right = oldPoint;
		}

		logger::info("START");

		ss << "newPoint: (" << newPoint.x << "," << newPoint.y << ")";
		ss << "; oldPoint.x: (" << oldPoint.x << "," << oldPoint.y << ")";

		if (newPoint.x < test.x) {
			ss << "; newPoint < test true";
		} else {
			ss << "; newPoint < test false";
		}

		if (test.x <= oldPoint.x) {
			ss << "; test <= oldPoint true";
		} else {
			ss << "; test <= oldPoint false";
		}


		if ((newPoint.x < test.x) == (test.x <= oldPoint.x)) {
			ss << "; newPoint<test<=oldPoint true";
		} else {
			ss << "; newPoint<test<=oldPoint false";
		}

		logger::info(ss);

		ss << "test.y: " << test.y;
		ss << "; left.y: " << left.y;
		ss << "; right.x: " << right.x;
		ss << "; left.x: " << left.x;
		ss << "; right.y: " << right.y;
		ss << "; test.x: " << test.x;

		logger::info(ss);


		ss << "(test.y - left.y) * (right.x - left.x): "
				<< (test.y - left.y) * (right.x - left.x);
		ss << "; (right.y - left.y) * (test.x - left.x): "
				<< (right.y - left.y) * (test.x - left.x);

		logger::info(ss);

		if ((test.y - left.y) * (right.x - left.x)
				< (right.y - left.y) * (test.x - left.x)) {
			logger::info(
					"((test.y - left.y) * (right.x - left.x) < (right.y - left.y) * (test.x - left.x)) : true ");
		} else {
			logger::info(
					"((test.y - left.y) * (right.x - left.x) < (right.y - left.y) * (test.x - left.x)) : false ");
		}


		// A point exactly on the left side of the polygon
		// will not intersect - as if it were "open"
		if ((newPoint.x < test.x) == (test.x <= oldPoint.x)
				&& (test.y - left.y) * (right.x - left.x)
						< (right.y - left.y) * (test.x - left.x)) {
			inside = !inside;

			if (inside) {
				logger::info("CHANGED: inside");
			} else {
				logger::info("CHANGED: !inside");
			}
		} else {
			if (inside) {
				logger::info("the same: inside");
			} else {
				logger::info("the same: !inside");
			}
		}

		oldPoint = newPoint;

		logger::info("");

	}
	return (inside);
}


} /* namespace base_game */
