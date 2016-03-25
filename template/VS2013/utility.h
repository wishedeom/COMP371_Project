#pragma once

#include <vector>

#include "glfw3.h"
#include "glm.hpp"

//------------Constants--------------//

// Global up direction
const glm::vec3 up(0.0f, 0.0f, 1.0f);

// Occasionally useful
const double pi = 3.1415926535897;

// 4-dimensional identity matrix
const glm::mat4 id4;


//------------Functions---------------//

// Given a number of profile polyline vertices p and a number of trajectory polyline vertices t, computes the array of vertex indices to draw each triangle in the
// translational sweep.
// p: Number of vertices in profile polyline
// t: Number of vertices in translational polyline
std::vector<GLuint> computeSweepIndices(const int p, const int t);


// Given a std::vector of 3D vectors representing vertices of a polyline (curve), computes the displacement of each vertex from the first vertex.
// Effectively translates the polyline so that the first vertes is at the origin.
// polyline: Polyline to compute displacements of
std::vector<glm::vec3> computeDisplacements(const std::vector<glm::vec3>& polyline);


// Compute the translational sweep generated by two polylines in 3D. The profileCurve is translated by the trajectoryCurve.
std::vector<glm::vec3> computeTranslationalSweep(const std::vector<glm::vec3>& profilePolyline, const std::vector<glm::vec3>& trajectoryPolyline);


// Rotates a planar polyline once by a given angle about the positive z-axis
std::vector<glm::vec3> rotatePolyline(const std::vector<glm::vec3>& polyline, const GLfloat angle);


// Produces a rotational sweep from a  profile curve and number of spans
std::vector<glm::vec3> computeRotationalSweep(const std::vector<glm::vec3>& profilePolyline, const int numSpans);


// Interprets a collection of vec2 as a collection of vec3 in the x-y plane.
std::vector<glm::vec3> embed(const std::vector<glm::vec2>& vertices);


// Flattens an std::vector of n glm::vec3s into an std::vector of 3 * n GLfloats.
std::vector<GLfloat> flatten(const std::vector<glm::vec3> vertices);


// Produces a collection of vec2s representing a regular n-gon with a given apothem length, centred at the origin, with a point on the positive x-axis.
std::vector<glm::vec2> regularPolygon(const int sides, const float apothem);


// Given a transformation matrix and a collection of vertices representing a polygon in 2D, applies the transformation matrix to each vertex
std::vector<glm::vec2> transformPolygon(const std::vector<glm::vec2>& polygon, const glm::mat4& matrix);


// Generates a random float from 0.0f to 1.0f
float randomFloat();


// Generates a random RGB colour
glm::vec3 randomColour();


// Translates a collection of vertices (a mesh) to a new position
std::vector<glm::vec3> translate(const std::vector<glm::vec3>& vertices, const glm::vec3& difference);