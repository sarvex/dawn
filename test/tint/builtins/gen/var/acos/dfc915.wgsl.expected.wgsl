fn acos_dfc915() {
  var arg_0 = vec2<f32>();
  var res : vec2<f32> = acos(arg_0);
}

@stage(vertex)
fn vertex_main() -> @builtin(position) vec4<f32> {
  acos_dfc915();
  return vec4<f32>();
}

@stage(fragment)
fn fragment_main() {
  acos_dfc915();
}

@stage(compute) @workgroup_size(1)
fn compute_main() {
  acos_dfc915();
}