fn dot_0c577b() {
  var arg_0 = vec4<f32>();
  var arg_1 = vec4<f32>();
  var res : f32 = dot(arg_0, arg_1);
}

@stage(vertex)
fn vertex_main() -> @builtin(position) vec4<f32> {
  dot_0c577b();
  return vec4<f32>();
}

@stage(fragment)
fn fragment_main() {
  dot_0c577b();
}

@stage(compute) @workgroup_size(1)
fn compute_main() {
  dot_0c577b();
}