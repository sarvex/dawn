fn fma_6a3283() {
  var arg_0 = vec4<f32>();
  var arg_1 = vec4<f32>();
  var arg_2 = vec4<f32>();
  var res : vec4<f32> = fma(arg_0, arg_1, arg_2);
}

@stage(vertex)
fn vertex_main() -> @builtin(position) vec4<f32> {
  fma_6a3283();
  return vec4<f32>();
}

@stage(fragment)
fn fragment_main() {
  fma_6a3283();
}

@stage(compute) @workgroup_size(1)
fn compute_main() {
  fma_6a3283();
}