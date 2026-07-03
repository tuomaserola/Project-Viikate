#pragma once

#include "defs.h"

#define CONTROL_AXIS_COUNT 3u
#define CONTROL_CANARD_COUNT 4u

typedef struct control_input {
    f64 dt_s;
    f64 position_m[CONTROL_AXIS_COUNT];
    f64 velocity_body_mps[CONTROL_AXIS_COUNT];
    f64 angular_rate_body_radps[CONTROL_AXIS_COUNT];
    f64 euler_rad[CONTROL_AXIS_COUNT];
} control_input;

typedef struct control_output {
    f64 canard_angle_rad[CONTROL_CANARD_COUNT];
} control_output;

typedef struct control_state {
    u32 step_count;
    f64 roll_integrator;
    f64 roll_filter;
    f64 pitch_integrator;
    f64 pitch_filter;
    f64 yaw_integrator;
    f64 yaw_filter;
} control_state;

void control_init(control_state *state);
void control_step(
    control_state *state,
    const control_input *input,
    control_output *output
);
