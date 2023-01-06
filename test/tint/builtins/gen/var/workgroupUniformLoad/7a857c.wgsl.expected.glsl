#version 310 es

shared float arg_0;
float tint_workgroupUniformLoad_arg_0() {
  barrier();
  float result = arg_0;
  barrier();
  return result;
}

void workgroupUniformLoad_7a857c() {
  float res = tint_workgroupUniformLoad_arg_0();
}

void compute_main(uint local_invocation_index) {
  {
    arg_0 = 0.0f;
  }
  barrier();
  workgroupUniformLoad_7a857c();
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  compute_main(gl_LocalInvocationIndex);
  return;
}
