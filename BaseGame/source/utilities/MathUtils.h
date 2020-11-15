/*
 * MathUtils.h
 *
 *  Created on: 5 lis 2020
 *      Author: Krzysztof
 */

#ifndef UTILITIES_MATHUTILS_H_
#define UTILITIES_MATHUTILS_H_

#include <glm/glm.hpp> // glm::ivec2, glm:mat4
#include <vector> //std::vector

namespace base_game {

class MathUtils {
public:
	static bool pointInPoly(glm::vec2 const &test,
			const std::vector<glm::vec2> &polygon);
};

} /* namespace base_game */

#endif /* UTILITIES_MATHUTILS_H_ */
