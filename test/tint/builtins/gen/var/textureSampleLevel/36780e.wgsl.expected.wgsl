@group(1) @binding(0) var arg_0 : texture_depth_2d_array;

@group(1) @binding(1) var arg_1 : sampler;

fn textureSampleLevel_36780e() {
  var arg_2 = vec2<f32>();
  var arg_3 = 1;
  var arg_4 = 0;
  var res : f32 = textureSampleLevel(arg_0, arg_1, arg_2, arg_3, arg_4, vec2<i32>());
}

@stage(vertex)
fn vertex_main() -> @builtin(position) vec4<f32> {
  textureSampleLevel_36780e();
  return vec4<f32>();
}

@stage(fragment)
fn fragment_main() {
  textureSampleLevel_36780e();
}

@stage(compute) @workgroup_size(1)
fn compute_main() {
  textureSampleLevel_36780e();
}