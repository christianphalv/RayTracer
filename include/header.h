#pragma once

#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

#include "Camera.h"
#include "Image.h"
#include "MathUtils.h"
#include "Scene.h"
#include "Vector3.h"

Vector3 traceRay(Ray ray, Scene* scene);