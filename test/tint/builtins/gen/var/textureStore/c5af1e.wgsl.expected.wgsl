@group(1) @binding(0) var arg_0 : texture_storage_3d<rgba16float, write>;

fn textureStore_c5af1e() {
  var arg_1 = vec3<i32>();
  var arg_2 = vec4<f32>();
  textureStore(arg_0, arg_1, arg_2);
}

@stage(vertex)
fn vertex_main() -> @builtin(position) vec4<f32> {
  textureStore_c5af1e();
  return vec4<f32>();
}

@stage(fragment)
fn fragment_main() {
  textureStore_c5af1e();
}

@stage(compute) @workgroup_size(1)
fn compute_main() {
  textureStore_c5af1e();
}