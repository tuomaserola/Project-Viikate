#include "control.h"

#include <math.h>

static bool control_vector_is_finite(const f64 values[CONTROL_AXIS_COUNT]) {
    for (u32 index = 0; index < CONTROL_AXIS_COUNT; index += 1u) {
        if (isfinite(values[index])) {
            continue;
        }

        return false;
    }

    return true;
}

static void control_assert_input(const control_input *input) {
    ASSERT(input != NULL, "control input must not be null");
    ASSERT(isfinite(input->dt_s), "control timestep must be finite");
    ASSERT(input->dt_s > 0.0, "control timestep must be positive");
    ASSERT(
        control_vector_is_finite(input->position_m),
        "position input must be finite"
    );
    ASSERT(
        control_vector_is_finite(input->velocity_body_mps),
        "body velocity input must be finite"
    );
    ASSERT(
        control_vector_is_finite(input->angular_rate_body_radps),
        "angular rate input must be finite"
    );
    ASSERT(
        control_vector_is_finite(input->euler_rad),
        "euler angle input must be finite"
    );
}

static void control_output_neutral(control_output *output) {
    ASSERT(output != NULL, "control output must not be null");

    for (u32 index = 0; index < CONTROL_CANARD_COUNT; index += 1u) {
        output->canard_angle_rad[index] = 0.0;
    }
}

void control_init(control_state *state) {
    ASSERT(state != NULL, "control state must not be null");

    state->step_count = 0u;
    state->roll_integrator = 0.0;
    state->roll_filter = 0.0;
    state->pitch_integrator = 0.0;
    state->pitch_filter = 0.0;
    state->yaw_integrator = 0.0;
    state->yaw_filter = 0.0;
}

void control_step(
    control_state *state,
    const control_input *input,
    control_output *output
) {
    ASSERT(state != NULL, "control state must not be null");
    ASSERT(state->step_count < 0xffffffffu, "control step counter overflow");
    control_assert_input(input);

    control_output_neutral(output);
    state->step_count += 1u;
}
