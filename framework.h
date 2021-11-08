inline float frand(int lo, int hi)
{
    return lo + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(hi-lo)));
}

// from stack overflow
// > (sqrt(1-u) sin(2πv), sqrt(1-u) cos(2πv), sqrt(u) sin(2πw), sqrt(u) cos(2πw))
inline Quaternion RandomQuaternion()
{
    float pi = 3.1415926535897932384626433832795f;
    float u = frand(0.0f, 1.0f);
    float v = frand(0.0f, 1.0f);
    float w = frand(0.0f, 1.0f);

    float theta = sqrtf(1.0f - u);
    float phi = 2.0f * pi * v;

    float x = theta * sinf(phi);
    float y = theta * cosf(phi);
    float z = sqrtf(u) * sinf(2.0f * pi * w);
    float w2 = sqrtf(u) * cosf(2.0f * pi * w);
    return {x, y, z, w2};
}
