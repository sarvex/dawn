@group(1) @binding(0) var arg_0 : texture_storage_2d_array<rgba16uint, write>;

fn textureStore_6da692() {
  var arg_1 = vec2<i32>();
  var arg_2 = 1;
  var arg_3 = vec4<u32>();
  textureStore(arg_0, arg_1, arg_2, arg_3);
}

@stage(vertex)
fn vertex_main() -> @builtin(position) vec4<f32> {
  textureStore_6da692();
  return vec4<f32>();
}

@stage(fragment)
fn fragment_main() {
  textureStore_6da692();
}

@stage(compute) @workgroup_size(1)
fn compute_main() {
  textureStore_6da692();
}