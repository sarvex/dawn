// Enable a void internal extension for multiple times
enable f16;
enable f16;
enable f16;

@stage(fragment)
fn main() -> @location(0) vec4<f32> {
    return vec4<f32>(0.1, 0.2, 0.3, 0.4);
}