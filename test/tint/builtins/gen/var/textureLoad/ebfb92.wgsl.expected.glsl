#version 310 es

uniform highp usampler2D arg_0_1;
void textureLoad_ebfb92() {
  ivec2 arg_1 = ivec2(0);
  uint arg_2 = 1u;
  uvec4 res = texelFetch(arg_0_1, arg_1, int(arg_2));
}

vec4 vertex_main() {
  textureLoad_ebfb92();
  return vec4(0.0f);
}

void main() {
  gl_PointSize = 1.0;
  vec4 inner_result = vertex_main();
  gl_Position = inner_result;
  gl_Position.y = -(gl_Position.y);
  gl_Position.z = ((2.0f * gl_Position.z) - gl_Position.w);
  return;
}
#version 310 es
precision mediump float;

uniform highp usampler2D arg_0_1;
void textureLoad_ebfb92() {
  ivec2 arg_1 = ivec2(0);
  uint arg_2 = 1u;
  uvec4 res = texelFetch(arg_0_1, arg_1, int(arg_2));
}

void fragment_main() {
  textureLoad_ebfb92();
}

void main() {
  fragment_main();
  return;
}
#version 310 es

uniform highp usampler2D arg_0_1;
void textureLoad_ebfb92() {
  ivec2 arg_1 = ivec2(0);
  uint arg_2 = 1u;
  uvec4 res = texelFetch(arg_0_1, arg_1, int(arg_2));
}

void compute_main() {
  textureLoad_ebfb92();
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  compute_main();
  return;
}