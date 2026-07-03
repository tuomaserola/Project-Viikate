control_inc = include_directories('include')

control_sources = files('src/control.c')

control_lib = static_library(
  'control',
  sources: control_sources,
  include_directories: control_inc,
  dependencies: shared_dep,
)

control_dep = declare_dependency(
  include_directories: control_inc,
  link_with: control_lib,
  dependencies: shared_dep,
)

control_smoke = executable(
  'control_smoke',
  sources: files('test/control_smoke.c'),
  dependencies: [
    control_dep,
    shared_dep,
  ],
)

test('control_smoke', control_smoke)
