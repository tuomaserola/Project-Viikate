project(
  'viikate',
  ['c', 'cpp'],
  default_options : [
    'buildtype=release',
    'c_args=-fno-pic',
    'cpp_args=-fno-pic',
  ]
)

dependencies = []
dependencies += dependency('teensy_core', fallback: ['teensy_core', 'teensy_core_dep'])
dependencies += dependency('bme280', fallback: ['bme280', 'bme280_dep'])

src = files()
inc = include_directories('src/')

subdir('src')

exe = executable(
  'firmware',
  src,
  include_directories: inc,
  dependencies: dependencies,
  link_language: 'c',
)

objcopy = find_program('objcopy')


hex_file = custom_target(
  'hex_convert',
  input : exe,
  output : '@BASENAME@.hex',
  command : [
    objcopy, '-O', 'ihex',
    '--set-section-flags', '.flashconfig=alloc,load,readonly,data',
    '--set-section-flags', '.image_vector_table=alloc,load,readonly,data',
    '@INPUT@', '@OUTPUT@'
  ],
  build_by_default : true,
  install : false
)
