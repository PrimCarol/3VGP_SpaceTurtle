#ifndef __MATHUTILS_H__
#define __MATHUTILS_H__ 1

#include <math.h>

class MathUtils {
	public:
		static float Clamp(float value, float minVal, float maxVal);
		static float Sqroot (const float value);
		static float Cosine (float value);
		static float Arcosine(float value);
		static float Sine (float value);
		static float Power(float value, float power);

	private:
		MathUtils();
		MathUtils(const MathUtils& copy);
		~MathUtils();
};

inline float MathUtils::Clamp(float value, float minVal, float maxVal) {
    if(value >= maxVal)return maxVal;
    if(value <= minVal)return minVal;
	return value;
}

inline float MathUtils::Sqroot (const float value){
    return  (float)sqrt(value);
}

inline float MathUtils::Cosine (float value){
    return cosf(value);
}

inline float MathUtils::Arcosine (float value){
    return acosf(value);
}

inline float MathUtils::Sine (float value){
    return sinf(value);
}

inline float MathUtils::Power(float value, float power){
    return powf(value,power);
}

#endif
