#include "control.h"
#include "defs.h"

static void assert_neutral_output(const control_output *output) {
    ASSERT(output != NULL, "output must not be null");

    for (u32 index = 0; index < CONTROL_CANARD_COUNT; index += 1u) {
        ASSERT(
            output->canard_angle_rad[index] == 0.0,
            "canard %u must be neutral",
            index
        );
    }
}

int main(void) {
    control_state state;
    control_output output;
    const control_input input = {
        .dt_s = 0.001,
        .position_m = {0.0, 0.0, 0.0},
        .velocity_body_mps = {1.0, 0.0, 0.0},
        .angular_rate_body_radps = {0.0, 0.0, 0.0},
        .euler_rad = {0.0, 0.0, 0.0},
    };

    control_init(&state);
    ASSERT(state.step_count == 0u, "step count must start at zero");

    control_step(&state, &input, &output);
    ASSERT(state.step_count == 1u, "step count must increment");
    assert_neutral_output(&output);

    return 0;
}
