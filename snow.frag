#version 400 core
#extension GL_OES_standard_derivatives : enable

uniform vec2 resolution;
uniform float time;

float snow(vec2 uv, float scale) {
float w = smoothstep(1.0, 0.0, -uv.y * (scale / 10.0));

if (w < 0.1) {
    return 0.0;
}

float c = time / scale;

// Fall to left:
// uv += clock;

uv.y += c;
uv.x -= c;

uv.y += c * 2.0;
uv.x += cos(uv.y + time * 0.5) / scale;
uv *= scale;

vec2 s = floor(uv);
vec2 f = fract(uv);
vec2 p = vec2(0.0);

float k = 3.0;
float d = 0.0;
p = 0.5 + 0.35 * sin(11.0 * fract(sin((s + p + scale) * mat2(7, 3, 6, 5)) * 5.0)) - f;
d = length(p);
k = min(d, k);

k = smoothstep(0.0, k, sin(f.x + f.y) * 0.01);
    return k * w;
}

void main (void) {
    float size = mix(min(resolution.x, resolution.y), max(resolution.x, resolution.y), 0.5);
    vec2 uv = (gl_FragCoord.xy * 2.0 - resolution.xy) / size;
    float c = smoothstep(1.0, 0.0, clamp(uv.y * 0.1 + 0.75, 0.0, 0.75));

    c += snow(uv, 30.0) * 0.3;
    c += snow(uv, 20.0) * 0.5;
    c += snow(uv, 15.0) * 0.8;

    c += snow(uv, 10.0);
    c += snow(uv, 8.0);
    c += snow(uv, 6.0);
    c += snow(uv, 5.0);

    gl_FragColor = vec4(vec3(c), 1.0); // 0.0
}
