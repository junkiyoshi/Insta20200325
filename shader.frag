#version 150

const int number_of_targets = 65;

out vec4 outputColor;
uniform float time;
uniform vec2 resolution;
uniform vec4 targets[number_of_targets];
uniform float sizes[number_of_targets];

void main() {

  vec2 p = (gl_FragCoord.xy * 2.0 - resolution) / min(resolution.x, resolution.y);
  vec3 color = vec3(0.0);
  for(int i = 0; i < number_of_targets; i++){

    vec2 t = vec2(targets[i].x, -targets[i].y) / min(resolution.x, resolution.y) * 2.0;
    t.xy += vec2(-resolution.x, resolution.y) / min(resolution.x, resolution.y);

    float r = 0.03 / length(p - t) * sizes[i];
    vec3 c = vec3(smoothstep(0.03, 1.0, r), smoothstep(0.03, 1.0, r), smoothstep(0.03, 1.0, r));
    color += c;
  }

  outputColor = vec4(color, 1.0);
}